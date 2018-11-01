set(targetname image)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(headers ImageProcess.h Image.h)
set(sources ImageProcess.cpp Image.cpp)

include(${PROJECT_SOURCE_DIR}/cmake/FindOpenImageIO.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/SetLibsTargetname.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/LinkOpenImageIO.cmake)