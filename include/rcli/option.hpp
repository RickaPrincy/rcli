#pragma once

#include <string>
#include <vector>

namespace rcli {
    class Option {
    private:
        std::vector<std::string> _options;
        std::string _description, _key_name;

    public:
        std::string get_description();
        std::string get_key_if_matched(std::string value);

        Option(std::string options, std::string description, std::string key_name);
    };
}  // namespace rcli
