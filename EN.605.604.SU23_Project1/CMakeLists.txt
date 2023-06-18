# CMakeList.txt : CMake project for EN.605.604.SU23_Project1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EN.605.604.SU23_Project1 "EN.605.604.SU23_Project1.cpp" "Merchandise.h" "Merchandise.cpp" "Configurations.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EN.605.604.SU23_Project1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
