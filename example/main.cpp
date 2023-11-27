#include <RCli/RCli.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    std::cout << RCli::ask_value_in_options("Project type",
    { "library", "executable" }) << std::endl;
}
