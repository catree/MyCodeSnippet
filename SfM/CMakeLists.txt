cmake_minimum_required(VERSION 2.8)

project(SfM)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
# add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext)