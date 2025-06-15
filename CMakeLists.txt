cmake_minimum_required(VERSION 3.18)

project(rcli_tools VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RCLI_IS_MAIN_PROJECT OFF)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(RCLI_IS_MAIN_PROJECT ON)
endif()

# target names
set(RCLI_LIB_NAME rcli)
set(RCLI_LIB_VERSION 2.0.23)
set(RCLI_LIB_VERSION_MAJOR 2)
set(RCLI_VERSION ${RCLI_LIB_VERSION})
set(RCLI_VERSION_MAJOR ${RCLI_LIB_VERSION_MAJOR})

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library" OFF)
option(RCLI_LIB_INSTALL "Install rcli lib" ${RCLI_IS_MAIN_PROJECT})
option(RCLI_BUILD_EXAMPLES "Build the examples in the project" ${RCLI_IS_MAIN_PROJECT})

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

  configure_file(${RCLI_SOURCE_DIR}/.templates/install.sh.in
                 ${RCLI_SOURCE_DIR}/install.sh @ONLY)

  configure_file(${RCLI_SOURCE_DIR}/.templates/create-release.sh.in
                 ${RCLI_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${RCLI_SOURCE_DIR}/.templates/${RCLI_LIB_NAME}_config.hpp.in
    ${RCLI_SOURCE_DIR}/include/${RCLI_LIB_NAME}/${RCLI_LIB_NAME}_config.hpp
    @ONLY)
endif()

if(NOT CMAKE_BUILD_SHARED_LIBS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

add_subdirectory(sources)

if(RCLI_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library to parse user command-line input")
include(CPack)

# clang-format
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES
     "${RCLI_SOURCE_DIR}/example/*.cpp"
     "${RCLI_SOURCE_DIR}/sources/*.cpp"
     "${RCLI_SOURCE_DIR}/sources/*.hpp"
     "${RCLI_SOURCE_DIR}/include/rcli/*.hpp")

  add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format to format code"
  )

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run --Werror -style=file ${ALL_SOURCE_FILES}
    COMMENT "Checking code format (clang-format) - will fail if formatting issues"
  )
else()
  message(WARNING "clang-format not found. Format targets will NOT be available.")
endif()

# clang-tidy
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
  if(NOT ALL_SOURCE_FILES)
    file(GLOB_RECURSE ALL_SOURCE_FILES
       "${RCLI_SOURCE_DIR}/example/*.cpp"
       "${RCLI_SOURCE_DIR}/sources/*.cpp"
       "${RCLI_SOURCE_DIR}/sources/*.hpp"
       "${RCLI_SOURCE_DIR}/include/rcli/*.hpp")
  endif()
  
  add_custom_target(lint
    COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_CURRENT_BINARY_DIR} ${ALL_SOURCE_FILES}
    COMMENT "Running clang-tidy"
  )
else()
  message(WARNING "clang-tidy not found. clang-tidy target will NOT be available.")
endif()
