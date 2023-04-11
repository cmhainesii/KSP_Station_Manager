#include "include/station_list.hpp"
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

    for (auto i = 0; i < m_stations.size(); ++i)
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