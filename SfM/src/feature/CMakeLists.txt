set(targetname feature)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(sources "sift_test.cpp")

include(${PROJECT_SOURCE_DIR}/cmake/FindOpenImageIO.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindVlFeat.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/SetAppsTargetname.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/LinkOpenImageIO.cmake)
# include(${PROJECT_SOURCE_DIR}/cmake/LinkVlFeat.cmake)

# https://stackoverflow.com/questions/25617839/undefined-reference-to-symbol-pthread-key-deleteglibc-2-2-5
target_link_libraries(${targetname} vlfeat ${CMAKE_THREAD_LIBS_INIT})