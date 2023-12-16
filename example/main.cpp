#include <RCli/RCli.hpp>
#include <iostream>

using namespace RCli;

int main(int argc, const char *argv[]){
    RCli::App templi("templi", "1.9.5", "Generate cool application");
    templi.run(argc, argv);
    return 0;
}
