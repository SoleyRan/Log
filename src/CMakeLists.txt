cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    message("Boost found: ${Boost_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "Cannot find Boost")
endif ()

add_library(good_log SHARED text_file_backend_self_defined.cpp)
target_compile_definitions(good_log PUBLIC -DBOOST_LOG_DYN_LINK)
target_include_directories(good_log PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(good_log PUBLIC 
    -lboost_system 
    -lboost_log_setup
    -lboost_log
    -lboost_thread
    -lboost_filesystem
    -lrt
    -ldl
    -lpthread
)
