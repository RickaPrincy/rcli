#include <algorithm>
#include <rcli/command.hpp>

using namespace rcli;

void Command::add_option(Option *option) { _options.push_back(option); }

bool Command::has_option(std::string option_name) {
    auto it = std::find_if(_options.begin(), _options.end(), [&option_name](Option *option) {
        return option->_description == option_name;
    });
    return it != _options.end();
}
