#include "include/utils.hpp"

string Utility::BoolToYesNo(bool input)
{
    return input ? "Yes" : "No";
}

string Utility::numberWithCommas(size_t input)
{
    string result = std::to_string(input);
    for (auto i = result.size() - 3; i > 0; i -=3)
    {
        result.insert(i, ",");
    }

    return result;
}

string Utility::PlanetToString(CelestialBody planet)
{
    switch(planet)
    {

    case CelestialBody::KERBOL:
        return "Kerbol";

    case CelestialBody::MOHO:
        return "Moho";

    case CelestialBody::EVE:
        return "Eve";
    case CelestialBody::GILLY:
        return "Gilly";

    case CelestialBody::KERBIN:
        return "Kerbin";
    case CelestialBody::MUN:
        return "Mun";
    case CelestialBody::MINMUS:
        return "Minmus";

    case CelestialBody::DUNA:
        return "Duna";
    case CelestialBody::IKE:
        return "Ike";
    case CelestialBody::DRES:
        return "Dres";
    case CelestialBody::JOOL:
        return "Juul";
    case CelestialBody::LAYTHE:
        return "Laythe";
    case CelestialBody::VALL:
        return "Vall";
    case CelestialBody::TYLO:
        return "Tylo";
    case CelestialBody::BOP:
        return "Bop";
    case CelestialBody::POL:
        return "Pol";
    case CelestialBody::ELOO:
        return "Eloo";
    default:
        return "Vulkin";
    }
}