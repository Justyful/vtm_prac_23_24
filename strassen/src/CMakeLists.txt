project(libraries)

add_library(matrix matrix.cpp strassen.cpp)
add_library(strassen strassen.cpp)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(strassen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})