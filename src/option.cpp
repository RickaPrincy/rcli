#include <rcli/option.hpp>

template <typename T>
rcli::Option<T>::Option(std::string options, std::string description, T value) {
    this->description = description;
    this->value = value;
}
