#ifndef STATION_LIST_HPP
#define STATION_LIST_HPP


#include <vector>
#include <string>
#include <memory>
#include "space_station.hpp"
#include <nlohmann/json.hpp>

using std::vector;
using std::string;
using unique_station = std::unique_ptr<KSP_SM::SpaceStationBuilder::SpaceStation>;

class StationList {
  public:
    StationList() = default;
    void AddStation(unique_station& station) noexcept;
    bool DeleteStation(const std::size_t index) noexcept;
    void ListAllStations() const;
    std::size_t ReadStationsFromFile(const string &filename);
    std::size_t GetSize() noexcept;
    void WriteStationsToFile(const string &filename);
    vector<unique_station>& GetStations();
    void Reset() noexcept;
    void ManageStationsFromConsole();

  private:
   vector<unique_station> m_stations;
   void AddKerbalsFromConsole(const std::size_t index, std::size_t max_additional);
   size_t RemoveKerbalFromConsole(const std::size_t& index);
   void ChangeCapacityFromConsole(const size_t& index);
};


#endif