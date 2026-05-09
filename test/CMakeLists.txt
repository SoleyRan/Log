cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(log_test)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME} log_test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    good_log
)

gtest_discover_tests(${PROJECT_NAME})
