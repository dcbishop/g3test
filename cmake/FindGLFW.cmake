# - Find GLFW library
# Find the native GLFW includes and library
# This module defines
#   GLFW_INCLUDE_DIR, where to find GL/glfw.h
#   GLFW_LIBRARIES libraries to link against to use GLFW
#   GLFW_FOUND If false, do not try to use GLFW
# $GLFWDIR is an environment variable that would correspond
# to the prefix used to configure GLFW.
#
# Created by Olivier Delannoy. This was influenced by
# FindOpenAL.cmake module. MACOSX is not yet handled correctly


# TODO parse pkg-config output
FIND_PATH(GLFW_INCLUDE_DIR GL/glfw.h
    $ENV{GLFWDIR}/include
    ~/Library/Frameworks/GLFW.framework/Headers
    /Library/Frameworks/GLFW.framework.Headers # Tiger
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
)
FIND_LIBRARY(GLFW_LIBRARIES NAMES glfw PATHS
    $ENV{GLFWDIR}/lib
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib
    /opt/X11/lib
    /opt/lib
)

SET(GLFW_FOUND "NO")
IF (GLFW_LIBRARIES)
    SET(GLFW_FOUND "YES")
ENDIF(GLFW_LIBRARIES)
MARK_AS_ADVANCED(GLFW_LIBRARIES GLFW_INCLUDE_DIR)
