#include <iostream>

#include "utils.hpp"

void rcli::Utils::print_as_key_value(std::string key, std::string value) {
    std::cout << key << ": " << value << "\n";
}
