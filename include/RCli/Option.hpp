#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        class Option{
            private: 
                VectorString _options;
                Callback _callback;
            public:
                Option(String options, Callback callback);
                VectorString get_values();
                bool call_if_matched(String option);
                bool matched(String option);
        };
    }
#endif