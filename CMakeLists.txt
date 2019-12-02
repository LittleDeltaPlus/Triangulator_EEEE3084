cmake_minimum_required(VERSION 3.15)
project(Triangulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc src)
add_library(VectorMath src/Vec3.cpp inc/Vec3.h src/Triangle.cpp inc/Triangle.h inc/VecList.h src/VecList.cpp inc/Matrix.h src/Matrix.cpp)
add_executable(Triangulator src/main.cpp)
target_link_libraries(Triangulator VectorMath)