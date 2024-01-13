#include <iostream>
#include <rcli/rcli.hpp>
#include "utils/utils.hpp" 

void rcli::sayHello(std::string name) {
    std::vector<int> test{1,4,7};
    std::cout << rcli::join(test, "-") << std::endl;
}
