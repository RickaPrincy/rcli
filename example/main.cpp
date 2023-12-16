#include <RCli/RCli.hpp>
#include <iostream>

void sayHello(){
    std::cout << "hello" << std::endl;
}

int main(int argc, char const *argv[]){
    RCli::Option option("-c,  --configure");
    option.call_if_valid("c");
    option.call_if_valid("configure");
    return 0;
}
