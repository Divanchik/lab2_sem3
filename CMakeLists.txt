cmake_minimum_required(VERSION 3.0)

project(lab2_sem3)

add_library(binimlib binimlib.cpp)

add_executable(result main.cpp)

target_link_libraries(result binimlib)