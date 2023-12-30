#ifndef __RCLI_OPTIONS__
#define __RCLI_OPTIONS__

    #include <string>
    #include <vector>

    namespace rcli{
        class Option{
            private: 
                std::vector<std::string> _options;
                std::string _description, _key_name;
            public:
                Option(std::string options,std::string description, std::string key_name);
                
                std::vector<std::string> get_values();
                std::string get_description();
                std::string get_key_if_matched(std::string value);
                bool matched(std::string option);
        };
    }
#endif