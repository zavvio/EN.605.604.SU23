# CMakeList.txt : CMake project for EN.605.604.SU23_Assignment5, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EN.605.604.SU23_Assignment5_P2 "EN.605.604.SU23_Assignment5_P2.cpp" "Song.h" "Song.cpp" "DevUtil.h" "Date.cpp" "Date.h" "SerializableSong.cpp" "Serializable.h" "SerializableSong.h" "SerializableDate.cpp" "SerializableDate.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EN.605.604.SU23_Assignment5_P2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
