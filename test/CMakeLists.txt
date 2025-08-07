cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(log_test)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    message("Boost found: ${Boost_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "Cannot find Boost")
endif ()

add_executable(${PROJECT_NAME} test.cpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOOST_LOG_DYN_LINK)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC 
    -lboost_system 
    -lboost_log_setup
    -lboost_log
    -lboost_thread
    -lboost_filesystem
    -lrt
    -ldl
    -lpthread
)
