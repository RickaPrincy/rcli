# List all source files
file(GLOB_RECURSE RCLI_SOURCES CONFIGURE_DEPENDS "*.cpp")

# Create the library
if(BUILD_SHARED_LIBS)
  add_library(rcli SHARED ${RCLI_SOURCES})
else()
  add_library(rcli STATIC ${RCLI_SOURCES})
endif()

# Set include directories for the library
target_include_directories(rcli
                           PUBLIC $<BUILD_INTERFACE:${RCLI_SOURCE_DIR}/include>)

# set properties
set_target_properties(
  rcli
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/cmake/rcliVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

# Install rcli header files
include(GNUInstallDirs)
install(DIRECTORY ${RCLI_SOURCE_DIR}/include/rcli
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  TARGETS rcli
  EXPORT rcliTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

# Install the Config and ConfigVersion files
install(
  EXPORT rcliTargets
  FILE rcliTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rcli)

configure_file(${RCLI_SOURCE_DIR}/cmake/rcliConfig.cmake.in
               ${CMAKE_BINARY_DIR}/cmake/rcliConfig.cmake @ONLY)

# Install the Config, ConfigVersion and custom Find module files
install(DIRECTORY ${CMAKE_BINARY_DIR}/cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rcli)
