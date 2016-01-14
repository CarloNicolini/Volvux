project(Volvux)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

################################ CMAKE OPTIONS ###############################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all libraries")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all executables")

####################### COMPILE OPTIONS  ##################################
option(QT4_SUPPORT "Compile the executable with Qt4 libraries" OFF)
option(QT5_SUPPORT "Compile the executable with Qt5 libraries" ON)
option(COMPILE_GLFW "Compile the GLFW library for OpenGL context creation" OFF)
option(COMPILE_GLEW "Compile the glew library from source" OFF)
option(COMPILE_FREEGLUT "Compile the FreeGLUT library from souce" OFF)

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

# 2. Try to find FreeGLUT or GLUT
if (NOT COMPILE_FREEGLUT)
    # On Apple use the system provided GLUT
    if(APPLE)
        include_directories( /System/Library/Frameworks )
        find_package(GLUT REQUIRED)
        find_library(GLUT_LIBRARY GLUT)
    endif(APPLE)
    # On Linux look for Freeglut
    if (UNIX)
        find_package(FreeGLUT REQUIRED)
    endif(UNIX)
else()
    # Include the FreeGLUT project for the necessary FreeGLUT implementation
    set(FREEGLUT_SRC_DIR "${PROJECT_SOURCE_DIR}/libs/FreeGLUT/freeglut/freeglut")
    # Override demos building http://stackoverflow.com/questions/3766740/overriding-a-default-option-value-in-cmake-from-a-parent-cmakelists-txt
    set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "Disable freeglut demos building")
    add_subdirectory(${FREEGLUT_SRC_DIR})
    include_directories(${FREEGLUT_SRC_DIR}/include/GL)
    set(GLUT_LIBRARIES "freeglut;${GLUT_LIBRARIES}")
endif()

# 3. Try to find GLFW
if(NOT COMPILE_GLFW)
    find_package(GLFW) #Looks for system-wise installed GLFW
    include_directories(${GLFW_INCLUDE_DIR})
    if (NOT GLFW_FOUND)
        message(FATAL_ERROR "GLFW not found in system. Please select compile GLFW from scratch.Set COMPILE_GLFW=True option.")
    endif()
else()
    # Override demos building http://stackoverflow.com/questions/3766740/overriding-a-default-option-value-in-cmake-from-a-parent-cmakelists-txt
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable glfw examples building")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable glfw tests building")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable glfw documentation building")
    set(GLFW_INSTALL OFF CACHE BOOL "Disable glfw installation")
    set(GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "Disable glfw internal documentation")
    # Now add glfw
    add_subdirectory("${PROJECT_SOURCE_DIR}/libs/glfw")
    set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libs/glfw/include")
    include_directories(${GLFW_INCLUDE_DIR})
endif(NOT COMPILE_GLFW)

# 4. Try to find GLEW
#if(NOT COMPILE_GLEW)
#    find_package(GLEW) #Looks for system-wise installed GLFW
#    include_directories(${GLEW_INCLUDE_DIR})
#    if (NOT GLEW_FOUND)
#        message(FATAL_ERROR "GLEW not found in system. Please select compile GLEW from scratch.Set COMPILE_GLEW=True option.")
#    endif()
#else() # compile glew 1.10 from cmake project source
#     add_subdirectory("${PROJECT_SOURCE_DIR}/libs/glew-1.10.0-src/")
#     set(GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libs/glew-1.10.0-src/include")
#     include_directories(${GLEW_INCLUDE_DIR})
#    if (WIN32)
#        set(GLEW_LIBRARY glew32)
#    endif(WIN32)
#endif(NOT COMPILE_GLEW)

# 5. Try to find Qt4 
#if(QT4_SUPPORT)
#    set(QT_MIN_VERSION "4.7.0")
#    set(QT_USE_QTMAIN TRUE)
#    set(QT_USE_OPENGL TRUE)
#    find_package(Qt4 ${QT_MIN_VERSION} COMPONENTS QtGui QtCore QtOpenGL REQUIRED )
#    include(${QT_USE_FILE})
#    include_directories(${QT_INCLUDE_PATH} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})
#endif(QT4_SUPPORT)

# 6. Try to find Boost
find_package(Boost)# COMPONENTS ${BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
#add_definitions("DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED")


# 7. Include Eigen
include_directories(libs/eigen)

# 8. Include the Smart Motor interfaces and ALP support *ONLY* on Windows
if(WIN32)
    MESSAGE(STATUS "MSVC_VERSION=${MSVC_VERSION}")
    # This set the following defines when compiling on windows
        if(MSVC)
        add_definitions("-D_WIN32 -DNOMINMAX /EHsc /wd4127 /wd4129 /wd4505 /wd4714 /wd4800 /wd4181 /wd4244 /wd4996 /wd4250 -D_WIN32_WINNT=0x0501")
		add_definitions("-DUNICODE")
		add_definitions("-D_UNICODE")
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


## 9. Qt5 support
if (QT5_SUPPORT)
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
endif(QT5_SUPPORT)

# 9. Disable stupid warnings on GCC
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
endif()

# 9. Finally add the project directory
add_subdirectory(src)
include_directories(src)
