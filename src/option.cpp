#include <rcli/option.hpp>

#include "utils/utils.hpp"

using namespace rcli;

rcli::Option::Option(std::string options, std::string description, std::string key_name) {
    _description = description;
    _key_name = key_name;
    _options = Utils::split(Utils::clean_text(options), ",");
}

std::string Option::get_key_if_matched(std::string value) {
    if (Utils::some(value, _options)) {
        return _key_name;
    }
    return "";
}

std::string Option::get_description() {
    return _description;
}
