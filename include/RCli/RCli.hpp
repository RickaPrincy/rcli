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
        String get_value_list(OptionValue config, VectorString options, bool ignore_case = false);
        bool get_boolean(String text, bool default_value = true);
    }
#endif
