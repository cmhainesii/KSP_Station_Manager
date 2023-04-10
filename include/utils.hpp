#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include "celestial_body.hpp"
#include "space_station.hpp"
#include <vector>

using std::string;
using std::vector;

class Utility {

public:
    static string BoolToYesNo(bool input);
    static string PlanetToString(CelestialBody planet);
    static string numberWithCommas(size_t input);
    static string PrettyFormatList(const vector<KSP_SM::CommunicationDevice>& list);
    static string PrettyFormatList(const vector<KSP_SM::DockingPort>& list);
};

#endif