cmake_minimum_required(VERSION 3.16)
project(practica1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(practica1
        classes.h
        display_tools.h
        main.cpp
        math_tools.h
        tools.h sel.h)
