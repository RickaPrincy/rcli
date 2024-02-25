#include <memory>
#include <rcli/command.hpp>

using namespace rcli;

Command::Command(std::string name, std::string description, Callback callback) {
    _name = name;
    _description = description;
    _callback = callback;
    add_option("-h,--help", "Show this help", "help");
}

std::string Command::get_name() {
    return _name;
}

std::string Command::get_description() {
    return _description;
}

bool Command::call_if_matched(std::string text) {
    if (is_matched(text)) {
        _callback(this);
        return true;
    }
    return false;
}

bool Command::is_matched(std::string text) {
    return text == _name;
}

void Command::print_help() {
    // TODO
}

void rcli::Command::add_option(std::string options, std::string description, std::string key_name) {
    this->add_option(new Option(options, description, key_name));
}

void rcli::Command::add_option(Option* new_option) {
    _options.push_back(std::make_shared<Option>(*new_option));
}

void rcli::Command::add_subcommand(Command* new_command) {
    _subcommands.push_back(std::make_shared<Command>(*new_command));
}

std::string Command::get_option_value(std::string key) {
    if (_options_values.find(key) == _options_values.end()) {
        return "";
    }
    return _options_values.at(key);
}

void Command::add_informations(std::map<std::string, std::string> informations) {
    for (const auto& info : informations) _informations.insert(info);
}

// TODO: refactor this function
void rcli::Command::parse(int argc, const char* argv[], int start) {
    if (start + 1 < argc) {
        std::string command_or_option = argv[start + 1];

        if (command_or_option == "--help" || command_or_option == "-h") {
            print_help();
            exit(EXIT_SUCCESS);
        }

        if (command_or_option.find("-") == 0) {
            bool valid_option = false;
            if (start + 2 >= argc) {
                print_help();
                exit(EXIT_SUCCESS);
            }
            for (auto option : _options) {
                std::string key_name = option->get_key_if_matched(command_or_option);
                if (key_name.empty()) {
                    continue;
                }

                _options_values.insert(std::make_pair(key_name, argv[start + 2]));
                valid_option = true;
                break;
            }

            if (!valid_option) {
                print_help();
                exit(EXIT_SUCCESS);
            } else {
                parse(argc, argv, start + 2);
                exit(EXIT_SUCCESS);
            }
        } else {
            for (auto command : _subcommands) {
                if (command->is_matched(command_or_option)) {
                    command->parse(argc, argv, start + 1);
                    exit(EXIT_SUCCESS);
                }
            }
            print_help();
            exit(EXIT_SUCCESS);
        }
    }

    _callback(this);
}

Command& Command::operator=(const Command& other) {
    if (this != &other) {
        _name = other._name;
        _description = other._description;
        _options_values = other._options_values;
    }
    return *this;
}
