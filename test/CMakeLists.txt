cmake_minimum_required(VERSION 3.10)
project(LogTest)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Boost
find_package(Boost REQUIRED COMPONENTS log filesystem system thread date_time)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} log_test.cpp ../log.hpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOOST_LOG_DYN_LINK)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main ${Boost_LIBRARIES})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})