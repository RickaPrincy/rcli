#include <iostream>
#include <ostream>

#include "utils.hpp"

using namespace rcli;

void rcli::Utils::print_as_key_value(std::string key, std::string value) {
    std::cout << key << ": " << value << "\n";
}

void rcli::Utils::log_error(std::string message) {
    std::cout << "[ ERROR ]: " << message << std::endl;
}
