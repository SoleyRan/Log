cmake_minimum_required(VERSION 3.5)

project(GoodLog VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_DEMO "Build demo target" ON)
option(BUILD_TEST "Build test target" ON)

add_subdirectory(src)

if(BUILD_DEMO)
    message("=============================================================")
    message("-- BUILD DEMO --")
    message("=============================================================")
    add_subdirectory(demo)
endif()

if(BUILD_TEST)
    message("=============================================================")
    message("-- BUILD TEST --")
    message("=============================================================")
    add_subdirectory(test)
endif()

set(GOODLOG_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/GoodLog")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GoodLogConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GoodLogConfig.cmake"
    INSTALL_DESTINATION "${GOODLOG_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GoodLogConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    EXPORT GoodLogTargets
    NAMESPACE GoodLog::
    DESTINATION "${GOODLOG_INSTALL_CMAKEDIR}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/GoodLogConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/GoodLogConfigVersion.cmake"
    DESTINATION "${GOODLOG_INSTALL_CMAKEDIR}"
)

install(
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}"
)