cmake_minimum_required(VERSION 3.27)
project(RCli VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(RCLI_INSTALL OFF)
option(RCLI_VERSION_BUILD "Build RCli version" OFF)

if(RCLI_VERSION_BUILD)
    configure_file("RCliConfig.h.in" "${RCLI_SOURCE_DIR}/include/RCli/RCliConfig.hpp")
endif()

add_subdirectory(src)