cmake_minimum_required(VERSION 3.10)
project(exec_time)

add_executable(exec_time main.cpp)

target_link_libraries(exec_time PRIVATE Core)
