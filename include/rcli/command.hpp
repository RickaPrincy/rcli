#pragma once

#include <map>
#include <rcli/option.hpp>
#include <rcli/types.hpp>
#include <string>
#include <vector>

namespace rcli {
    class Command {
    protected:
        std::string _name, _description;
        Callback _callback;
        std::vector<Option> _options;
        std::vector<Command> _subcommands;

        std::map<std::string, std::string> _options_values, _informations;

        Command* _parent = nullptr;

        void parse(int argc, const char* argv[], int start);
        bool is_matched(std::string text);
        bool call_if_matched(std::string text);

        Command(){};

    public:
        virtual void print_help();

        std::string get_name();
        std::string get_description();
        std::string get_option_value(std::string key);

        std::string get_suffix();

        void add_option(Option new_option);
        void add_option(std::string options, std::string description, std::string key_name);
        void add_subcommand(Command new_command);
        void add_informations(std::map<std::string, std::string> informations);

        Command& operator=(const Command& other);
        Command(std::string name, std::string description, Callback callback);
    };
}  // namespace rcli
