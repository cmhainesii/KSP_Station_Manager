#ifndef SPACE_STATION_HPP
#define SPACE_STATION_HPP

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <array>

#include "celestial_body.hpp"

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace KSP_SM
{

    using std::string;
    using std::vector;

    struct OrbitalParameters
    {
        size_t apoapsis;
        size_t periapsis;

    public:
        OrbitalParameters() = default;

        OrbitalParameters(size_t ap, size_t pe);
    };

    struct DockingPortCount {

        std::size_t xs {};
        std::size_t sm {};
        std::size_t md {};
        std::size_t lg {};
        std::size_t xl {};

      public:
        DockingPortCount() = default;
        DockingPortCount(std::array<std::size_t,5> counts);
    };

    enum class CommunicationDevice
    {
        COMM_16,
        COMM_16S,
        RA_15,
        RA_2,
        COMM_88_88,
        COMM_DTS_M1,
        COMM_HG_5,
        COMM_HG_55,
        RA_100,
    };

    enum class DockingPort
    {
        XSMALL,
        SMALL,
        MEDIUM,
        LARGE,
        XLARGE
    };

    class SpaceStationBuilder
    {

    public:
        explicit SpaceStationBuilder(string station_id);

        class SpaceStation
        {

        public:
            string ToString() const;
            static string DockingPortToString(DockingPort port);
            static string CommsDeviceToString(CommunicationDevice dev);
            string GetName() const;
            string GetStationID() const;
            size_t GetCapacity() const;
            bool isActive() const;
            OrbitalParameters GetOrbitalDetails() const;
            SpaceStation() = default;
            SpaceStation(string station_id) noexcept;
            ~SpaceStation();


        private:
            friend class SpaceStationBuilder;
            string m_station_id;
            string m_station_name = "Unknown Station";
            OrbitalParameters m_orbit_details = OrbitalParameters(100000, 100000);
            size_t m_capacity = 3;
            bool m_active = true;
            vector<CommunicationDevice> m_comms_devices;
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
        SpaceStationBuilder& AddCommsDevice(CommunicationDevice dev);
        SpaceStationBuilder& AddCommsDevices(size_t quantity, CommunicationDevice dev);
        SpaceStationBuilder& AddCommsDevices(vector<CommunicationDevice> devs);
        SpaceStationBuilder& AddKerbal(string kerbal_name);
        SpaceStationBuilder& AddKerbals(const vector<string>& kerbals);
        SpaceStationBuilder& SetDockingPortQuantities(const DockingPortCount& quantities);
        SpaceStationBuilder& SetOrbitingBody(CelestialBody planet);
        std::unique_ptr<SpaceStation> build();
        static std::unique_ptr<SpaceStation> createStationFromConsoleInput();

    private:
        std::unique_ptr<SpaceStation> m_space_station;
    };

}
#endif