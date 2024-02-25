#include <cstdlib>
#include <rcli/app.hpp>

#include "utils/utils.hpp"

using namespace rcli;

App::App(std::string name, std::string description, std::string version) {
    if (name.empty() || version.empty() || description.empty()) {
        Utils::log_error("\"name\", \"version\" and \"description\" are required");
        exit(EXIT_FAILURE);
    }

    _name = name;
    _version = version;
    _description = description;
    this->add_option("-v,--version", "Show the version", "version");
}

void App::print_help() {
    // TODO
}

void rcli::App::run(int argc, const char *argv[]) {
    if (argc == 1) {
        this->print_help();
        return;
    }

    std::string arg = argv[1];
    if (arg == "-v" || arg == "--version") {
        this->print_version();
        return;
    }
    this->parse(argc, argv, 0);
}

void rcli::App::print_version() {
    Utils::print_as_key_value("Name", _name);
    Utils::print_as_key_value("Version", _version);
    for (const auto &[key, value] : _informations) {
        Utils::print_as_key_value(key, value);
    }
}
