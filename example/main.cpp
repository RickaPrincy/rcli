#include <RCli/RCli.hpp>
#include <iostream>

using namespace RCli;

int main(int argc, char const *argv[]){
    RCli::App templi("templi", "1.9.5", "Generate cool application");
    templi.print_help();
    
    return 0;
}
