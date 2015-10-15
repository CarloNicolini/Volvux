project(Volvux)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
################################ CMAKE OPTIONS ###############################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all libraries")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all executables")

#add_definitions("-DCNCSVISION_BASE_DIRECTORY")
####################### COMPILE OPTIONS  ##################################
option(BUILD_SHARED_LIBS OFF)
option(QT4_SUPPORT "Compile the executable with Qt4 libraries" TRUE)
option(QT5_SUPPORT "Compile the executable with Qt5 libraries" FALSE)
option(COMPILE_GLFW "Compile the GLFW library for OpenGL context creation" OFF)
####################### FIND PACKAGES AND LIBRARIES ####################
find_package(StandardMathLibrary)
if(WIN32)
    option(ALP_SUPPORT "Include and link ALP projector libraries (Win32 only)" OFF)
    option(SMI_SUPPORT "Include and link Smart Motor Interface" OFF)

    if(ALP_SUPPORT)
    find_package(ALP)
    add_definitions("-DALP_SUPPORT")
    set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} /LARGEADDRESSAWARE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
    message(STATUS "MSVC: Enabled large address awareness")
    endif(ALP_SUPPORT)

    if(SMI_SUPPORT)
    find_package(SmartMotor)
    endif(SMI_SUPPORT)
endif(WIN32)

# # Support for GLW, please keep it up-to-date running a git pull on "src/glfw"
# if(COMPILE_GLFW)
#     # See http://www.glfw.org/docs/latest/build.html
#     add_subdirectory("${PROJECT_SOURCE_DIR}/src/glfw")
#     set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/glfw/include")
#     # "if The Xf86VidMode library and headers were not found"
#     # On Ubuntu 12.04 LTS need to install
#     # sudo apt-get install xorg-dev  libglu1-mesa-dev
#     include_directories(${GLFW_INCLUDE_DIR})
# endif(COMPILE_GLFW)
if (QT5_SUPPORT)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})
# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})
# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
# Enable the C++11 standard
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
endif(QT5_SUPPORT)

######################## QT4 ########################
if(QT4_SUPPORT)
    set(QT_MIN_VERSION "4.8.0")
    set(QT_USE_QTMAIN TRUE)
    set(QT_USE_OPENGL TRUE)
    find_package(Qt4 ${QT_MIN_VERSION} COMPONENTS QtGui QtCore QtOpenGL REQUIRED )
    include(${QT_USE_FILE})
    include_directories(${QT_INCLUDE_PATH} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})
endif(QT4_SUPPORT)

####################### BOOST #######################
find_package(Threads REQUIRED)
message(STATUS "Using ${CMAKE_THREAD_LIBS_INIT} threading library")
set(BOOST_LIBS regex iostreams)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Find GLEW
find_package(GLEW)
if(NOT GLEW_FOUND)
  message (FATAL_ERROR "GLEW not found! CNCSVision needs GLEW libraries in order to support advanced rendering options.")
endif()

# Include the GLFW project for the necessary GLFW implementation
add_subdirectory(libs/glfw)

# Include OpenGL and FreeGLUT stuff
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
# Include the FreeGLUT project for the necessary FreeGLUT implementation
add_subdirectory(libs/freeglut)

# Finally add the project directory
add_subdirectory(src)
include_directories(src)
