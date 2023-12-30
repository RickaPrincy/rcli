#include <rcli/utils.hpp>
#include <algorithm>
#include <cctype>
#include <numeric>

using namespace rcli;

bool rcli::Utils::some(std::string text, std::vector<std::string> values, bool ignore_case){
    return std::find_if(values.begin(), values.end(), [&](const std::string &element) {
        return ignore_case ? compare_ignore_case(text, element): text == element;
    }) != values.end();
}

bool rcli::Utils::compare_ignore_case(std::string text, std::string text2){
    return std::equal(
        text.begin(), text.end(),
        text2.begin(), text2.end(),
        [](char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
        }
    );
}

std::string rcli::Utils::uppercase(std::string text){
    std::string result = text;
    for (char &c : result)
        c = std::toupper(c);
    return result;
}

std::string rcli::Utils::lowercase(std::string text){
    std::string result = text;
    for (char &c : result)
        c = std::tolower(c);
    return result;
}


std::string rcli::Utils::repeat(std::string text, int number){
    return number < 1 ? text : text + Utils::repeat(text, --number);
}

std::string rcli::Utils::clean_text(std::string text, char symbol){
    text.erase(std::remove(text.begin(), text.end(), symbol), text.end());
    return text;
}

std::string rcli::Utils::join(std::vector<std::string> values, std::string separator){
    return std::accumulate(
        values.begin() + 1, 
        values.end(),
        values.front(), 
        [separator](const std::string &acc, const std::string &element) {
            return acc + separator + element;
        }
    );
}