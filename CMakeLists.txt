cmake_minimum_required(VERSION 3.5)
project(SFM)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(ImageLoader SHARED src/ImageLoader.cpp)
add_library(FeatureManager SHARED src/FeatureManager.cpp)
add_library(GMSMatcher SHARED src/GMSMatcher.cpp)

add_executable(main src/main.cpp)

target_link_libraries(main ImageLoader FeatureManager GMSMatcher ${OpenCV_LIBS})