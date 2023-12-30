#include "rcli/option.hpp"
#include "rcli/utils.hpp"
#include <regex>
#include <iostream>

using namespace rcli;

rcli::Option::Option(std::string options, std::string description, std::string key_name){
    options = Utils::clean_text(options);
    std::regex pattern(R"(-([a-zA-Z]),--([a-zA-Z]+))");
    std::regex short_only(R"(-([a-zA-Z]))"); 
    std::smatch matches;

    if(options.empty() || description.empty())
        Utils::quit_error("Option cannot be empty and callback cannot be null");
    
    _description = description;
    _key_name = key_name;
    
    if(std::regex_match(options, matches, pattern)){
        std::string short_value = matches[1];
        std::string long_value = matches[2];
        _options.push_back("-" + short_value);
        _options.push_back("--" + long_value);
    }else if(std::regex_match(options, matches, short_only)){
        std::string short_value = matches[1];
        _options.push_back("-" + short_value);
    }else{
        Utils::quit_error("Invalid option. Valid examples include \"-c,--configure\" or \"-c\"");
    }
}

std::string Option::get_key_if_matched(std::string value){
    if(matched(value)){
        return _key_name;
    }
    return "";
}

bool Option::matched(std::string option){
    return Utils::some(option, _options);
}

std::vector<std::string> Option::get_values(){
    return _options;
}

std::string Option::get_description(){
    return _description;
}