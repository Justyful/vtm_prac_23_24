add_executable(main test.cpp)
target_link_libraries(main strassen)

add_executable(mainf test.f90)
target_link_libraries(mainf strassen)
