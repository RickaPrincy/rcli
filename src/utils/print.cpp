#include "rcli/utils.hpp"
#include "TColor/TColor.hpp"
#include "rcli/color_config.hpp"

using namespace rcli;

void rcli::Utils::write_key_value(std::string key, std::string value, bool is_info){
    auto key_color = is_info ? ColorConfig::_info_key_color : ColorConfig::_input_key_color;
    auto value_color = is_info ? ColorConfig::_input_value_color: ColorConfig::_input_value_color;

    TColor::write(key_color, key + ": ");
    TColor::write_endl(value_color, value);
}