#include <iostream>
#include "TColor/TColor.hpp"
#include "rcli/color_config.hpp"

using namespace rcli;

//default color
std::string
    ColorConfig::_input_key_color = TColor::WHITE,
    ColorConfig::_input_value_color = TColor::WHITE,
    ColorConfig::_error_color = TColor::WHITE,
    ColorConfig::_info_value_color = TColor::WHITE,
    ColorConfig::_info_key_color = TColor::B_WHITE;
