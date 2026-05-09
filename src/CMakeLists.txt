cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system log_setup log thread filesystem)
find_package(Threads REQUIRED)

add_library(good_log SHARED text_file_backend_self_defined.cpp)
add_library(GoodLog::good_log ALIAS good_log)

set_target_properties(good_log PROPERTIES
    EXPORT_NAME good_log
    OUTPUT_NAME good_log
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_compile_definitions(good_log PUBLIC BOOST_LOG_DYN_LINK)

target_include_directories(good_log
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/goodlog>
)

target_link_libraries(good_log
    PUBLIC
        Boost::system
        Boost::log_setup
        Boost::log
        Boost::thread
        Boost::filesystem
        Threads::Threads
)

if(CMAKE_DL_LIBS)
    target_link_libraries(good_log PUBLIC ${CMAKE_DL_LIBS})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(good_log PUBLIC rt)
endif()

install(
    TARGETS good_log
    EXPORT GoodLogTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/goodlog
)

install(
    FILES
        log.hpp
        text_file_backend_self_defined.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/goodlog
)
