#ifndef __RCLI_APP__
#define __RCLI_APP__
    
    #include <RCli/Command.hpp>
    #include <RCli/Option.hpp>
    #include <RCli/inputs.hpp>
    
    namespace RCli{
        class App: public RCli::Command{
            public:
                //Attributes
                RCli::String _version;

                //Constructors
                App(RCli::String name, RCli::String version, RCli::String description);

                //Methods
                void print_help();
                void add_option(Option new_option);
                void add_options(std::vector<Option> options);
        };
    }
#endif