#include <RCli/utils.hpp>
#include <cctype>

using namespace RCli;

bool RCli::Utils::some(RCli::String text, VectorString values, bool ignore_case){
    return std::find_if(values.begin(), values.end(), [&](const std::string &element) {
        return ignore_case ? compare_ignore_case(text, element): text == element;
    }) != values.end();
}

bool RCli::Utils::compare_ignore_case(RCli::String text, RCli::String text2){
    return std::equal(
        text.begin(), text.end(),
        text2.begin(), text2.end(),
        [](char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
        }
    );
}

RCli::String RCli::Utils::uppercase(RCli::String text){
    std::string result = text;
    for (char &c : result)
        c = std::toupper(c);
    return result;
}

RCli::String RCli::Utils::lowercase(RCli::String text){
    std::string result = text;
    for (char &c : result)
        c = std::tolower(c);
    return result;
}


RCli::String RCli::Utils::repeat(String text, int number){
    return number < 1 ? text : text + Utils::repeat(text, --number);
}

void RCli::Utils::clean_text(String &text, char symbol){
    text.erase(std::remove(text.begin(), text.end(), symbol), text.end());
}

String RCli::Utils::join(VectorString values, String separator){
    return std::accumulate(
        values.begin() + 1, 
        values.end(),
        values.front(), 
        [separator](const String &acc, const String &element) {
            return acc + separator + element;
        }
    );
}