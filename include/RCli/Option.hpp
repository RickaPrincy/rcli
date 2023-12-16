#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        using Callback = std::function<void()>;
        
        class Option{
            private: 
                VectorString _options;
                Callback _callback;
            public:
                Option(String options, Callback callback);
                bool call_if_matched(String option);
                bool is_matched(String option);
        };
    }
#endif