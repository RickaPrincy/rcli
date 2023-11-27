#include <RCli/utils/utils.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    RCli::String value =  RCli::Utils::get_one_value("Project Name", true, true);

    std::cout << value << std::endl;
    return 0;
}
