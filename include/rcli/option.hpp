#pragma once

#include <string>
#include <vector>

namespace rcli {
    class Option {
    protected:
        std::vector<std::string> _options;
        std::string _description, _key_name;
        std::string _base_names;

    public:
        std::string get_description();
        std::string get_base_names();
        std::string get_key_if_matched(std::string value);
        Option(std::string options, std::string description, std::string key_name);
    };
}  // namespace rcli
