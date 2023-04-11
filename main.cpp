#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include <ios>

#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "include/space_station.hpp"
#include "include/menu.hpp"
#include "include/celestial_body.hpp"
#include "include/build_vars.h"
#include "include/station_list.hpp"

using SpaceStation = KSP_SM::SpaceStationBuilder::SpaceStation;
using SpaceStationBuilder = KSP_SM::SpaceStationBuilder;

using nlohmann::json;
using std::vector;
using namespace KSP_SM;

using unique_station = std::unique_ptr<SpaceStation>;

int main(int argc, char **argv);



const string STATIONS_FILENAME = "stations.json";

int main(int argc, char **argv)
{

    if (argc > 1) 
    {
        // Running in non-interactive mode!
        if (std::strcmp(argv[1], "-i") == 0)
        {
            StationList stations;

            
            
            std::ofstream out_file("stations.txt");
            for (const auto& current : stations.GetStations())
            {
                out_file << current->ToString();
                out_file.close();
            }
            
        }

        return 0;
    }

    StationList stations;
    bool exitProgram = false;
    std::string buffer;
    std::string menuText = Menu::getMenuText();

    std::cout << "KSP Station Manger\n";
    std::cout << fmt::format("Verson: {}.{}\n", KSP_SM_VERSION_MAJOR, KSP_SM_VERSION_MINOR);

    while (!exitProgram)
    {


        std::cout << std::endl;
        std::cout << menuText;
        std::cout << "Enter Your Selection: ";
        std::cin >> buffer;
        char selection = std::tolower(buffer.at(0));
        if (selection == 'r')
        {
            // Attempt to read stations from file. Result is the number of stations read from json file.
            auto number_of_stations = stations.ReadStationsFromFile(STATIONS_FILENAME);
            if (!number_of_stations) // Show an error if no stations are found / file not found.
            {
                std::cerr << "Aborting." << std::endl;
                continue;
            }
            // Successful load, print number of stations loaded and go back to the main menu.
            std::cout << fmt::format("Read in {} stations from file {}.", stations.GetSize(), STATIONS_FILENAME) << std::endl;
            continue;
        }
        if (selection == 'w')
        {
            stations.WriteStationsToFile(STATIONS_FILENAME);

            std::cout << "Wrote stations list to file." << std::endl
                      << std::endl;
            continue;
        }
        if (selection == 'a')
        {
            auto newStation = SpaceStationBuilder::createStationFromConsoleInput();
            stations.AddStation(newStation);
            continue;
        }
        if (selection == 'd')
        {
            std::size_t station_index;
            std::cout << std::endl;
            std::cout << "Delete Station" << std::endl;
            std::cout << "Enter Station List Index: ";
            while(!(std::cin >> station_index))
            {
                std::cout << "Invalid Index" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Station List Index: ";

            }
            
            if(stations.DeleteStation(station_index))
            {
                std::cout << fmt::format("Deleted station at index {}", station_index) << std::endl;
            }
            else
            {
                std::cout << "Invalid index / Station not found" << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;

        }

        if (selection == 'l')
        {
            stations.ListAllStations();
            continue;
        }
        if (buffer.compare("q") == 0)
        {
            exitProgram = true;
            continue;
        }

        std::cerr << "Error reading selection." << std::endl;
    }

    return 0;
}






