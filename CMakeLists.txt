cmake_minimum_required(VERSION 3.10)
project(Tinker)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(Tinker main.cpp Worker1.cpp Worker1.h Worker2.cpp Worker2.h)
target_link_libraries(Tinker ${OpenCV_LIBS} )
