#ifndef __RCLI_APP__
#define __RCLI_APP__
    
    #include <string>    
    #include "rcli/command.hpp"

    namespace rcli{
        class App: public Command{
            public:
                std::string _version;
                Callback callback;
                
                App(std::string name, std::string version, std::string description);

                void print_help();
                void print_version();
                void run(int argc,const char *argv[]);
        };
    }
#endif