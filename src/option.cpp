#include <RCli/Option.hpp>
#include <RCli/utils.hpp>
#include <regex>
#include <iostream>

using namespace RCli;

RCli::Option::Option(String options, String description, String key_name){
    options = Utils::clean_text(options);
    std::regex pattern(R"(-([a-zA-Z]),--([a-zA-Z]+))");
    std::regex shortOnly(R"(-([a-zA-Z]))"); 
    std::smatch matches;

    if(options.empty() || description.empty())
        Utils::quit_error("Option cannot be empty and callback cannot be null");
    
    _description = description;
    _key_name = key_name;
    
    if(std::regex_match(options, matches, pattern)){
        String shortValue = matches[1];
        String longValue = matches[2];
        _options.push_back("-" + shortValue);
        _options.push_back("--" + longValue);
    }else if(std::regex_match(options, matches, shortOnly)){
        String shortValue = matches[1];
        _options.push_back("-" + shortValue);
    }else{
        Utils::quit_error("Invalid option. Valid examples include \"-c,--configure\" or \"-c\"");
    }
}

String Option::get_key_if_matched(String value){
    if(matched(value)){
        return _key_name;
    }
    return "";
}

bool Option::matched(String option){
    return Utils::some(option, _options);
}

VectorString Option::get_values(){
    return _options;
}

String Option::get_description(){
    return _description;
}