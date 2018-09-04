set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)

file(GLOB SFM_GEOMETRY_HEADER *.h)
file(GLOB SFM_GEOMETRY_CPP *.cpp)

file(GLOB UNIT_TEST_FILE *_test.cpp)
# set(SFM_GEOMETRY_HEADER
#     Homography.h
#     Ransac.h
#     # RansacHomography.h
#     )

# set(SFM_GEOMETRY_CPP
#     Homography.cpp
#     Ransac.cpp
#     # RansacHomography.cpp
#     )

list(REMOVE_ITEM SFM_GEOMETRY_CPP ${UNIT_TEST_FILE})

add_library(sfm_geometry 
            SHARED
            ${SFM_GEOMETRY_HEADER} 
            ${SFM_GEOMETRY_CPP})
target_link_libraries(sfm_geometry ${CERES_LIBRARIES})

add_executable(RansacHomography_test RansacHomography_test.cpp)

target_link_libraries(RansacHomography_test 
                      sfm_geometry)