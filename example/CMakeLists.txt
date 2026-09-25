add_executable(example main.cpp)
target_link_libraries(example PRIVATE rcli::rcli)
set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
