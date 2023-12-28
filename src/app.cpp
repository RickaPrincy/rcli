#include <regex>
#include <RCli/RCli.hpp> 
#include <RCli/utils.hpp> 
#include <TColor/TColor.hpp> 
#include <RCli/Config.hpp>

using namespace RCli;

//default color
String 
    Config::_input_key_color = TColor::WHITE,
    Config::_input_value_color = TColor::WHITE,
    Config::_error_color = TColor::WHITE,
    Config::_info_value_color = TColor::WHITE,
    Config::_info_key_color = TColor::B_WHITE;

App::App(String name, String version, String description): Command(name, description, [](Command*){}, false){
    std::regex pattern("\\d+\\.\\d+\\.\\d+"); 
    version = Utils::clean_text(version);
    if(!name.empty() && !version.empty() && !description.empty()){
        if(!std::regex_match(version, pattern)){
            Utils::quit_error("[ ERROR ]: \"version\" must be \"x.x.x\" (x are number)");
        }
        _name = name;
        _version = version;
        _description = description;
    }else{
        Utils::quit_error("[ ERROR ]: \"name\", \"version\" and \"description\" are required");
    }
}

void App::print_help(){
    print_version();
    Command::print_help(false);
}

void RCli::App::run(int argc,const char *argv[]){
    if(argc == 1){
        App::print_help();
        return;
    }

    String arg = argv[1];
    if(arg == "-v" || arg == "--version"){
        print_version();
        return;
    }
    
    parse(argc, argv, 0);
}

void App::print_version(){
    Utils::write_key_value("Name", _name, true);
    Utils::write_key_value("Version", _version, true);
    for(const auto &[key, value]: _informations) {
        Utils::write_key_value(key, value, true);
    }
}