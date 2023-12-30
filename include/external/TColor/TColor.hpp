/*
 * TColor: TColor is a simple header file that provides you with options to print text in color within the terminal 
 *
 * Usage example:
 *   TColor::write(TColor::B_RED, "This is bold red text.");
 */

#ifndef __TCOLOR_COLORS__
#define __TCOLOR_COLORS__

#include <string>
#include <iostream>

namespace TColor {
    const std::string RESET = "\033[0m";
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string B_BLACK = "\033[1;30m";
    const std::string B_RED = "\033[1;31m";
    const std::string B_GREEN = "\033[1;32m";
    const std::string B_YELLOW = "\033[1;33m";
    const std::string B_BLUE = "\033[1;34m";
    const std::string B_MAGENTA = "\033[1;35m";
    const std::string B_CYAN = "\033[1;36m";
    const std::string B_WHITE = "\033[1;37m";

    template<typename T>
    inline void write(const std::string& color, const T& value) {
        std::cout << color << value << RESET;
    }

    template<typename T>
    inline void write_endl(const std::string& color, const T& value) {
        write(color, value);
        std::cout << std::endl;
    }

    inline void set_color(const std::string &color){
        std::cout << color;
    }
}

#endif