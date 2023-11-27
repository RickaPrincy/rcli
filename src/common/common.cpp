#include <RCli/common.hpp>
#include <string>

using namespace RCli;

RCli::String RCli::Common::repeat(RCli::String text, int number = 100){
    return number < 1 ? text : text + Common::repeat(text, --number);
}

void RCli::Common::clean_text(RCli::String &text, RCli::String symbol){
    text.erase(std::remove(text.begin(), text.end(), symbol), text.end());
}