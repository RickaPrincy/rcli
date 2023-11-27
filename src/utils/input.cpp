#include <RCli/utils/utils.hpp>
#include <RCli/common/common.hpp>
#include <TColor/TColor.hpp>
#include <iostream>

using namespace RCli;

String RCli::Utils::get_line(bool do_endl){
    String value;
    std::getline(std::cin, value);
    if(do_endl)
        std::cout << std::endl;
    return value;
}

String RCli::Utils::get_one_value(OptionValue option){
    String message{option._text};
    
    if(option._default != "")
        message = message + " (default: \"" + option._default + "\" )";

    TColor::write(TColor::BLUE, message + " : ");
    TColor::set_color(TColor::YELLOW);
    String value = Utils::get_line();

    if(option._clean)
        Common::clean_text(value);
    if(option._default != "" && value.empty())
        value = option._default;
    if(option._required && value.empty()){
        TColor::write_endl(TColor::RED, "[ REQUIRED ]: " + option._text);
        return Utils::get_one_value(option);
    }
    return value;
}

VectorString Utils::get_multiple_value(std::vector<OptionValue> options){
    VectorString results;
    for(const auto option: options){
        results.push_back(Utils::get_one_value(option));
    }
    return results;
}