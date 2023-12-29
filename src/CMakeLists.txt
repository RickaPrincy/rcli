file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)


add_library(RCli STATIC ${SOURCES})

target_include_directories(RCli PUBLIC ${RCLI_SOURCE_DIR}/include)

set_target_properties(RCli PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if(RCLI_INSTALL)
    install(TARGETS RCli DESTINATION lib)
    install(DIRECTORY ${RCLI_SOURCE_DIR}/include/RCli DESTINATION include)
    install(DIRECTORY ${RCLI_SOURCE_DIR}/include/dumb_types DESTINATION include)
    install(DIRECTORY ${RCLI_SOURCE_DIR}/include/TColor DESTINATION include)
endif()
