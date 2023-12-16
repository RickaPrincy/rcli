#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        class Option{
            private: 
                VectorString _options;
                String _description;
                Callback _callback;
            public:
                Option(String options,String description, Callback callback);
                VectorString get_values();
                String get_description();
                bool call_if_matched(String option);
                bool matched(String option);
        };
    }
#endif