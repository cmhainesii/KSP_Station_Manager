#include "include/station_list.hpp"
#include "include/utils.hpp"
#include <fmt/core.h>
#include <iostream>
#include <fstream>



void StationList::AddStation(unique_station& station) noexcept
{
    this->m_stations.push_back(std::move(station));
}

bool StationList::DeleteStation(const std::size_t index) noexcept
{
    if (index < this->m_stations.size())
    {
        this->m_stations.erase(m_stations.begin() + index);
        return true;
    }

    return false;
}

void StationList::ListAllStations() const
{

    for (size_t i = 0; i < m_stations.size(); ++i)
    {
        std::cout << fmt::format("{}) {}", i, m_stations.at(i)->ToString()) << std::endl;
    }
}

std::size_t StationList::ReadStationsFromFile(const string &filename)
{
    std::ifstream in_file(filename);
    if (!in_file)
    {
        std::cerr << fmt::format("Error: {} not found.", filename) << std::endl;
        return 0;
    }
    json j;
    in_file >> j;
    in_file.close(); // close file when done!

    this->Reset();                             // clear stations vector prior to loading stations from json
    m_stations = j.get<vector<unique_station>>(); // convert json to vector of unique_ptrs to json
    return m_stations.size();
}

std::size_t StationList::GetSize() noexcept
{
    return this->m_stations.size();
}

void StationList::WriteStationsToFile(const string &filename)
{
    json stations_json = this->m_stations;
    std::ofstream out_file(filename);
    out_file << stations_json.dump(4) << std::endl;
    out_file.close(); // close file when done!
}

vector<unique_station>& StationList::GetStations()
{
    return this->m_stations;
}

void StationList::Reset() noexcept
{
    this->m_stations.clear();
}


void StationList::ManageStationsFromConsole()
{
    if (this->GetSize() == 0) 
    {
        std::cout << "No stations to manage.\n";
        return;
    }
    
    string buffer {};
    size_t index;
    bool inputValidated {false};

    std::cout << "Manage Station\n\n";
    std::cout << "Enter station index: ";

    while (!inputValidated)
    {
        while (!(std::cin >> index))
        {
            std::cout << "Invalid response. Index must be an integer.\n";
            // Clear input buffer
            Utility::ClearInputBuffer();
        }

        if (index >= this->GetSize())
        {
            std::cout << "Invalid response. Index exceeds bounds of station list.\n";
            Utility::ClearInputBuffer();
            continue;
        }

        inputValidated = true;
    }

    std::cout << std::endl;
    Utility::ClearInputBuffer();

    bool doneManaging = false;

    while (!doneManaging)
    {
        std::cout << "Manage Station Options\n\n";
        std::cout << "A -> Add Kerbal\n";
        std::cout << "R -> Remove Kerbal\n";
        std::cout << "E -> Edit Capacity\n";
        std::cout << "F -> Finish Managing Stations\n\n";
        std::cout << "Enter Your Selection: ";
        std::getline(std::cin, buffer);
        if (buffer.size() == 0)
        {
            continue;
        }

        char selection = std::tolower(buffer.at(0));

        // Add Kerbals to station
        switch (selection)
        {
          case 'a': 
          {
            // Check that the station has capacity to add a kerbal
            if ( this->GetStations().at(index)->GetNumberKerbalsAboard() >= this->GetStations().at(index)->GetCapacity())
            {
                std::cerr << "Unable to add kerbals. This station is currently at capacity.\n";
                Utility::PressEnterToContinue();
                continue;
            }
            
            size_t max_additional_kerbals = this->GetStations().at(index)->GetCapacity() - this->GetStations().at(index)->GetNumberKerbalsAboard();
            
            this->AddKerbalsFromConsole(index, max_additional_kerbals);

            break;
          }
          case 'r':
          {
            auto number_on_board = this->GetStations().at(index)->GetNumberKerbalsAboard();
            if (number_on_board == 0)
            {
                std::cout << "Error: No kerbals onboard to remove.\n";
                Utility::PressEnterToContinue();
                continue;
            }

            this->RemoveKerbalFromConsole(index);            
            break;
          }

          case 'e':
          {
            this->ChangeCapacityFromConsole(index);
            break;
          }

          case 'f':
          {
            doneManaging = true;
            break;
          }
          
          default:
          {
            break;
          }
          
        }


    }    
}

void StationList::AddKerbalsFromConsole(const std::size_t stationIndex, std::size_t max_additonal)
{
    bool doneAddingKerbals {false};
    string buffer {};

    while (!doneAddingKerbals && max_additonal >= 1)
    {
        std::cout << "Enter Kerbal Name (leave blank to finish): ";
        std::getline(std::cin, buffer);

        if (buffer.compare("") != 0)
        {
            // Add kerbal to the stations list
            this->m_stations.at(stationIndex)->AddKerbal(buffer);
            --max_additonal;
            continue;
        }

        // If execution reaches here, the user is finished entering kerbals.
        
        // Print a message letting the user know in the event the station
        // is at capacity and we are returning to the manage station menu
        // automatically.
        
        doneAddingKerbals = true;
    }

    if (max_additonal == 0)
    {
        std::cout << "Station has reached capacity. Returning to manage stations menu.\n";
        Utility::PressEnterToContinue();
    }
}

std::size_t StationList::RemoveKerbalFromConsole(const std::size_t &index)
{
    size_t kerbal_remove_index{};
    size_t num_removed {};

    bool done_removing_kerbals{false};
    while (!done_removing_kerbals)
    {
        std::cout << "Enter index of kerbal to remove: ";
        while (!(std::cin >> kerbal_remove_index))
        {
            std::cout << "Invalid response. Must be an integer.\n";
            Utility::ClearInputBuffer();
            std::cout << "Enter index of kerbal to remove: ";
        }

        // Validate input
        if (kerbal_remove_index >= this->m_stations.at(index)->GetNumberKerbalsAboard())
        {
            std::cout << "Error: Index exceeds bounds of list of onboard kerbals.\n";
            continue;
        }

        // If exection reaches here, valid index was received
        // Remove kerbal by index
        num_removed = this->GetStations().at(index)->RemoveKerbalByIndex(kerbal_remove_index);
        std::cout << fmt::format("Removed kerbal at index {}\n", kerbal_remove_index);
        done_removing_kerbals = true;
        
    }
    return num_removed;
}

void StationList::ChangeCapacityFromConsole(const std::size_t& index)
{
    size_t new_capacity;
    unique_station& current_station = this->GetStations().at(index);
    std::cout << "Enter new capacity: ";
    while(!(std::cin >> new_capacity))
    {
        std::cout << "Invalid Response. Must be positive integer or zero.\n";
        Utility::ClearInputBuffer();
    }

    Utility::ClearInputBuffer();

    // Check capacity is equal to or larger than the current number of kerbals
    // onboard.
    if (new_capacity < current_station->GetNumberKerbalsAboard())
    {
        std::cerr << "ERROR: New capacity cannot be less than the number of kerbals currently onboard. Aborting\n\n";
        Utility::PressEnterToContinue();
        return;
    }

    // Change station capacity
    current_station->ChangeCapcity(new_capacity);
    std::cout << fmt::format("Station capacity is now {}\n\n", current_station->GetCapacity());
    Utility::PressEnterToContinue();
    return;
}