#pragma once

#include <string>
#include <vector>

namespace rcli {
    namespace Utils {

        // for string manipulation
        std::string repeat(std::string text, int number = 100);
        std::string join(const std::vector<std::string> &values, std::string separator = ",");
        std::string uppercase(const std::string text);
        std::string lowercase(const std::string text);
        bool some(
            std::string text, const std::vector<std::string> &values, bool ignore_case = false);
        bool compare_ignore_case(std::string text, std::string text2);
        std::string clean_text(const std::string text, char symbol = ' ');

        // Other
        void print_as_key_value(std::string key, std::string value);
        std::string get_line(bool do_endl = false);
    }  // namespace Utils
}  // namespace rcli
