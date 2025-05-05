cmake_minimum_required (VERSION 3.29.5)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ArdaCoreLib")

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "*.cpp"
)

# Add Files to ArdaCore 
set(ArdaCoreLibTarget ArdaCore)
add_library(${ArdaCoreLibTarget}
		${SRC}
  "Core.h" "Assert.h" "DynamicArray.cpp")

if (MSVC)
	target_compile_options(${ArdaCoreLibTarget} PRIVATE /MP)	# Multithread compilation
else() # Clang or GCC
	message("Not MSVC software, not managed")
endif()