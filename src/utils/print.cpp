#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <RCli/Config.hpp>

using namespace RCli;

void RCli::Utils::write_key_value(String key, String value, bool is_info){
    auto key_color = is_info ? Config::_info_key_color : Config::_input_key_color;
    auto value_color = is_info ? Config::_input_value_color: Config::_input_value_color;

    TColor::write(key_color, key + ": ");
    TColor::write_endl(value_color, value);
}
