#include <RCli/RCli.hpp>
#include <iostream>

using namespace RCli;

int main(int argc, const char *argv[]){
    RCli::App templi("templi", "1.9.5", "Generate cool application");
    
    Command init("init", "init new project",[](Command *tet){
        String file_name =  tet->get_option_value("file");
        std::cout << "file_name: " << file_name << std::endl;
    });

    init.add_option(Option("-f,--file", "Specify filename", "file"));
    templi.add_subcommand(init);

    templi.run(argc, argv);
    return 0;
}
