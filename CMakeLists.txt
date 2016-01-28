project(Volvux)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

################################ CMAKE OPTIONS ###############################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all libraries")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all executables")

####################### COMPILE OPTIONS  ##################################
option(QT5_SUPPORT "Compile the executable with Qt5 libraries" ON)

####################### FIND PACKAGES AND LIBRARIES ####################
set(CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_COMPILER_FLAGS} -Wall")
# 1. Try to find the StandardMathLibrary standard package
#find_package(StandardMathLibrary)

# 1. Try to find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found in system. Please install an OpenGL driver on the system.")
endif()

# 2. Include Eigen
include_directories(libs/eigen)

# 3. Include the Smart Motor interfaces and ALP support *ONLY* on Windows
if(WIN32)
    MESSAGE(STATUS "MSVC_VERSION=${MSVC_VERSION}")
    # This set the following defines when compiling on windows
        if(MSVC)
        add_definitions("-D_WIN32 -DNOMINMAX /EHsc /wd4127 /wd4129 /wd4505 /wd4714 /wd4800 /wd4181 /wd4244 /wd4996 /wd4250 -D_WIN32_WINNT=0x0501 -DUNICODE -D_UNICODE")
        endif(MSVC)

    IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message(STATUS "Compiling in Debug mode")
        add_definitions("/Wall")
    ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

    if( NOT SMI_SUPPORT)
        if(MSVC)
        add_definitions("/MP") #disable multiprocessor compilation when including Smart Motor
        endif(MSVC)
    endif(NOT SMI_SUPPORT)
    option(ALP_SUPPORT "Include and link ALP projector libraries (Win32 only)" OFF)
    option(SMI_SUPPORT "Include and link Smart Motor Interface" OFF)
    # ALP Support
    if(ALP_SUPPORT)
        find_package(ALP)
        add_definitions("-DALP_SUPPORT")
        set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} /LARGEADDRESSAWARE")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
        message(STATUS "MSVC: Enabled large address awareness")
    endif(ALP_SUPPORT)

    # Smart Motors Support
    if(SMI_SUPPORT)
        add_definitions("-DSMI_SUPPORT")
        find_package(SmartMotor)
    endif(SMI_SUPPORT)
endif(WIN32)


## 4. Use Qt5

if (WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/5.5/msvc2012/lib/cmake/")
endif()
if(NOT CMAKE_PREFIX_PATH)
    message(FATAL_ERROR "Must specify where Qt5 modules are to be found. Use cmake -DCMAKE_PREFIX_PATH=/path/to/cmakeqt5modules")
endif()
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5Gui)
# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
# Enable the C++11 standard
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++11)
message(STATUS "Found Qt5 include directories: ${Qt5Widgets_INCLUDE_DIRS}")
message(STATUS "Found Qt5 libs directories: ${Qt5Widgets_LIBRARIES}")


# 5. Disable stupid warnings on GCC
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
endif()

# 6. Finally add the project directory
add_subdirectory(src)
include_directories(src)
