#include <RCli/utils.hpp>
#include <string>

using namespace RCli;

RCli::String RCli::Utils::repeat(String text, int number){
    return number < 1 ? text : text + Utils::repeat(text, --number);
}

void RCli::Utils::clean_text(String &text, char symbol){
    text.erase(std::remove(text.begin(), text.end(), symbol), text.end());
}