#ifndef __RCLI_COMMAND__
#define __RCLI_COMMAND__

#include <rcli/option.hpp>
#include <string>
#include <vector>

namespace rcli {

    class Command {
    protected:
        std::vector<Command*> _subcommands{};
        std::vector<Option*> _options{};
        bool _is_parsed = false;
        bool has_option(std::string option_name);

    public:
        void add_option(Option *option);
    };

}  // namespace rcli

#endif  //__RCLI_COMMAND__
