#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <RCli/Config.hpp>
#include <iostream>

using namespace RCli;

String RCli::Utils::get_line(bool do_endl, String color){
    String value;
    TColor::set_color(color);
    std::getline(std::cin, value);
    TColor::set_color(Config::_input_value_color);

    if(do_endl)
        std::cout << std::endl;
    return value;
}