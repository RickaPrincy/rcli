#ifndef __RCLI_TYPES__
#define __RCLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    #include <algorithm>
    
    namespace RCli{
        using String = std::string;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
    } 

#endif