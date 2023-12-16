#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <RCli/types.hpp> 

    namespace RCli{
        using Callback = void(*)();

        class Option{
            private: 
                RCli::VectorString _options;
                Callback _callback;
            public:
                Option(RCli::String options, Callback callback);
        };
    }
#endif