#ifndef __RCLI_APP__
#define __RCLI_APP__
    #include <RCli/types.hpp>
    
    namespace RCli{
        class App{
            private:
                RCli::String  name, version, description;
            public:
                App(RCli::String name, RCli::String version, RCli::String description);
                void print_version();
        };
    }
#endif