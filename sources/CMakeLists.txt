project(
  ${RCLI_LIB_NAME}
  VERSION ${RCLI_LIB_VERSION}
  LANGUAGES CXX)

set(LIB_SOURCES
    app.cpp
    color_config.cpp
    command.cpp
    inputs.cpp
    option.cpp
    utils/input.cpp
    utils/print.cpp
    utils/string.cpp)

# Create the library
if(BUILD_SHARED_LIBS)
  add_library(${RCLI_LIB_NAME} SHARED ${LIB_SOURCES})
else()
  add_library(${RCLI_LIB_NAME} STATIC ${LIB_SOURCES})
endif()

# Set include directories for the library
target_include_directories(
  ${RCLI_LIB_NAME} PRIVATE $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include>)

# target_link target_link_libraries(${RCLI_LIB_NAME} PUBLIC rcli)

# set properties
set_target_properties(
  ${RCLI_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             SOVERSION ${RCLI_LIB_VERSION_MAJOR}
             VERSION ${RCLI_LIB_VERSION})

# lib install configuration
if(RCLI_LIB_INSTALL)
  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${RCLI_LIB_NAME}Version.cmake
    VERSION ${RCLI_VERSION}
    COMPATIBILITY SameMajorVersion)

  include(GNUInstallDirs)
  install(DIRECTORY ${RCLI_SOURCE_DIR}/include/${RCLI_LIB_NAME}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    TARGETS ${RCLI_LIB_NAME}
    EXPORT ${RCLI_LIB_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

  # Install the Config and ConfigVersion files
  install(
    EXPORT ${RCLI_LIB_NAME}Targets
    FILE ${RCLI_LIB_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${RCLI_LIB_NAME})

  configure_file(${RCLI_SOURCE_DIR}/cmake/${RCLI_LIB_NAME}Config.cmake.in
                 ${CMAKE_BINARY_DIR}/cmake/${RCLI_LIB_NAME}Config.cmake @ONLY)
  # Install the Config, ConfigVersion, and custom Find module files
  install(FILES ${CMAKE_BINARY_DIR}/cmake/${RCLI_LIB_NAME}Config.cmake
                ${CMAKE_BINARY_DIR}/cmake/${RCLI_LIB_NAME}Version.cmake
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${RCLI_LIB_NAME})
endif()
