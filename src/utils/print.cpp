#include <RCli/utils.hpp>
#include <RCli/common.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

void RCli::Utils::write_line(int number = 100){
    TColor::write_endl(TColor::BLUE, Common::repeat("*", number));
}