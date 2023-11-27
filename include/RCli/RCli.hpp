#ifndef __RCLI_LIB__
#define __RCLI_LIB_

    #include <RCli/types.hpp>
    
    namespace RCli{
        class App{
            private:
                String name, version, description;
            public:
                App(String name, String version, String description);
                void printVersion();
        };
    }
#endif
