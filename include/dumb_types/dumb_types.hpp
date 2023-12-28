// dumb_types.hpp

// dumb_types: A Simple and Convenient C++ Header-Only Library
// ========================================================
// Author: RickaPrincy 
// GitHub: https://github.com/RickaPrincy/dumb_types
// Version: 1.0.0
// License: MIT License
// ========================================================
//
// Welcome to DumbTypes, a lightweight C++ library providing
// convenient aliases for common data types. Keep your code
// clean and simple with dumb_types!
//
// Visit our GitHub repository for updates and contributions.
// I Made this 'cause I was too lazy to write std::string everytime XD
// Happy coding!

#ifndef __DUMP_TYPES_HEADER__
#define __DUMP_TYPES_HEADER__
   
    #include <set>
    #include <map>
    #include <string>
    #include <vector>
    
    namespace dumb_types{
        using String = std::string;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
        using IntVector = std::vector<int>;
        using FloatVector = std::vector<float>;
        using DoubleVector = std::vector<double>;
        using IntSet = std::set<int>;
        using PairStringInt = std::pair<String, int>;
    }
#endif