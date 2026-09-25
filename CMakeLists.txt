cmake_minimum_required(VERSION 3.18)

# single source of truth for the version: include/rcli/version.hpp
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/rcli/version.hpp" RCLI_VERSION_HEADER)
foreach(part MAJOR MINOR PATCH)
  string(REGEX MATCH "#define RCLI_VERSION_${part} ([0-9]+)" _ "${RCLI_VERSION_HEADER}")
  set(RCLI_VERSION_${part} ${CMAKE_MATCH_1})
endforeach()

project(
  rcli
  VERSION ${RCLI_VERSION_MAJOR}.${RCLI_VERSION_MINOR}.${RCLI_VERSION_PATCH}
  DESCRIPTION "Header-only library to build command line applications in C++17"
  HOMEPAGE_URL "https://github.com/RickaPrincy/rcli"
  LANGUAGES CXX)

set(RCLI_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(RCLI_IS_MAIN_PROJECT ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

option(RCLI_BUILD_TESTS "Build the rcli tests" ${RCLI_IS_MAIN_PROJECT})
option(RCLI_BUILD_EXAMPLES "Build the rcli examples" ${RCLI_IS_MAIN_PROJECT})
option(RCLI_INSTALL "Generate the rcli install target" ${RCLI_IS_MAIN_PROJECT})

include(GNUInstallDirs)

# the library itself: headers only. Link with rcli::rcli (or rcli, kept for compatibility)
add_library(rcli INTERFACE)
add_library(rcli::rcli ALIAS rcli)
target_compile_features(rcli INTERFACE cxx_std_17)
target_include_directories(
  rcli INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(RCLI_INSTALL)
  include(CMakePackageConfigHelpers)
  set(RCLI_CMAKE_DIR ${CMAKE_INSTALL_DATADIR}/cmake/rcli)

  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/rcli
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(TARGETS rcli EXPORT rcliTargets)
  install(
    EXPORT rcliTargets
    NAMESPACE rcli::
    DESTINATION ${RCLI_CMAKE_DIR})

  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rcliConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/rcliConfig.cmake
    INSTALL_DESTINATION ${RCLI_CMAKE_DIR})
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/rcliConfigVersion.cmake
    COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rcliConfig.cmake
                ${CMAKE_CURRENT_BINARY_DIR}/rcliConfigVersion.cmake
          DESTINATION ${RCLI_CMAKE_DIR})
endif()

if(RCLI_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(RCLI_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

if(RCLI_IS_MAIN_PROJECT)
  # regenerate single_include/rcli/rcli.hpp from include/
  find_package(Python3 COMPONENTS Interpreter QUIET)
  if(Python3_FOUND)
    add_custom_target(amalgamate
      COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/amalgamate.py
      COMMENT "Generating the single header")
  endif()

  file(GLOB_RECURSE RCLI_ALL_SOURCES CONFIGURE_DEPENDS
       "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
       "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
       "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp"
       "${CMAKE_CURRENT_SOURCE_DIR}/example/*.cpp")

  find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
  if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(format
      COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${RCLI_ALL_SOURCES}
      COMMENT "Formatting sources with clang-format")
    add_custom_target(format-check
      COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run --Werror -style=file ${RCLI_ALL_SOURCES}
      COMMENT "Checking sources format with clang-format")
  endif()

  find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
  if(CLANG_TIDY_EXECUTABLE)
    file(GLOB RCLI_TIDY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/example/*.cpp")
    add_custom_target(lint
      COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR} ${RCLI_TIDY_SOURCES}
      COMMENT "Running clang-tidy")
  endif()
endif()
