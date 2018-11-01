set(targetname feature)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(headers Sift.h Feature.h)
set(sources Sift.cpp Feature.cpp)

include(${PROJECT_SOURCE_DIR}/cmake/FindOpenImageIO.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindVlFeat.cmake)


# set target name
include(${PROJECT_SOURCE_DIR}/cmake/SetLibsTargetname.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/LinkOpenImageIO.cmake)

# https://stackoverflow.com/questions/25617839/undefined-reference-to-symbol-pthread-key-deleteglibc-2-2-5
target_link_libraries(${targetname} 
                      vlfeat 
                      image 
                      ${CMAKE_THREAD_LIBS_INIT})


# executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
if(WITH_OPENCV)
    include(${PROJECT_SOURCE_DIR}/cmake/UseOpenCV.cmake)
endif()

add_executable(sift_test sift_test.cpp)

if(WITH_OPENCV)
    include(${PROJECT_SOURCE_DIR}/cmake/LinkOpenCV.cmake)
endif()
target_link_libraries(sift_test image feature)   