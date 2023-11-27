#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <iostream>

using namespace RCli;

String RCli::Utils::get_line(bool do_endl){
    String value;
    TColor::set_color(TColor::YELLOW);
    std::getline(std::cin, value);
    TColor::set_color(TColor::BLUE);

    if(do_endl)
        std::cout << std::endl;
    return value;
}