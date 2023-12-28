cmake_minimum_required(VERSION 3.27)
project(example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(example main.cpp)

target_link_libraries(example PUBLIC RCli)