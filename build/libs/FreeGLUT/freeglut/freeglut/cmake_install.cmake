# Install script for directory: /home/hololab/workspace/Volvux/libs/FreeGLUT/freeglut/freeglut

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so.3.10.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/lib/libglut.so.3.10.0"
    "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/lib/libglut.so.3"
    "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/lib/libglut.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so.3.10.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglut.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/lib/libglut.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GL" TYPE FILE FILES
    "/home/hololab/workspace/Volvux/libs/FreeGLUT/freeglut/freeglut/include/GL/freeglut.h"
    "/home/hololab/workspace/Volvux/libs/FreeGLUT/freeglut/freeglut/include/GL/freeglut_ext.h"
    "/home/hololab/workspace/Volvux/libs/FreeGLUT/freeglut/freeglut/include/GL/freeglut_std.h"
    "/home/hololab/workspace/Volvux/libs/FreeGLUT/freeglut/freeglut/include/GL/glut.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE RENAME "freeglut.pc" FILES "/home/hololab/workspace/Volvux/build/freeglut.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake"
         "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets-debug.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES
    "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/FreeGLUT/FreeGLUTConfig.cmake"
    "/home/hololab/workspace/Volvux/build/libs/FreeGLUT/freeglut/freeglut/FreeGLUT/FreeGLUTConfigVersion.cmake"
    )
endif()

