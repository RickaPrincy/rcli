cmake_minimum_required(VERSION 3.27)

project(rcli VERSION 1.5.0 LANGUAGES CXX)

#Set RCLI_SOURCE_DIR to the current path
set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check if RCLI is the main project
set(RCLI_IS_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(RCLI_IS_MAIN_PROJECT ON)
endif()

# Make default build type to "Debug" 
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Define Options
option(RCLI_INSTALL "Add install step for rcli" ${RCLI_IS_MAIN_PROJECT})
option(BUILD_SHARED_LIBS "Build rcli as a shared library" OFF)
option(RCLI_BUILD_EXAMPLES "Build the examples in the project" OFF)

# Build example if build types is not release and rcli is a main project
if (RCLI_IS_MAIN_PROJECT AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(RCLI_BUILD_EXAMPLES ON)
endif()

# Clang format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)

if(CLANG_FORMAT_EXECUTABLE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${RCLI_SOURCE_DIR}/src/*.cpp
        ${RCLI_SOURCE_DIR}/src/utils/*.cpp
        ${RCLI_SOURCE_DIR}}/include/*.hpp
    )

    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT_EXECUTABLE}
                -i
                -style=file
                ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format"
    )
else()
    message(WARNING "clang-format not found. Clang-format target will not be available.")
endif()


# Add subdirectory
add_subdirectory(src)

if(RCLI_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# Use GNUIInstallDirs for the installation
include(GNUInstallDirs)

# Install the library
install(
    TARGETS rcli
    EXPORT rcliTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install rcli header files
install(
    DIRECTORY ${RCLI_SOURCE_DIR}/include/rcli
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
