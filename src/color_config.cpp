#include <iostream>
#include "TColor/TColor.hpp"
#include "RCli/ColorConfig.hpp"

using namespace RCli;

//default color
std::string
    ColorConfig::_input_key_color = TColor::WHITE,
    ColorConfig::_input_value_color = TColor::WHITE,
    ColorConfig::_error_color = TColor::WHITE,
    ColorConfig::_info_value_color = TColor::WHITE,
    ColorConfig::_info_key_color = TColor::B_WHITE;
