#ifndef __RCLI_COLOR_CONFIG__
#define __RCLI_COLOR_CONFIG__
    
    #include <string>    
    
    namespace rcli{
        class ColorConfig{
            public:
                static std::string 
                    _input_key_color,
                    _input_value_color,
                    _info_key_color,
                    _info_value_color,
                    _error_color;
        };
    }
#endif