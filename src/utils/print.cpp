#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

void RCli::Utils::write_line(int number){
    TColor::write_endl(TColor::BLUE, Utils::repeat("*", number));
}