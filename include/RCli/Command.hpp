#ifndef __RCLI_COMMAND__
#define __RCLI_COMMAND__

    #include <RCli/Option.hpp>

    namespace RCli{
        class Command;
        
        using Callback = std::function<void(Command*)>;
        
        class Command{
            protected:
                String _name, _description,  _command_suffix;
                Callback _callback;
                std::vector<RCli::Option> _options;
                std::vector<RCli::Command> _subcommands;
                MapString _options_values;
                void parse(int argc,const char *argv[], int start);
                Command(String name, String description, bool subcommand);
            public:
                Command(String name, String description, Callback callback);
                
                bool matched(String text);
                bool call_if_matched(String text);
                void print_help(bool is_subcommand = true);
                
                String get_name();
                String get_description();
                String get_option_value(String key);
                
                String get_suffix();
                void set_suffix(String suffix);

                void add_option(Option new_option);
                void add_options(std::vector<Option> options);
                void add_subcommand(Command new_command);
                void add_subcommands(std::vector<Command> commands);
                
                Command& operator=(const Command& other); 
        };
    }

#endif