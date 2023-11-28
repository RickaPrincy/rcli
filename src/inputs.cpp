#include <RCli/RCli.hpp>
#include <TColor/TColor.hpp>
#include <RCli/utils.hpp>

using namespace RCli;

String RCli::ask_input_value(OptionValue option){
    String message{option._text};
    
    if(option._default != "")
        message = message + " (default: \"" + option._default + "\" )";

    TColor::write(TColor::BLUE, message + ": ");
    String value = Utils::get_line();

    if(option._clean)
        Utils::clean_text(value);
    if(option._default != "" && value.empty())
        value = option._default;
    if(option._required && value.empty()){
        TColor::write_endl(TColor::RED, "[ REQUIRED ]: " + option._text);
        return RCli::ask_input_value(option);
    }
    return value;
}

VectorString RCli::ask_inputs_values(std::vector<OptionValue> options){
    VectorString results;
    for(const auto option: options){
        results.push_back(RCli::ask_input_value(option));
    }
    return results;
}

String RCli::ask_value_in_list(OptionValue config, VectorString options, bool ignore_case){
    String value = RCli::ask_input_value(config);

    if(!Utils::some(value, options, ignore_case)){
        TColor::write_endl(TColor::RED, "[ NOT VALID ]: These are the expected values [" + Utils::join(options, ", ") + "]");
        return RCli::ask_value_in_list(config, options, ignore_case);
    }
    return value;
}

bool RCli::ask_boolean(String text, bool default_value){
    OptionValue option_value(text, true, true, default_value ? "y" : "n");
    return Utils::lowercase(RCli::ask_value_in_list(option_value, {"n","y"}, true)) == "y";
}

String RCli::ask_value_in_options(String text, VectorString options){
    VectorString list_options;
    TColor::set_color(TColor::BLUE);
    for(size_t i = 0; i < options.size(); i++){
        std::cout <<  i + 1 << ") " << options.at(i) << std::endl;
        list_options.push_back(std::to_string(i + 1));
    }

    String value = RCli::ask_value_in_list(OptionValue(text, true), list_options);
    return options.at(std::stoi(value) - 1);
}