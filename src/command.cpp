#include <RCli/Command.hpp>
#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <RCli/Config.hpp>

using namespace RCli;

Command& Command::operator=(const Command& other) {
    if (this != &other) { 
        _name = other._name;
        _description = other._description;
        _command_suffix = other._command_suffix;
        _options = other._options;
        _subcommands = other._subcommands;
        _options_values = other._options_values;
    }
    return *this;
}

Command::Command(String name, String description, Callback callback, bool subcommand){
    _name = name;
    _description = description;
    _command_suffix = name;

    if(!subcommand) {
        Option version("-v, --version","Show version", "version");
        add_option(version);
    }
    Option help("-h,--help","Show this help", "help");
    add_option(help);
    
    _callback = callback;
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
        _callback(this);
        return true;
    }
    return false;
}

void Command::print_help(bool is_subcommand){
    if(is_subcommand){
        Utils::write_key_value("Command", _name, true);
    }
     
    Utils::write_key_value("Description", _description, true);

    Utils::write_key_value("\nUsage", _command_suffix + " <command> <<option> <option_value>>", true);
    
    if(!_subcommands.empty()){
        TColor::write_endl(Config::_info_key_color, "\nCommands:");
        
        for(auto command: _subcommands){
            Utils::write_key_value("\t" + command.get_name(), command.get_description(), true);
        }
    }
    
    if(!_options.empty()){
        TColor::write_endl(Config::_info_key_color, "\nOptions:");
        
        for(auto option: _options){
            String optionValue = Utils::join(option.get_values()," or " );
            Utils::write_key_value("\t" + optionValue, option.get_description(), true);
        }
    }
}

void RCli::Command::add_option(String options, String description, String key_name){
    _options.push_back(Option(options, description, key_name));
}

void RCli::Command::add_option(Option new_option){
    _options.push_back(new_option);
}

void RCli::Command::add_options(std::vector<Option> options){
    for(auto option: options){
        add_option(option);
    }
}

String RCli::Command::get_suffix(){
    return _command_suffix;
}

void RCli::Command::set_suffix(String suffix){
    _command_suffix = suffix;
}

void RCli::Command::add_subcommand(Command new_command){
    if(!get_suffix().empty()){
        new_command.set_suffix(get_suffix() + " " + new_command.get_suffix());
    }
    _subcommands.push_back(new_command);
}

void RCli::Command::add_subcommands(std::vector<Command> commands){
    for(auto command: commands){
        add_subcommand(command);
    }
}

String Command::get_option_value(String key){
    if(_options_values.find(key) == _options_values.end()){
        return "";
    }
    return _options_values.at(key);
}

void RCli::Command::parse(int argc,const char *argv[], int start){
    if(start + 1 < argc){
        String command_or_option = argv[start + 1];
        
        if(command_or_option == "--help" || command_or_option == "-h"){
            print_help();
            exit(EXIT_SUCCESS);
        }

        if(command_or_option.find("-") == 0){
            bool valid_option = false;
            if(start + 2 >= argc){
                print_help();
                exit(EXIT_SUCCESS);
            }
            for(auto option: _options){
                String key_name = option.get_key_if_matched(command_or_option);
                
                if(key_name.empty()){
                    continue;
                }
                
                _options_values.insert(std::make_pair(key_name, argv[start + 2]));
                valid_option = true;
                break;
            }
            
            if(!valid_option){
                print_help();
                exit(EXIT_SUCCESS);
            }else{
                parse(argc, argv, start + 2);
                exit(EXIT_SUCCESS);
            }
        }else{
            for(auto command: _subcommands){
                if(command.matched(command_or_option)){
                    command.parse(argc, argv, start + 1);
                    exit(EXIT_SUCCESS);
                }
            }
            print_help();
            exit(EXIT_SUCCESS);
        }
    }

    _callback(this);
}

void Command::add_informations(MapString informations){
    for(auto information : informations)
        _informations.insert(std::make_pair(information.first, information.second));
}