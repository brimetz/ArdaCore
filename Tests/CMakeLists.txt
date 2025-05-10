cmake_minimum_required (VERSION 3.29.5)

#project ("ArdaCoreTests")

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "*.cpp"
)

# create executable with all files inside SRC variables
add_executable (ArdaCoreExe ${SRC})

target_include_directories(ArdaCoreExe PUBLIC "../")
target_link_libraries(ArdaCoreExe ArdaCoreLib)

#set_property(TARGET ArdaCore PROPERTY CXX_STANDARD 20)