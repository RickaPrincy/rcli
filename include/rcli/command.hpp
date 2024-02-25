#pragma once

#include <rcli/types.hpp>
#include <string>

namespace rcli {
    class Command {
    private:
        Callback callback;
        std::string key, description;
        bool make_action_if_matched(std::string arg);

    public:
        Command(std::string key, std::string description, Callback callback);
        virtual void print_help();
    };
}  // namespace rcli
