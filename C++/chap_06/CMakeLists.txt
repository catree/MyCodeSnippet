cmake_minimum_required(VERSION 3.0)

project(GradeBook)

file(GLOB gradebook_src GradeBook.* main.cpp)

add_executable(gradebook_main ${gradebook_src})

add_executable(scope scope.cpp)