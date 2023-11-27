#include <RCli/RCli.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    if(RCli::get_boolean("Play chess ? ", false))
        std::cout << "ok" << std::endl;
    else
        std::cout << "tsy ok" << std::endl;
    return 0;
}
