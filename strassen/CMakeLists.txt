cmake_minimum_required(VERSION 3.10)
project(test 
	LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories(include)
add_subdirectory(src)

add_executable(main test.cpp)

target_link_libraries(main matrix)
target_link_libraries(main strassen)