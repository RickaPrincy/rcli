#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <RCli/Config.hpp>

using namespace RCli;

void Utils::quit_error(String message){
    TColor::write_endl(Config::_error_color, message);
    exit(EXIT_FAILURE);
}