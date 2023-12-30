#include "rcli/utils.hpp"
#include "TColor/TColor.hpp"
#include "rcli/color_config.hpp"

using namespace rcli;

void Utils::quit_error(std::string message){
    TColor::write_endl(ColorConfig::_error_color, message);
    exit(EXIT_FAILURE);
}