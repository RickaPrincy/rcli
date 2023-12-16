#ifndef __RCLI_COMMAND__
#define __RCLI_COMMAND__

    #include <RCli/Option.hpp>

    namespace RCli{
        class Command{
            protected:
                String _name, _description;
                Callback _callback;
                std::vector<RCli::Option> _options;
                std::vector<RCli::Command> _subcommands;
                
            public:
                Command(String name, String description, Callback callback);
                
                bool matched(String text);
                bool call_if_matched(String text);
                void print_help(bool is_subcommand = true);
                
                String get_name();
                String get_description();
                
                void add_option(Option new_option);
                void add_options(std::vector<Option> options);
                void add_subcommand(Command new_command);
                void add_subcommands(std::vector<Command> commands);
        };
    }

#endif