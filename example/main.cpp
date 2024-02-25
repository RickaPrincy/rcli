#include <iostream>
#include <rcli/rcli.hpp>
#include "rcli/input_config.hpp"
#include "rcli/inputs.hpp"

using namespace rcli;

int main(int argc, const char *argv[]) {
    InputConfig config;
    App ctemplate("ctemplate", "Cool application", "1.5.0");
    Option option("-f, --file", "get file name", "file");

    Command generate("generate", "generate new project", [&](Command *_generate) {
        std::string file_name = _generate->get_option_value("file");
        std::cout << "file -> " << file_name << std::endl;
        std::cout << "path -> " << _generate->get_option_value("path") << std::endl;

        if (file_name.empty()){
            std::cout << ask_boolean("Wanna hangout ?", true) << std::endl;
        }
    });

    generate.add_option(&option);
    generate.add_option("-p, --path", "say where is the path", "path");

    ctemplate.add_subcommand(&generate);
    ctemplate.run(argc, argv);
}
