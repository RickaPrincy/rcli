#ifndef __RCLI_TYPES__
#define __RCLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    #include <algorithm>
    #include <functional>
    #include <initializer_list>
    #include <numeric>
    #include <dumb_types/dumb_types.hpp>
    #include <TColor/TColor.hpp>
    
    namespace RCli{
        
        using namespace dumb_types; 
        
        class InputConfig{
            public:
                String _text = "", _default = "";
                bool _clean = true, _required = false;
                InputConfig &text(String text){
                    _text = text;
                    return *this;
                }

                InputConfig &default_value(String text){
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