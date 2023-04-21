#ifndef DEVICES_HPP
#define DEVICES_HPP

#include <cstdlib>
#include <array>

constexpr size_t NUM_COMM_DEVICES = 9;
constexpr size_t NUM_DOCKING_PORTS = 5;

namespace KSP_SM
{

    struct DockingPortCount
    {

        std::size_t xs{};
        std::size_t sm{};
        std::size_t md{};
        std::size_t lg{};
        std::size_t xl{};

    public:
        DockingPortCount() = default;
        explicit DockingPortCount(std::array<std::size_t, 5> counts);
        std::array<std::size_t, NUM_DOCKING_PORTS> GetAsArray() const;
    };

    struct CommsDevCount
    {
        std::size_t C16 {};
        std::size_t C16S {};
        std::size_t C8888 {};
        std::size_t CDTS {};
        std::size_t CHG5 {};
        std::size_t CHG55 {};
        std::size_t RA15 {};
        std::size_t RA2 {};
        std::size_t RA100 {};

    public:
        CommsDevCount() = default;
        explicit CommsDevCount(std::array<std::size_t, 9> counts);
        std::array<std::size_t, NUM_COMM_DEVICES> GetAsArray() const;
    };

    enum class CommunicationDevice
    {
        COMM_16,
        COMM_16S,
        COMM_88_88,
        COMM_DTS_M1,
        COMM_HG_5,
        COMM_HG_55,
        RA_15,
        RA_2,
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
}
#endif