cmake_minimum_required(VERSION 3.10)
project(tester)

add_executable(tester main.cpp)

target_link_libraries(tester PRIVATE Core)
