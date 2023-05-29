cmake_minimum_required(VERSION 3.25)
project(OS5_ActiveObject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(OS5_ActiveObject
        Part_A.c
        Part_A.h)
