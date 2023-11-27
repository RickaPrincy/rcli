#ifndef __RCLI_UTILS__
#define __RCLI_UTILS__

    #include <RCli/types.hpp>

    namespace RCli{
        namespace Utils{
            void write_line(int number = 100);
            RCli::String get_one_value(RCli::String text, bool clean = true, bool required = false,RCli::String default_value = "");
            RCli::String get_line(bool do_endl = false);
            RCli::VectorString get_multiple_value();
        }
    }
#endif