#ifndef __RCLI_COMMAND__
#define __RCLI_COMMAND__

    #include <RCli/Option.hpp>

    namespace RCli{
        class Command{
            public:
                std::vector<RCli::Option> _options;
                std::vector<RCli::Command> _subcommands;
                Command(){};
        };
    }

#endif