#include <RCli/utils/utils.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    RCli::VectorString values =  RCli::Utils::get_multiple_value({
        RCli::OptionValue("Project Name", true, true, "name"),
        RCli::OptionValue("version", true),
        RCli::OptionValue("Author", true, true),
        RCli::OptionValue("Description", false, true)
    });

    for(const auto value: values){
        std:: cout << value << std::endl;
    }
    return 0;
}
