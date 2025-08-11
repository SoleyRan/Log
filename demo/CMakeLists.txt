cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(log_demo)

add_executable(${PROJECT_NAME} log_demo.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    good_log
)
