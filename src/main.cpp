#include "RCli.h"
#include "RCli/add.h"
#include <iostream>
#include "external/TColor/TColor.hpp"

int RCli::add(int a, int b){
    TColor::write_endl(TColor::B_BLUE, "Hello");
    return a + b;
}

void RCli::say_hello(std::string name){
    std::cout << "Hello" << std::endl;
}