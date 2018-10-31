set(targetname feature)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(headers Sift.h)
set(sources Sift.cpp)

include(${PROJECT_SOURCE_DIR}/cmake/FindOpenImageIO.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindVlFeat.cmake)

# include(${PROJECT_SOURCE_DIR}/cmake/SetAppsTargetname.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SetLibsTargetname.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/LinkOpenImageIO.cmake)

# https://stackoverflow.com/questions/25617839/undefined-reference-to-symbol-pthread-key-deleteglibc-2-2-5
target_link_libraries(${targetname} 
                      vlfeat 
                      image 
                      ${CMAKE_THREAD_LIBS_INIT})


# executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(sift_test sift_test.cpp)
target_link_libraries(sift_test image feature)   