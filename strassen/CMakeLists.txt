cmake_minimum_required(VERSION 3.20)
project(test 
    LANGUAGES CXX Fortran)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")
set(CMAKE_Fortran_MODULE_DIRECTORY ${PROJECT_SOURCE_DIR}/include)

include_directories(include)

add_library(strassen)

add_subdirectory(src)
add_subdirectory(test)


