cmake_minimum_required(VERSION 3.27)

project(RCli VERSION 1.4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SUBMODULES external/TColor)
set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(RCLI_INSTALL OFF)

configure_file("RCliConfig.h.in" "${RCLI_SOURCE_DIR}/include/RCli/RCliConfig.hpp")

#Download deps
find_package(Git REQUIRED)
foreach(submodule ${SUBMODULES})
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init ${submodule} 
        WORKING_DIRECTORY ${RCLI_SOURCE_DIR}
        RESULT_VARIABLE GIT_SUBMOD_RESULT
    )
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init  ${submodule} failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endforeach()

add_subdirectory(src)