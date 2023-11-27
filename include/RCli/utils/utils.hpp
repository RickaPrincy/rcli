#ifndef __RCLI_UTILS__
#define __RCLI_UTILS__

    #include <RCli/types.hpp>
    #include <RCli/utils/OptionValue.hpp>

    namespace RCli{
        namespace Utils{
            void write_line(int number = 100);
            RCli::String get_one_value(OptionValue option);
            RCli::VectorString get_multiple_value(std::vector<OptionValue> options);
            RCli::String get_line(bool do_endl = false);
        }
    }
#endif