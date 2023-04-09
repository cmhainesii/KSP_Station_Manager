#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include "celestial_body.hpp"

using std::string;

class Utility {

public:
    static string BoolToYesNo(bool input);
    static string PlanetToString(CelestialBody planet);
    static string numberWithCommas(size_t input);
};

#endif