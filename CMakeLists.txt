cmake_minimum_required (VERSION 3.29.5)

project ("ArdaCore")

message("Cmake:  ${CMAKE_VERSION}")
message("Compiler:  ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(ArdaCore)
add_subdirectory(Tests)

set_property(TARGET ArdaCore PROPERTY CXX_STANDARD 20)
