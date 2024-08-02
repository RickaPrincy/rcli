#pragma once

#include <rcli/command.hpp>
#include <string>

namespace rcli {
class App : public Command {
protected:
  std::string _version;

public:
  App(std::string name, std::string version, std::string description);

  virtual void print_version();
  void run(int argc, const char *argv[]);
};
} // namespace rcli
