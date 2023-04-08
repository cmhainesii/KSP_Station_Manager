#include "include/menu.hpp"
#include <sstream>

string Menu::getMenuText()
{
    std::stringstream ss;

    ss << "Main Menu" << std::endl << std::endl;

    ss << "1) Load Stations from Disk" << std::endl;
    ss << "2) Write Stations to Disk" << std::endl;
    ss << "3) Add New Station" << std::endl;
    ss << "4) Delete Station" << std::endl;
    ss << "5) List All Stations" << std::endl;
    ss << "q) Quit" << std::endl << std::endl;

    return ss.str();
}