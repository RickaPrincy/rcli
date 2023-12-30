cmake_minimum_required(VERSION 3.27)

project(rcli VERSION 1.4.2 LANGUAGES CXX)

#Set RCLI_SOURCE_DIR to the current path
set(RCLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if RCLI is the main project
set(RCLI_IS_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(RCLI_IS_MAIN_PROJECT ON)
endif()

# Default to build type "Debug" 
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Define Options
option(RCLI_BUILD_EXAMPLES "Build the examples in the project" OFF)
option(RCLI_INSTALL "Add install step for rcli" ${RCLI_IS_MAIN_PROJECT})
option(RCLI_SHARED_LIBS "Build rcli as a shared library" OFF)

# Build example if build types is not release and rcli is a main project
if (RCLI_IS_MAIN_PROJECT AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(RCLI_BUILD_EXAMPLES ON)
endif()

add_subdirectory(src)

if(RCLI_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# Use GNUIInstallDirs for the installation
include(GNUInstallDirs)

# Generate rcliConfig.cmake
configure_file(
	"${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_BINARY_DIR}/rcliConfig.cmake" @ONLY
)

# Generate rcliConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/rcliConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

# Install rcliConfig.cmake and rcliConfigVersion.cmake
install(
    FILES
        "${CMAKE_BINARY_DIR}/rcliConfig.cmake"
        "${CMAKE_BINARY_DIR}/rcliConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rcli
)

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

# Install external header files
install(
    DIRECTORY ${RCLI_SOURCE_DIR}/include/external/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the Config and ConfigVersion files
install(
    EXPORT rcliTargets
    FILE rcliTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rcli
)