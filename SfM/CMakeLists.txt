cmake_minimum_required(VERSION 2.8)

project(SfM)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Set path for cmake finder
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake)

# Download and configure gtest
include(${PROJECT_SOURCE_DIR}/cmake/ConfigGTest.cmake)

# Find packages
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)

# Add include directories
include_directories(${CERES_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PORJECT_SOURCE_DIR}/ext/googletest-src/googletest/include)

# Add subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext)