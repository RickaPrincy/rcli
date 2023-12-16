#include <RCli/Option.hpp>
#include <RCli/utils.hpp>
#include <regex>
#include <iostream>

using namespace RCli;

RCli::Option::Option(String options, Callback callback){
    options = Utils::clean_text(options);
    std::regex pattern(R"(-([a-zA-Z]),--([a-zA-Z]+))");
    std::regex shortOnly(R"(-([a-zA-Z]))"); 
    std::smatch matches;

    if(options.empty() || callback == nullptr || callback == NULL)
        Utils::quit_error("Option cannot be empty and callback cannot be null");
    
    _callback = callback;
    
    if(std::regex_match(options, matches, pattern)){
        _options.push_back(matches[1]);
        _options.push_back(matches[2]);
    }else if(std::regex_match(options, matches, shortOnly)){
        _options.push_back(matches[1]);
    }else{
        Utils::quit_error("Invalid option. Valid examples include \"-c,--configure\" or \"-c\"");
    }
}

bool Option::call_if_matched(String option){
    if(matched(option)){
        _callback();
        return true;
    }
    return false;
}

bool Option::matched(String option){
    return Utils::some(option, _options);
}

VectorString Option::get_values(){
    return _options;
}