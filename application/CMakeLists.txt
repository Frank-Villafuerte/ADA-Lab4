cmake_minimum_required(VERSION 3.10)
project(application)

add_executable(application main.cpp)

target_link_libraries(application PRIVATE Core)
