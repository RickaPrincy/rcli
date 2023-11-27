#ifndef __RCLI_LIB__
#define __RCLI_LIB__

    #include <RCli/types.hpp>
    
    namespace RCli{
        class App{
            private:
                RCli::String  name, version, description;
            public:
                App(RCli::String name, RCli::String version, RCli::String description);
                void print_version();
        };

        RCli::String get_one_value(OptionValue option);
        RCli::VectorString get_multiple_value(std::vector<OptionValue> options);
    }
#endif
