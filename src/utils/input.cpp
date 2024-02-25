#include <iostream>

#include "TColor/TColor.hpp"
#include "utils.hpp"

std::string rcli::Utils::get_line(bool do_endl) {
    std::string value;
    TColor::set_color(TColor::WHITE);
    std::getline(std::cin, value);
    if (do_endl) std::cout << std::endl;
    return value;
}
