#include <rcli/command.hpp>

rcli::Command::Command(std::string key, std::string description, Callback callback) {
    this->key = key;
    this->description = description;
    this->callback = callback;
}

bool rcli::Command::make_action_if_matched(std::string arg) {
    if (key == arg) {
        callback();
        return true;
    }
    return false;
}

void rcli::Command::print_help(){
}
