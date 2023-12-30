#include "rcli/utils.hpp"
#include "TColor/TColor.hpp"
#include "rcli/color_config.hpp"
#include <iostream>

using namespace rcli;

std::string rcli::Utils::get_line(bool do_endl, std::string color){
    std::string value;
    TColor::set_color(color);
    std::getline(std::cin, value);
    TColor::set_color(ColorConfig::_input_value_color);

    if(do_endl)
        std::cout << std::endl;
    return value;
}