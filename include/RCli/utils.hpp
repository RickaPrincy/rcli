#ifndef __RCLI_UTILS__
#define __RCLI_UTILS__

    #include <RCli/types.hpp>

    namespace RCli{
        namespace Utils{
            RCli::String repeat(RCli::String text, int number = 100);
            RCli::String join(VectorString values, String separator = ",");
            RCli::String uppercase(RCli::String text);
            RCli::String lowercase(RCli::String text);
            bool some(RCli::String text, VectorString values, bool ignore_case = false);
            bool compare_ignore_case(RCli::String text, RCli::String text2);
            void clean_text(RCli::String &text, char symbol = ' ');
            void write_line(int number = 100);
            RCli::String get_line(bool do_endl = false);
        }
    }
#endif