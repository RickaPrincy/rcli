#include <iostream>
#include <rcli/rcli.hpp>

void rcli::sayHello(std::string name) {
    std::cout << "Hello " << name << std::endl;
}
