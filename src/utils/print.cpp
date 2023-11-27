#include <RCli/utils/utils.hpp>
#include <RCli/common/common.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

void RCli::Utils::write_line(int number){
    TColor::write_endl(TColor::BLUE, Common::repeat("*", number));
}