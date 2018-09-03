cmake_minimum_required(VERSION 3.0)

project(SfM)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Eigen3 REQUIRED)

include_directories("/usr/include/eigen3")

add_subdirectory(src)