#include <RCli/common/common.hpp>
#include <string>

using namespace RCli;

RCli::String RCli::Common::repeat(RCli::String text, int number){
    return number < 1 ? text : text + Common::repeat(text, --number);
}

void RCli::Common::clean_text(RCli::String &text, char symbol){
    text.erase(std::remove(text.begin(), text.end(), symbol), text.end());
}