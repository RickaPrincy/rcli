#pragma once

#include <string>

namespace rcli {
    class App {
    public:
        std::string version, description;
        App(std::string version, std::string description);
    };
}  // namespace rcli
