#include <RCli/utils.hpp>
#include <TColor/TColor.hpp>
#include <iostream>

using namespace RCli;

String RCli::Utils::get_line(bool do_endl){
    String value;
    std::getline(std::cin, value);
    if(do_endl)
        std::cout << std::endl;
    return value;
}