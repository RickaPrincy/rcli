#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp>

    namespace RCli{
        class OptionValue{
            public:
                RCli::String _text, _default;
                bool _clean, _required;
                
                OptionValue(String text, bool clean = true, bool required = false, String default_value = "")
                    : _text(text), _clean(clean), _default(default_value), _required(required) {}

                OptionValue(const OptionValue& other){
                    *this = other;
                }
                
                OptionValue& operator=(const OptionValue& other) {
                    if (this != &other) {
                        _text = other._text;
                        _clean = other._clean;
                        _default = other._default;
                        _required = other._required;
                    }
                    return *this;
                }
        };
    }
#endif