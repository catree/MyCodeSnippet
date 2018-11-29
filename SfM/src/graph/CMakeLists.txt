set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)

file (GLOB SFM_GRAPH_HEADER *.h)
file (GLOB SFM_GRAPH_CPP *.cpp)

file(GLOB UNIT_TEST_FILE *_test.cpp)

list(REMOVE_ITEM SFM_GRAPH_CPP ${UNIT_TEST_FILE})

add_executable(graph_test Graph_test.cpp)
target_link_libraries(graph_test gtest_main)

enable_testing()
add_test(NAME graph_test COMMAND graph_test)


add_library(sfm_graph
            ${SFM_GRAPH_HEADER}
            ${SFM_GRAPH_CPP})   