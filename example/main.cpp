#include <RCli/RCli.hpp>
#include <iostream>

using namespace RCli;

int main(int argc, const char *argv[]){
    App templi("templi", "1.9.5", "Generate cool application");
    InputConfig config("What is your name", true, true);

    Command init("init", "init new project", [](Command* _init){
        std::cout <<"file value: " <<  _init->get_option_value("file") << std::endl;
    });

    init.add_option(Option("-f,--file","Specify file name", "file"));
    
    Command hello("hello", "say hello", [&](Command* _hello){
        String name = _hello->get_option_value("name");
        if(name.empty()){
            name = ask_input_value(config);
        }

        std::cout << "Hello  " << name  << std::endl;
    });
    
    hello.add_option(Option("-n,--name", "Specify your name", "name"));
    
    templi.add_subcommand(init);
    templi.add_subcommand(hello);
    templi.run(argc, argv);
    return 0;
}
