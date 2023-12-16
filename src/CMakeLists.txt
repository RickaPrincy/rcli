set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/external/TColor/include)
add_library(RCli STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/RCli DESTINATION include)