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
                
                void print_help();
                bool matched(String text);
                bool call_if_matched(String text);
            public:
                String get_name();
                String get_description();
                Command(String name, String description, Callback callback);
        };
    }

#endif