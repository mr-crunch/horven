cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

project(horven)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(horven src/main.cpp)
