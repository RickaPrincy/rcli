#include <RCli/Option.hpp>
#include <RCli/utils.hpp>
#include <regex>
#include <iostream>

using namespace RCli;

RCli::Option::Option(String options, Callback callback){
    options = Utils::clean_text(options);
    std::regex pattern(R"(-([a-zA-Z]),?--([a-zA-Z]+)?)");
    std::smatch matches;

    if(options.empty() || callback == nullptr || callback == NULL)
        Utils::quit_error("Option cannot be empty and callback cannot be null");

    if(std::regex_match(options, matches, pattern)){

    }else{
        Utils::quit_error("Invalid option. Valid examples include \"-c,--configure\" or \"-c\"");
    }
}