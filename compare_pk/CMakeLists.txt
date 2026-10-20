cmake_minimum_required(VERSION 3.10)
project(compare_pk)

add_executable(compare_pk main.cpp)

target_link_libraries(compare_pk PRIVATE Core)
