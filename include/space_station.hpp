#ifndef SPACE_STATION_HPP
#define SPACE_STATION_HPP

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <array>

#include "celestial_body.hpp"

#include <nlohmann/json.hpp>
#include "devices.hpp"

using nlohmann::json;



namespace KSP_SM
{

    using std::string;
    using std::vector;

    struct OrbitalParameters
    {
        size_t apoapsis { 100000};
        std::size_t periapsis {100000};

    public:
        OrbitalParameters() = default;
        explicit OrbitalParameters(size_t ap, size_t pe);
    };

    

    

    class SpaceStationBuilder
    {

    public:
        explicit SpaceStationBuilder(string station_id);

        class SpaceStation
        {

        public:
            ~SpaceStation();
            string ToString() const;
            static string DockingPortToString(DockingPort port);
            static string CommsDeviceToString(CommunicationDevice dev);
            string GetName() const;
            string GetStationID() const;
            std::size_t GetCapacity() const;
            std::size_t GetNumberKerbalsAboard() const;
            void AddKerbal(const std::string& name);
            bool isActive() const;
            OrbitalParameters GetOrbitalDetails() const;
            void ChangeCapcity(const std::size_t& capacity);
            SpaceStation() = default;
            explicit SpaceStation(string station_id) noexcept;
            std::size_t RemoveKerbalByIndex(std::size_t index);
            


        private:
            friend class SpaceStationBuilder;
            string m_station_id;
            string m_station_name = "Unknown Station";
            OrbitalParameters m_orbit_details = OrbitalParameters(100000, 100000);
            size_t m_capacity = 3;
            bool m_active = true;
            CommsDevCount m_comms_dev_quantities;
            DockingPortCount m_port_quantities;
            vector<string> m_kerbals;
            CelestialBody m_orbiting_body = CelestialBody::KERBIN;
            std::unique_ptr<SpaceStation> build();
            friend void to_json(json& j, const SpaceStation& ss);
            friend void from_json(const json& j, SpaceStation& ss);
            friend void to_json(json& j, const std::unique_ptr<SpaceStation>& ss);
            friend void from_json(const json& j, std::unique_ptr<SpaceStation>& ss);
        };

        SpaceStationBuilder& SetName(const string &name);
        SpaceStationBuilder& SetOrbitDetails(OrbitalParameters params);
        SpaceStationBuilder& SetOrbitDetails(size_t apoapsis, size_t periapsis);
        SpaceStationBuilder& SetCapacity(size_t capacity);
        SpaceStationBuilder& SetActive(bool is_active);
        SpaceStationBuilder& AddKerbal(string kerbal_name);
        SpaceStationBuilder& AddKerbals(const vector<string>& kerbals);
        SpaceStationBuilder& SetDockingPortQuantities(const DockingPortCount& quantities);
        SpaceStationBuilder& SetCommsDevicesQuantities(const CommsDevCount& quantities);
        SpaceStationBuilder& SetOrbitingBody(CelestialBody planet);
        std::unique_ptr<SpaceStation> build();
        static std::unique_ptr<SpaceStation> createStationFromConsoleInput();

    private:
        std::unique_ptr<SpaceStation> m_space_station;
    };

}
#endif