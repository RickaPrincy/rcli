set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
include_directories(${RCLI_SOURCE_DIR}/include)
include_directories(${RCLI_SOURCE_DIR}/external/TColor/include)
add_library(RCli STATIC ${SOURCES})

if(RCLI_INSTALL)
    install(TARGETS ${BINARY} DESTINATION lib)
    install(DIRECTORY ${RCLI_SOURCE_DIR}/include/RCli DESTINATION include)
endif()