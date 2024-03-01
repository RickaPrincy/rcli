#include <TColor/TColor.hpp>
#include <rcli/color_config.hpp>

#include "utils.hpp"

using namespace rcli;

void rcli::Utils::print_as_key_value(std::string key, std::string value) {
    TColor::write(ColorConfig::key, key + ": ");
    TColor::write(ColorConfig::value, value + "\n");
}

void rcli::Utils::log_error(std::string message) {
    TColor::write(TColor::B_RED, " [ ERROR ]: " + message + "\n");
}
