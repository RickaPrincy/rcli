#ifndef __RCLI_UTILS__
#define __RCLI_UTILS__

    #include <string>
    #include <vector>
    #include "rcli/color_config.hpp"

    namespace rcli{
        namespace Utils{

            //for string manipulation
            std::string repeat(std::string text, int number = 100);
            std::string join(std::vector<std::string> values, std::string separator = ",");
            std::string uppercase(std::string text);
            std::string lowercase(std::string text);
            bool some(std::string text, std::vector<std::string> values, bool ignore_case = false);
            bool compare_ignore_case(std::string text, std::string text2);
            std::string clean_text(std::string text, char symbol = ' ');

            //Other 
            void write_key_value(std::string key, std::string value, bool is_info = false);
            std::string get_line(bool do_endl = false, std::string color = ColorConfig::_input_value_color);
            void quit_error(std::string message);
        }
    }
#endif