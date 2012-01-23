cmake_minimum_required(VERSION 2.6)

# Project name
project( g3test )

# Projects default options
option( Debug          "Debug"        	OFF )
option( Profile        "Profile"      	OFF )
option( C++11          "C++11"        	ON  )
option( USE_BOOST      "USE_BOOST"    	ON  )
option( USE_OPENGL     "USE_OPENGL"   	ON  )
option( USE_GL3H       "USE_GL3H"      ON  )
option( USE_GLEW       "USE_GLEW"      ON  )
option( USE_QT         "USE_QT"        ON  )
option( USE_GLFW       "USE_GLFW"      OFF )
option( USE_SFML       "USE_SFML"      OFF )
option( USE_GLUT       "USE_GLUT"      OFF )

# Set cmake module path
set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

# Add custom debug build compiler flags here...
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

# Set debug build type as default
if (NOT CMAKE_BUILD_TYPE)
   message(STATUS "No build type specified, defaulting to Debug")
   set(CMAKE_BUILD_TYPE "Debug")
endif()

# Ensure that setting the debug option also sets the build type and visaversa
if(Debug)
   set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
   option(Debug "Debug" ON)
endif()

# Set _DEBUG #define for project
if(Debug)
   add_definitions(-D_DEBUG)
endif()

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
   message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
else(CMAKE_BUILD_TYPE)
   add_definitions(-DBUILD_TYPE_="Default")
   message(STATUS "Unspecified build type")
endif(CMAKE_BUILD_TYPE)

# Git SHA1 define
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
add_definitions(-DGIT_SHA1_="${GIT_SHA1}")

# Add debug define
if(CMAKE_BUILD_TYPE MATCHES "Debug") 
   add_definitions(-D_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES "Debug") 

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

# OpenGL
if(USE_OPENGL)
   find_package(OpenGL REQUIRED)
   if(OPENGL_FOUND)
      add_definitions(-DHAVE_OPENGL)
      set(COMMON_LIBS ${COMMON_LIBS} ${OPENGL_LIBRARIES})
   endif()
endif()

# For GL3/gl3.h
if(USE_GL3H)
   include_directories("${CMAKE_SOURCE_DIR}/external")
   add_definitions(-DUSE_GL3H)
   message(STATUS "Using gl3.h")
endif()

# GLEW
if(USE_GLEW)
   find_package(GLEW REQUIRED)
   if(GLEW_FOUND)
      set(COMMON_LIBS ${COMMON_LIBS} ${GLEW_LIBRARIES})
      add_definitions(-DHAVE_GLEW)
      add_definitions(-DUSE_GLEW)
   endif()
endif()

# Add Boost libs
if(USE_BOOST)
   find_package(Boost COMPONENTS filesystem system REQUIRED)
   if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
      add_definitions(-DHAVE_BOOST)
      #target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
      set(COMMON_LIBS ${COMMON_LIBS} ${Boost_LIBRARIES})
   endif()
endif()

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

# Specify the sources for specific build targets
set(QT_SOURCES "${CMAKE_SOURCE_DIR}/src/Application/QTApplication.cpp" ${qt_CPP})
set(SFML_SOURCES "${CMAKE_SOURCE_DIR}/src/Application/SFMLApplication.cpp")
set(GLUT_SOURCES "${CMAKE_SOURCE_DIR}/src/Application/GLUTApplication.cpp")
set(GLFW_SOURCES "${CMAKE_SOURCE_DIR}/src/Application/GLFWApplication.cpp")

# Remove specific build target sources
list(REMOVE_ITEM SOURCES ${QT_SOURCES} ${SFML_SOURCES} ${GLUT_SOURCES} ${GLFW_SOURCES})

# QT target
if(USE_QT)
   find_package(Qt4 4.6 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
   include(${QT_USE_FILE})
   QT4_WRAP_CPP(QT_SOURCES ${qt_HPP})

   if(QT4_FOUND)
      set(QT_PROJECT_NAME "${PROJECT_NAME}-qt")
      add_executable(${QT_PROJECT_NAME} ${QT_SOURCES} ${SOURCES})
      target_link_libraries(${QT_PROJECT_NAME} ${QT_LIBRARIES} ${COMMON_LIBS})
      set_target_properties(${QT_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_QT")
   endif()
endif()

# SFML target
if(USE_SFML)
   find_package(SFML REQUIRED COMPONENTS System Window Graphics)
   if(SFML_FOUND)
      set(SFML_PROJECT_NAME "${PROJECT_NAME}-sfml")
      add_executable(${SFML_PROJECT_NAME} ${SFML_SOURCES} ${SOURCES})
      target_link_libraries(${SFML_PROJECT_NAME} ${COMMON_LIBS} ${SFML_LIBRARIES})
      set_target_properties(${SFML_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_SFML")
   endif()
endif()

# GLFW target
if(USE_GLFW)
   find_package(GLFW REQUIRED)
   if(GLFW_FOUND)
      set(GLFW_PROJECT_NAME "${PROJECT_NAME}-glfw")
      add_executable(${GLFW_PROJECT_NAME} ${GLFW_SOURCES} ${SOURCES})
      target_link_libraries(${GLFW_PROJECT_NAME} ${COMMON_LIBS} ${GLFW_LIBRARIES})
      set_target_properties(${GLFW_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_GLFW")
   endif()
endif()

# Glut target
if(USE_GLUT)
   find_package(GLUT REQUIRED)
   if(GLUT_FOUND)
      set(GLUT_PROJECT_NAME "${PROJECT_NAME}-glut")
      add_executable(${GLUT_PROJECT_NAME} ${GLUT_SOURCES} ${SOURCES})
      target_link_libraries(${GLUT_PROJECT_NAME} ${COMMON_LIBS} ${GLUT_LIBRARIES})
      set_target_properties(${GLUT_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_GLUT")
   endif()
endif()
