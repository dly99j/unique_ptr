cmake_minimum_required(VERSION 3.22)
project(unique_ptr)

set(CMAKE_CXX_STANDARD 23)

add_executable(unique_ptr main.cpp unique_ptr.cpp unique_ptr.h)
