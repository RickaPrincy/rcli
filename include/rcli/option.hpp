#pragma once

#include <rcli/types.hpp>
#include <string>
#include <vector>

namespace rcli {

    template <typename T>
    class Option {
    public:
        T value;
        std::string description;
        std::vector<std::string> options;

        Option(std::string options, std::string description);
        Option(std::string options, std::string description, T value);
    };

}  // namespace rcli
