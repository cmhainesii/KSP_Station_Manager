#include "include/menu.hpp"
#include <sstream>

string Menu::getMenuText()
{
    std::stringstream ss;

    ss << "Main Menu" << std::endl << std::endl;

    ss << "R -> Read Stations from Disk" << std::endl;
    ss << "W -> Write Stations to Disk" << std::endl;
    ss << "A -> Add New Station" << std::endl;
    ss << "D -> Delete Station" << std::endl;
    ss << "L -> List All Stations" << std::endl;
    ss << "Q -> Quit" << std::endl << std::endl;

    return ss.str();
}