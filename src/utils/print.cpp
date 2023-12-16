#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

void RCli::Utils::write_line(int number){
    TColor::write_endl(TColor::BLUE, Utils::repeat("*", number));
}

void RCli::Utils::write_key_value(String key, String value){
    TColor::write(TColor::BLUE, key + ": ");
    TColor::write_endl(TColor::YELLOW, value);
}
