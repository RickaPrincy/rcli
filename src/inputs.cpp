#include <RCli/RCli.hpp>
#include <TColor/TColor.hpp>
#include <RCli/utils.hpp>

using namespace RCli;

String RCli::ask_input_value(InputConfig config){
    String message{config._text};
    
    if(config._default != "")
        message = message + " (default: \"" + config._default + "\" )";

    TColor::write(Config::_input_key_color, message + ": ");
    TColor::set_color(Config::_input_value_color);
    String value = Utils::get_line();

    if(config._clean)
        value = Utils::clean_text(value);
    if(config._default != "" && value.empty())
        value = config._default;
    if(config._required && value.empty()){
        TColor::write_endl(Config::_error_color, "[ REQUIRED ]: This is required");
        return RCli::ask_input_value(config);
    }
    return value;
}

VectorString RCli::ask_inputs_values(std::vector<InputConfig> configs){
    VectorString results;
    for(const auto config: configs){
        results.push_back(RCli::ask_input_value(config));
    }
    return results;
}

String RCli::ask_value_in_list(InputConfig config, VectorString options, bool ignore_case){
    String value = RCli::ask_input_value(config);

    if(!Utils::some(value, options, ignore_case)){
        TColor::write_endl(Config::_error_color, "[ NOT VALID ]: These are the expected values [" + Utils::join(options, ", ") + "]");
        return RCli::ask_value_in_list(config, options, ignore_case);
    }
    return value;
}

bool RCli::ask_boolean(String text, bool default_value){
    InputConfig config = InputConfig()
        .text(text)
        .default_value(default_value ? "y" : "n")
        .clean(true)
        .required(true);
    return Utils::lowercase(RCli::ask_value_in_list(config, {"n","y"}, true)) == "y";
}

String RCli::ask_value_in_options(String text, VectorString options){
    VectorString list_options;
    TColor::set_color(Config::_input_key_color);
    for(size_t i = 0; i < options.size(); i++){
        std::cout <<  i + 1 << ") " << options.at(i) << std::endl;
        list_options.push_back(std::to_string(i + 1));
    }

    InputConfig config = InputConfig().text(text).clean(true);
    
    String value = RCli::ask_value_in_list(config, list_options);
    return options.at(std::stoi(value) - 1);
}