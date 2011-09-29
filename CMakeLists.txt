cmake_minimum_required(VERSION 2.6)
project(g3test)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "-std=c++0x")

# Set the defines
# Build time define
include(GetDateTime)
DATETIME(BUILD_DATETIME)
add_definitions(-D_BUILD_DATE="${BUILD_DATETIME}")

# Git version info
include(GetGitRevisionDescription)
git_describe(GIT_DESCRIBE "--always")
add_definitions(-D_GIT_VERSION="${GIT_DESCRIBE}")

# Git SHA1 define
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
add_definitions(-D_GIT_SHA1="${GIT_SHA1}")

if(CMAKE_BUILD_TYPE MATCHES "Debug") 
   add_definitions(-D_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES "Debug") 

# Note this is the 'bad' way of doing this, but the recommended alternative is to keep a list of *all* source files =/
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# SFML
FIND_PACKAGE(SFML REQUIRED COMPONENTS System Window Graphics) 

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# For GL3/gl3.h
include_directories("${CMAKE_SOURCE_DIR}/external")

# Boost
find_package(Boost COMPONENTS filesystem system REQUIRED)
add_definitions(-D_BOOSTPTR)

# Final target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
