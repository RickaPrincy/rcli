#ifndef __RCLI_TYPES__
#define __RCLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    #include <algorithm>
    #include <functional>
    #include <numeric>
    
    namespace RCli{
        
        using String = std::string;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
        
        class InputConfig{
            public:
                RCli::String _text = "", _default = "";
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