#include <cstdlib>
#include <iostream>
#include <rcli/app.hpp>
#include <rcli/command.hpp>

#include "utils/utils.hpp"

using namespace rcli;

App::App(std::string name, std::string description, std::string version) {
    if (name.empty() || version.empty() || description.empty()) {
        Utils::log_error("\"name\", \"version\" and \"description\" are required");
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }

    _name = name;
    _version = version;
    _description = description;
    this->add_option("-v,--version", "Show the version", "version");
    this->add_option("-h,--help", "Show this help", "help");
    this->_callback = [&](Command *_app) { _app->print_help(); };
}

void rcli::App::run(int argc, const char *argv[]) {
    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "-v" || arg == "--version") {
            this->print_version();
            return;
        }
    }

    this->parse(argc, argv, 1);
}

void rcli::App::print_version() {
    Utils::print_as_key_value(" Name", _name);
    Utils::print_as_key_value(" Version", _version);
    Utils::print_as_key_value(" Description", _description);
    for (const auto &[key, value] : _informations) {
        Utils::print_as_key_value(" " + key, value);
    }
}
