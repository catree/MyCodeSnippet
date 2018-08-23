cmake_minimum_required(VERSION 3.0)
project(CERES_PRACTICE)

set(CMAKE_CXX_FLAGS="-std=c++11")

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

add_subdirectory(src)
