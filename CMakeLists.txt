FIND_PACKAGE(OpenGL REQUIRED)
TARGET_LINK_LIBRARIES(${targetname} ${OPENGL_LIBRARY} ${OPENGL_LIBRARIES})

###################
# UseGLUT.cmake #
###################

IF(MSVC_IDE)
  FIND_PATH(GLUT_ROOT Readme.txt HINTS "${PROJECT_SOURCE_DIR}/freeglut")
  FIND_LIBRARY(GLUT_LIBRARY freeglut HINTS "${GLUT_ROOT}/lib/x64")
  FIND_PATH(GLUT_INCLUDE_DIR GL/glut.h HINTS "${GLUT_ROOT}/include")
ELSEIF(APPLE)
  FIND_PACKAGE(GLUT REQUIRED)
ELSEIF("${CMAKE_SYSTEM}" MATCHES "Linux")
  FIND_LIBRARY(GLUT_LIBRARY glut HINTS "/usr/lib/x86_64-linux-gnu")
  FIND_PATH(GLUT_INCLUDE_DIR glut.h HINTS "/usr/include/GL")
ENDIF()

INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})


##################
# LinkGLUT.cmake #
##################

TARGET_LINK_LIBRARIES(${targetname} ${GLUT_LIBRARY})

IF(MSVC_IDE)
  ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GLUT_ROOT}/bin/x64/freeglut.dll" "$<TARGET_FILE_DIR:${targetname}>")
ENDIF()


OPTION(WITH_GLFW "Build with GLFW support: " TRUE)

IF(WITH_GLFW)
    MESSAGE(STATUS "Build with GLFW support: TRUE")
    FIND_PATH(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h
    PATHS /usr/X11R6/include
        /usr/include/X11
        /opt/graphics/OpenGL/include
        /opt/graphics/OpenGL/contrib/libglfw
        /usr/local/include
        /usr/include/GL
        /usr/include)

    FIND_LIBRARY(GLFW_LIBRARIES NAMES glfw glfw3
    PATHS /usr/lib64
            /usr/lib
            /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}
            /usr/local/lib64
            /usr/local/lib
            /usr/local/lib/${CMAKE_LIBRARY_ARCHITECTURE}
            /usr/X11R6/lib)
    INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIR})
ELSE()
    MESSAGE(STATUS "Build with GLFW support: FALSE")
ENDIF()

IF(WITH_GLFW)
    TARGET_LINK_LIBRARIES(${targetname} ${GLFW_LIBRARIES})
ENDIF()

################
# UsePNG.cmake #
################

OPTION(WITH_PNG "Build with libpng support?" OFF)

IF(WITH_PNG)
  MESSAGE(STATUS "Build with libpng support: ON")
  FIND_PACKAGE(PNG REQUIRED)

  INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})
  ADD_DEFINITIONS(${PNG_DEFINITIONS})
  ADD_DEFINITIONS(-DUSE_LIBPNG)
ELSE()
  MESSAGE(STATUS "Build with libpng support: OFF")
ENDIF()

#################
# LinkPNG.cmake #
#################

IF(WITH_PNG)
  TARGET_LINK_LIBRARIES(${targetname} ${PNG_LIBRARIES})
ENDIF()


OPTION(WITH_JPEG "Build with libjpeg support?" OFF)

IF(WITH_JPEG)
    MESSAGE(STATUS "Build with libjpeg support: ON")
    FIND_PACKAGE(JPEG REQUIRED)

    IF(JPEG_FOUND)
        MESSAGE(STATUS "JPEG found in " ${JPEG_INCLUDE_DIR})
        INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
        ADD_DEFINITIONS(${JPEG_DEFINITIONS})
        ADD_DEFINITIONS(-DUSE_LIBJPEG)
    ELSE()
        MESSAGE(STATUS "Use jpeg declared, but jpeg not found")
    ENDIF()
ELSE()
    MESSAGE(STATUS "Build with libjpeg support: OFF")
ENDIF()

IF(WITH_JPEG)
    MESSAGE(STATUS ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES(${targetname} ${JPEG_LIBRARIES})
ENDIF()
