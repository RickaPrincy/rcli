#ifndef __RCLI_CONFIG__
#define __RCLI_CONFIG__
    
    #include <RCli/types.hpp> 

    namespace RCli{
        class Config{
            public:
                static String 
                    _input_key_color,
                    _input_value_color,
                    _info_key_color,
                    _info_value_color,
                    _error_color;
        };
    }
#endif