cmake_minimum_required(VERSION 3.10)
project(main 
	LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_library(matrix matrix.cpp matrix.h)
#add_library(strassen strassen.cpp strassen.h)

add_executable(main main.cpp)

target_link_libraries(main matrix)
#target_link_libraries(main strassen)

#add_subdirectory(directory_name)
#target_include_directories( chto-to )