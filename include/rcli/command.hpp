#ifndef __RCLI_COMMAND__
#define __RCLI_COMMAND__

    #include <string>
    #include <functional>
    #include <vector>
    #include "rcli/option.hpp"

    namespace RCli{
        class Command;
        
        using Callback = std::function<void(Command*)>;
        
        class Command{
            protected:
                std::string _name, _description,  _command_suffix;
                Callback _callback;
                std::vector<RCli::Option> _options;
                std::vector<RCli::Command> _subcommands;
                Mapstd::string _options_values, _informations;
                void parse(int argc,const char *argv[], int start);
            public:
                Command(std::string name, std::string description, Callback callback, bool subcommand = true);
                
                bool matched(std::string text);
                bool call_if_matched(std::string text);
                void print_help(bool is_subcommand = true);
                
                std::string get_name();
                std::string get_description();
                std::string get_option_value(std::string key);
                
                std::string get_suffix();
                void set_suffix(std::string suffix);

                void add_option(Option new_option);
                void add_option(std::string options, std::string description, std::string key_name);
                void add_options(std::vector<Option> options);
                void add_subcommand(Command new_command);
                void add_subcommands(std::vector<Command> commands);
                void add_informations(Mapstd::string informations);
                Command& operator=(const Command& other); 
        };
    }

#endif