#include <iostream>

#include "utils.hpp"

std::string rcli::Utils::get_line(bool do_endl) {
    std::string value;
    std::getline(std::cin, value);
    if (do_endl) std::cout << std::endl;
    return value;
}
