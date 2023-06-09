#include "include/utils.hpp"
#include <sstream>
#include <iostream>

using namespace KSP_SM;

string Utility::BoolToYesNo(bool input)
{
    return input ? "Yes" : "No";
}

string Utility::numberWithCommas(size_t input)
{
    string result = std::to_string(input);
    if (result.size() < 3)
        return result;
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

string Utility::PrettyFormatList(const vector<KSP_SM::CommunicationDevice>& list)
{
    size_t i = 0;
    std::stringstream ss;
    char tab = '\t';

    for (auto current : list)
    {
        ss << tab << KSP_SM::SpaceStationBuilder::SpaceStation::CommsDeviceToString(current);
        if(++i % 4 == 0)
        {
            ss << '\n';
        }
    }
    if (i % 4 != 0)
    {
        ss << '\n';
    }

    return ss.str();
}

string Utility::PrettyFormatList(const vector<DockingPort>& list)
{
    size_t i = 0;
    std::stringstream ss;
    char tab = '\t';

    for (auto current : list)
    {
        ss << tab << SpaceStationBuilder::SpaceStation::DockingPortToString(current);
        if (++i % 4 == 0)
        {
            ss << '\n';
        }
    }
    if (i % 4 != 0)
    {
        ss << '\n';
    }

    return ss.str();
}

void Utility::ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utility::PressEnterToContinue()
{
    string temporary;
    std::cout << "Press any key to continue...";
    std::getline(std::cin, temporary);
    std::cout << "\n\n";
}