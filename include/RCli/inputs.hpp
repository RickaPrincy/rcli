#ifndef __RCLI_INPUTS__
#define __RCLI_INPUTS__

    #include <RCli/types.hpp>
    
    namespace RCli{
        RCli::String ask_input_value(InputConfig config);
        RCli::VectorString ask_inputs_values(std::vector<InputConfig> configs);
        String ask_value_in_list(InputConfig config, VectorString options, bool ignore_case = false);
        bool ask_boolean(String text, bool default_value = true);
        RCli::String ask_value_in_options(String text, VectorString options);
    }
#endif
