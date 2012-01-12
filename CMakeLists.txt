cmake_minimum_required(VERSION 2.6)
project(g3test)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

option(Profile "Profile" OFF)

# Set the defines
# Build time define
include(GetDateTime)
DATETIME(BUILD_DATETIME)
add_definitions(-DBUILD_DATE_="${BUILD_DATETIME}")

# Git version info
include(GetGitRevisionDescription)
git_describe(GIT_DESCRIBE "--always")
add_definitions(-DGIT_VERSION_="${GIT_DESCRIBE}")

# Build type
if(CMAKE_BUILD_TYPE)
   add_definitions(-DBUILD_TYPE_="${CMAKE_BUILD_TYPE}")
   message("Build type: ${CMAKE_BUILD_TYPE}...")
else(CMAKE_BUILD_TYPE)
   add_definitions(-DBUILD_TYPE_="Default")
   message("Default build type...")
endif(CMAKE_BUILD_TYPE)

# Git SHA1 define
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
add_definitions(-DGIT_SHA1_="${GIT_SHA1}")

# Add debug define
if(CMAKE_BUILD_TYPE MATCHES "Debug") 
   add_definitions(-D_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES "Debug") 

# Add custom debug build compiler flags here...
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

# GCC specific flags...
if(CMAKE_COMPILER_IS_GNUCC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Werror") #-Weffc++
   
   if(Profile)
      message("Profiling: ON...")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg") 
   endif(Profile)
endif(CMAKE_COMPILER_IS_GNUCC)

# Note this is the 'bad' way of doing this, but the recommended alternative is to keep a list of *all* source files =/
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# SFML
FIND_PACKAGE(SFML REQUIRED COMPONENTS System Window Graphics) 

# GLFW
find_package(GLFW REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# For GL3/gl3.h
include_directories("${CMAKE_SOURCE_DIR}/external")

# Boost
find_package(Boost COMPONENTS filesystem system REQUIRED)
add_definitions(-D_BOOSTPTR)

# TODO: Starting with CMAKE 2.8.6 there is automoc.
# See: http://blogs.kde.org/node/4495
#set(CMAKE_AUTOMOC TRUE)

# Add files that need to be run through the QT moc.
set(qt_CPP
   "${CMAKE_SOURCE_DIR}/src/Application/QTWidgets/Widget.cpp"
   "${CMAKE_SOURCE_DIR}/src/Application/QTWidgets/GLWidget.cpp"
)

set(qt_HPP 
   "${CMAKE_SOURCE_DIR}/src/Application/QTWidgets/Widget.hpp"
   "${CMAKE_SOURCE_DIR}/src/Application/QTWidgets/GLWidget.hpp"
)

# Remove the QT moc source files from compilation.
list(REMOVE_ITEM SOURCES $qt_CPP)

# QT
find_package(Qt4 4.6 COMPONENTS QtCore QtGui QtOpenGL QtWebKit REQUIRED)
include(${QT_USE_FILE})
QT4_WRAP_CPP(SOURCES ${qt_HPP})

# Final target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${QT_LIBRARIES} ${SFML_LIBRARIES} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES})
