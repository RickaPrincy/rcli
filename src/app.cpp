#include <RCli/RCli.hpp> 
#include <RCli/utils.hpp> 
#include <TColor/TColor.hpp> 
#include <regex>

using namespace RCli;

App::App(String name, String version, String description){
    std::regex pattern("\\d+\\.\\d+\\.\\d+"); 
    name = Utils::clean_text(name);
    version = Utils::clean_text(version);
    description = Utils::clean_text(description);

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