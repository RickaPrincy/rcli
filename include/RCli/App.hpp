#ifndef __RCLI_APP__
#define __RCLI_APP__
    
    #include <RCli/Command.hpp>
    #include <RCli/Option.hpp>
    #include <RCli/inputs.hpp>
    
    namespace RCli{
        class App: public Command{
            public:
                //Attributes
                String _version;
                Callback callback;

                //Constructors
                App(String name, String version, String description);

                //Methods
                void print_help();
                void print_version();
                void run(int argc,const char *argv[]);
        };
    }
#endif