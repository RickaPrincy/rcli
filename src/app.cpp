#include <RCli/RCli.hpp> 
#include <RCli/utils.hpp> 
#include <TColor/TColor.hpp> 
#include <regex>

using namespace RCli;

App::App(String name, String version, String description): Command(name, description, [](){}){
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

void RCli::App::print_help(){
    Utils::write_line();
    Utils::write_key_value("Name", _name);
    Utils::write_key_value("Version", _version);
    
    Command::print_help(false);
}