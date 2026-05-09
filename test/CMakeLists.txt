cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(log_test)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} log_test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    good_log
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
