cmake_minimum_required(VERSION 3.18)

project(rcli_tools VERSION 0.0.1)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deps find_package(rcli REQUIRED)

set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RCLI_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(RCLI_IS_MAIN_PROJECT ON)
endif()

# target names
set(RCLI_LIB_NAME rcli)
set(RCLI_LIB_VERSION 2.0.0)
set(RCLI_LIB_VERSION_MAJOR 2)
set(RCLI_VERSION ${PROJECT_VERSION})
set(RCLI_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library"
       ${RCLI_IS_MAIN_PROJECT})
option(RCLI_LIB_BUILD "Build rcli lib" ON)
option(RCLI_LIB_INSTALL "Install rcli lib" ${RCLI_IS_MAIN_PROJECT})
option(RCLI_BUILD_EXAMPLES "Build the examples in the project" OFF)

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Build example if build types is not release and rcli is a main project
if(RCLI_IS_MAIN_PROJECT AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(RCLI_BUILD_EXAMPLES ON)
endif()

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(RCLI_TEST OFF)
endif()

if(RCLI_IS_MAIN_PROJECT)
  configure_file(${RCLI_SOURCE_DIR}/.templates/PKGBUILD.in
                 ${RCLI_SOURCE_DIR}/PKGBUILD @ONLY)

  configure_file(${RCLI_SOURCE_DIR}/.templates/create-release.sh.in
                 ${RCLI_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${RCLI_SOURCE_DIR}/.templates/${RCLI_LIB_NAME}Config.hpp.in
    ${RCLI_SOURCE_DIR}/include/${RCLI_LIB_NAME}/${RCLI_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

if(RCLI_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${RCLI_SOURCE_DIR}/sources/*.cpp"
       "${RCLI_SOURCE_DIR}/include/*.hpp" "${RCLI_SOURCE_DIR}/sources/*.hpp"
       "${RCLI_SOURCE_DIR}/example/*.cpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY Starter of styled cli for c++)
include(CPack)
