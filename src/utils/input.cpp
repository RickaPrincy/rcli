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

String RCli::Utils::get_one_value(String text, bool clean, bool required, String default_value){
    String message{text};
    
    if(default_value != "")
        message + " (default: " + default_value + " )";

    TColor::write(TColor::BLUE, message + " : ");
    TColor::set_color(TColor::YELLOW);
    String value = Utils::get_line(true);

    if(clean)
        Common::clean_text(value);
    if(default_value != "")
        value = default_value;
    if(required && value.empty()){
        TColor::write_endl(TColor::BLUE, text + " is Required");
        return Utils::get_one_value(text, clean, required, default_value);
    }
    return value;
}