#ifndef __RCLI_COMMON__
#define __RCLI_COMMON__

    #include <RCli/types.hpp>

    namespace RCli{
        namespace Common{
            RCli::String repeat(RCli::String text, int number = 100);
            void clean_text(RCli::String &text, char symbol = ' ');
        }
    }
#endif