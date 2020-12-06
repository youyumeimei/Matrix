cmake_minimum_required(VERSION 3.14.5)
project(assignment)

set(CMAKE_CXX_STANDARD 14)

add_executable(mat matrix.cpp useMatrix.cpp)
add_executable(thr matrix.cpp matrix_thread.cpp)
