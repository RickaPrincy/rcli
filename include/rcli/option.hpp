#ifndef __RCLI_OPTION__
#define __RCLI_OPTION__

#include <string>

namespace rcli {
    class Option {
    public:
        std::string _name, _description;
        char _short_name;
        bool _is_parsed = false;
        Option(std::string name, char short_name, std::string description)
            : _name(name), _short_name(short_name), _description(description) {}
    };

}  // namespace rcli
#endif  // !__RCLI_OPTION__
