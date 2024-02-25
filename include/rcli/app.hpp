#pragma once

#include <rcli/command.hpp>
#include <string>

namespace rcli {
    class App : public Command {
    public:
        std::string _version;

        App(std::string name, std::string version, std::string description);

        void print_help() override;
        void print_version();
        void run(int argc, const char *argv[]);
    };
}  // namespace rcli
