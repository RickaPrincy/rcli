#ifndef __RCLI_INPUT_CONFIG__
#define __RCLI_INPUT_CONFIG__

    #include <string>
    
    namespace RCli{
        class InputConfig{
            public:
                std::string _text = "", _default = "";
                bool _clean = true, _required = false;
                InputConfig &text(std::string text){
                    _text = text;
                    return *this;
                }

                InputConfig &default_value(std::string text){
                    _default = text;
                    return *this;
                }

                InputConfig &required(bool required){
                    _required = required;
                    return *this;
                }

                InputConfig &clean(bool clean){
                    _clean = clean;
                    return *this;
                }
                
                InputConfig& operator=(const InputConfig& other) {
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