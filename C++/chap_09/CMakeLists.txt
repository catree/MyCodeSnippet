cmake_minimum_required(VERSION 3.0)

project(chap_09)

file(GLOB create_and_destroy_src *.h *.cpp)
add_executable(main_create_and_destroy ${create_and_destroy_src})
