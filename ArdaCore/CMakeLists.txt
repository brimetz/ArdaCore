cmake_minimum_required (VERSION 3.29.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

project("ArdaCoreLib" LANGUAGES CXX)

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "*.cpp"
)

# Add Files to ArdaCore 
set(ArdaCoreLibTarget ArdaCoreLib)
add_library(${ArdaCoreLibTarget}
		${SRC})

target_include_directories(ArdaCoreLib PUBLIC "../")

#if (MSVC)
#	target_compile_options(${ArdaCoreLibTarget} PRIVATE /MP)	# Multithread compilation
#else() # Clang or GCC
#	message("Not MSVC software, not managed")
#endif()

set_property(TARGET ArdaCoreLib PROPERTY CXX_STANDARD 20)


# ArdaCore/CMakeLists.txt

# Crée une bibliothèque statique ArdaCore
add_library(ArdaCore
    Array.cpp
    DynamicArray.cpp
    String.cpp
    StringView.cpp
    # liste de tous tes .cpp de ArdaCore
)

# Inclure le dossier parent (car tu fais #include "ArdaCore/Core.h")
target_include_directories(ArdaCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}   # le dossier racine qui contient "ArdaCore/"
)