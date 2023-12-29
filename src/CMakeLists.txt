# List all source files
file(GLOB_RECURSE RCLI_SOURCES CONFIGURE_DEPENDS "*.cpp")

# Create the static library
add_library(RCli STATIC ${RCLI_SOURCES})

# Set include directories for the library
target_include_directories(RCli
    PUBLIC
        $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include/external>
)

# Set C++ standard
target_compile_features(RCli PUBLIC cxx_std_17)

# Set output directory
set_target_properties(RCli PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)