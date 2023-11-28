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

        RCli::String ask_input_value(OptionValue option);
        RCli::VectorString ask_inputs_values(std::vector<OptionValue> options);
        String ask_value_in_list(OptionValue config, VectorString options, bool ignore_case = false);
        bool ask_boolean(String text, bool default_value = true);
        RCli::String ask_value_in_options(String text, VectorString options);
    }
#endif
