cmake_minimum_required(VERSION 3.20)
project(test 
    LANGUAGES CXX Fortran)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

include_directories(include)

add_library(matrix)
add_library(strassen)
add_library(strassenf)

add_subdirectory(src)
add_subdirectory(test)

