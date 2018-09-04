file(GLOB SFM_GEOMETRY_SRC *.h *.cpp)

add_library(sfm_geometry ${SFM_GEOMETRY_SRC})
target_link_libraries(geometry ${CERES_LIBRARIES})