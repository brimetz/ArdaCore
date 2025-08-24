cmake_minimum_required (VERSION 3.29.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Cmake:  ${CMAKE_VERSION}")
message("Compiler:  ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

project (ArdaCore LANGUAGES CXX)

add_subdirectory(ArdaCore)

# Enable testing for this directory and below.
enable_testing()
add_subdirectory(Tests)

add_test(NAME AllTests COMMAND ArdaCoreExe)