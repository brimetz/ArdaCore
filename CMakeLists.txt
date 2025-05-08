cmake_minimum_required (VERSION 3.29.5)

set(CMAKE_CXX_STANDARD 20)

message("Cmake:  ${CMAKE_VERSION}")
message("Compiler:  ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

project (ArdaCore)

add_subdirectory(ArdaCore)
add_subdirectory(Tests)
