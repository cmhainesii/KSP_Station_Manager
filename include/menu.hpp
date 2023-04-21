#ifndef MENU_HPP
#define MENU_HPP

#include <string>

using std::string;
class Menu
{
  public:
    static string getMainMenuText();
    static string getMangeStationMenuText();

  private:
    static constexpr unsigned char indent_spaces = 4;
};

#endif