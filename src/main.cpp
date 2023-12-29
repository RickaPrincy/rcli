#include "RCli/add.h"
#include <iostream>
#include "TColor/TColor.hpp"

int RCli::add(int a, int b){
    TColor::write_endl(TColor::B_BLUE, "Hello");
    return a + b;
}