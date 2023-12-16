#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        using Callback = std::function<void()>;
        
        class Option{
            private: 
                RCli::VectorString _options;
                Callback _callback;
            public:
                Option(RCli::String options, Callback callback);
                bool call_if_valid(String option);
        };
    }
#endif