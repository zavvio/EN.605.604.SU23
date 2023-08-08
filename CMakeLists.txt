# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("EN.605.604.SU23")

# Include sub-projects.
add_subdirectory ("EN.605.604.SU23_Assignment1")
add_subdirectory ("EN.605.604.SU23_Assignment2_P1")
add_subdirectory ("EN.605.604.SU23_Assignment2_P2")
add_subdirectory ("EN.605.604.SU23_Assignment3")
add_subdirectory ("EN.605.604.SU23_Assignment4_P1")
add_subdirectory ("EN.605.604.SU23_Assignment4_P2")
add_subdirectory ("EN.605.604.SU23_Assignment5_P1")
add_subdirectory ("EN.605.604.SU23_Assignment5_P2")
add_subdirectory ("EN.605.604.SU23_Project1")
add_subdirectory ("EN.605.604.SU23_Project2")
