#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        class Option{
            private: 
                VectorString _options;
                String _description, _key_name;
            public:
                Option(String options,String description, String key_name);
                
                VectorString get_values();
                String get_description();
                String get_key_if_matched(String value);
                bool matched(String option);
        };
    }
#endif