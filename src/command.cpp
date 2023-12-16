#include <RCli/Command.hpp>
#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>

using namespace RCli;

Command::Command(String name, String description, Callback callback){
    _name = _name;
    _description = _description;
    _callback = callback;
    // Option help("-h,--help","Print help", [&](){ print_help(); });
    // add_option(help);
}

String Command::get_name(){
    return _name;
}

String Command::get_description(){
    return _description;
}

bool Command::matched(String text){
    return _name == text;
}

bool Command::call_if_matched(String text){
    if(matched(text)){
        _callback();
        return true;
    }
    return false;
}

void Command::print_help(bool is_subcommand){
    if(!is_subcommand){
        Utils::write_line();
        Utils::write_key_value("Command", _name);
    }
     
    Utils::write_key_value("Description", _description);
    
    if(!_subcommands.empty()){
        TColor::write_endl(TColor::BLUE, "\nCommands:");
        
        for(auto command: _subcommands){
            Utils::write_key_value("\t" + command.get_name(), command.get_description());
        }
    }
    
    if(!_options.empty()){
        TColor::write_endl(TColor::BLUE, "\nOptions:");
        
        for(auto option: _options){
            String optionValue = Utils::join(option.get_values()," or " );
            Utils::write_key_value("\t" + optionValue, option.get_description());
        }
    }

    Utils::write_line();
}

void RCli::Command::add_option(Option new_option){
    _options.push_back(new_option);
}

void RCli::Command::add_options(std::vector<Option> options){
    for(auto option: options){
        add_option(option);
    }
}

void RCli::Command::add_subcommand(Command new_command){
    _subcommands.push_back(new_command);
}

void RCli::Command::add_subcommands(std::vector<Command> commands){
    for(auto command: commands){
        add_subcommand(command);
    }
}