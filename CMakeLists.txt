cmake_minimum_required(VERSION 3.27)

project(RCli VERSION 1.4.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(RCLI_INSTALL OFF)

configure_file("RCliConfig.h.in" "${RCLI_SOURCE_DIR}/include/RCli/RCliConfig.hpp")

add_subdirectory(src)