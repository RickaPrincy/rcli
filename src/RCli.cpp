#include <RCli/RCli.hpp>
#include <TColor/TColor.hpp>
#include <RCli/utils.hpp>

using namespace RCli;

String RCli::get_one_value(OptionValue option){
    String message{option._text};
    
    if(option._default != "")
        message = message + " (default: \"" + option._default + "\" )";

    TColor::write(TColor::BLUE, message + ":");
    String value = Utils::get_line();

    if(option._clean)
        Utils::clean_text(value);
    if(option._default != "" && value.empty())
        value = option._default;
    if(option._required && value.empty()){
        TColor::write_endl(TColor::RED, "[ REQUIRED ]: " + option._text);
        return get_one_value(option);
    }
    return value;
}

VectorString RCli::get_multiple_value(std::vector<OptionValue> options){
    VectorString results;
    for(const auto option: options){
        results.push_back(get_one_value(option));
    }
    return results;
}

String RCli::get_value_list(OptionValue config, VectorString options, bool ignore_case){
    String value = RCli::get_one_value(config);

    if(!Utils::some(value, options, ignore_case)){
        TColor::write_endl(TColor::RED, "[ NOT VALID ]: These are the expected values [ " + Utils::join(options, ", ") + " ]");
        RCli::get_value_list(config, options, ignore_case);
    }
    return value;
}

bool RCli::get_boolean(String text, bool default_value){
    OptionValue option_value(text, true, true, default_value ? "y" : "n");
    return Utils::lowercase(RCli::get_value_list(option_value, {"n","y"}, true)) == "y";
}