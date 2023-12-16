#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

void Utils::quit_error(String message){
    TColor::write_endl(TColor::RED, message);
    exit(EXIT_FAILURE);
}