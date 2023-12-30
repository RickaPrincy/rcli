add_executable(example main.cpp)

target_include_directories(example PUBLIC 
    ${RCLI_SOURCE_DIR}/include
    ${RCLI_SOURCE_DIR}/include/external
)
target_link_directories(example PRIVATE ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(example PUBLIC rcli)