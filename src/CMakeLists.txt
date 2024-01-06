# List all source files
file(GLOB_RECURSE RCLI_SOURCES CONFIGURE_DEPENDS "*.cpp")

# Create the library
if(RCLI_SHARED_LIBS)
    add_library(rcli SHARED ${RCLI_SOURCES})
else()
    add_library(rcli STATIC ${RCLI_SOURCES})
endif()

# Set include directories for the library
target_include_directories(rcli
    PUBLIC
        $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include/external>
)

# Set C++ standard
target_compile_features(rcli PUBLIC cxx_std_17)

# Set output directory
set_target_properties(rcli PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)