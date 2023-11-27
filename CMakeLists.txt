cmake_minimum_required(VERSION 3.27)
project(RCli VERSION 0.5.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RCLI_VERSION_BUILD "Build RCli version" OFF)

if(RCLI_VERSION_BUILD)
    configure_file("RCliConfig.h.in" "${CMAKE_SOURCE_DIR}/include/RCli/RCliConfig.hpp")
endif()

add_subdirectory(src)