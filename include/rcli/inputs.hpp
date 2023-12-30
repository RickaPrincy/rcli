#ifndef __RCLI_INPUTS__
#define __RCLI_INPUTS__

    #include <string>
    #include <vector>
    #include "rcli/input_config.hpp"

    namespace rcli{
        std::string ask_input_value(InputConfig config);
        std::vector<std::string> ask_inputs_values(std::vector<InputConfig> configs);
        std::string ask_value_in_list(InputConfig config, std::vector<std::string> options, bool ignore_case = false);
        bool ask_boolean(std::string text, bool default_value = true);
        std::string ask_value_in_options(std::string text, std::vector<std::string> options);
    }
#endif
