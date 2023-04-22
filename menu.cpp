#include "include/menu.hpp"
#include <sstream>

string Menu::GetMainMenuText()
{
    std::stringstream ss;

    ss << "Main Menu" << std::endl << std::endl;

    ss << "R -> Read Stations from Disk" << std::endl;
    ss << "W -> Write Stations to Disk" << std::endl;
    ss << "A -> Add New Station" << std::endl;
    ss << "M -> Manage Station" << std::endl;
    ss << "D -> Delete Station" << std::endl;
    ss << "L -> List All Stations" << std::endl;
    ss << "Q -> Quit" << std::endl << std::endl;

    return ss.str();
}

string Menu::GetMangeStationMenuText()
{
    std::stringstream ss;

    ss << "Manage Station Options\n\n";
    ss << "A -> Add Kerbal\n";
    ss << "R -> Remove Kerbal\n";
    ss << "E -> Edit Capacity\n";
    ss << "F -> Finish Managing Stations\n\n";
    ss << "Enter Your Selection: ";

    return ss.str();
}