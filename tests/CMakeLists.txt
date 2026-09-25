# doctest is header-only: we only need its include directory, added as SYSTEM so its
# macros don't trigger our strict warnings.
find_package(doctest 2.4 QUIET)
if(doctest_FOUND)
  get_target_property(DOCTEST_INCLUDE_DIR doctest::doctest INTERFACE_INCLUDE_DIRECTORIES)
else()
  include(FetchContent)
  FetchContent_Declare(
    doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.12.tar.gz
    URL_HASH SHA256=73381c7aa4dee704bd935609668cf41880ea7f19fa0504a200e13b74999c2d70
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    SOURCE_SUBDIR do-not-add-subdirectory)
  FetchContent_MakeAvailable(doctest)
  set(DOCTEST_INCLUDE_DIR ${doctest_SOURCE_DIR})
endif()

set(RCLI_TEST_SOURCES main.cpp test_option.cpp test_command.cpp test_app.cpp)

function(rcli_add_test_executable name)
  add_executable(${name} ${RCLI_TEST_SOURCES})
  target_compile_features(${name} PRIVATE cxx_std_17)
  target_include_directories(${name} SYSTEM PRIVATE ${DOCTEST_INCLUDE_DIR})
  if(MSVC)
    target_compile_options(${name} PRIVATE /W4 /WX /permissive-)
  else()
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    # doctest's TEST_CASE macros use __COUNTER__, flagged by recent clang in pedantic mode
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(-Wc2y-extensions RCLI_HAS_WC2Y_EXTENSIONS)
    if(RCLI_HAS_WC2Y_EXTENSIONS)
      target_compile_options(${name} PRIVATE -Wno-c2y-extensions)
    endif()
  endif()
  add_test(NAME ${name} COMMAND ${name})
endfunction()

# 1. the modular headers (include/)
rcli_add_test_executable(rcli_tests)
target_link_libraries(rcli_tests PRIVATE rcli::rcli)

# every public header must compile on its own
file(GLOB RCLI_PUBLIC_HEADERS CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/include/rcli/*.hpp")
foreach(header ${RCLI_PUBLIC_HEADERS})
  get_filename_component(header_name ${header} NAME_WE)
  set(header_test ${CMAKE_CURRENT_BINARY_DIR}/self_contained/${header_name}.cpp)
  file(WRITE ${header_test} "#include <rcli/${header_name}.hpp>\n")
  target_sources(rcli_tests PRIVATE ${header_test})
endforeach()

# 2. the same tests against the generated single header (single_include/)
rcli_add_test_executable(rcli_single_header_tests)
target_include_directories(rcli_single_header_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/single_include)
