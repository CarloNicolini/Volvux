# Copyright (C) 2007-2009 LuaDist.
# Created by Peter Kapec <kapecp@gmail.com>
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
#	Note:
#		Searching headers and libraries is very simple and is NOT as powerful as scripts
#		distributed with CMake, because LuaDist defines directories to search for.
#		Everyone is encouraged to contact the author with improvements. Maybe this file
#		becomes part of CMake distribution sometimes.

# - Find FreeGLUT
# Find the native FreeGLUT headers and libraries.
#
#  FREEGLUT_INCLUDE_DIRS - where to find freeglut.h, etc.
#  FREEGLUT_LIBRARIES    - List of libraries when using FreeGLUT.
#  FREEGLUT_FOUND        - True if FreeGLUT found.

# Look for the header file.

#FIND_PATH(FREEGLUT_INCLUDE_DIR NAMES GL/freeglut.h)

FIND_PATH(
  FREEGLUT_INCLUDE_DIR GL/freeglut.h
  ${CMAKE_INCLUDE_PATH}
  $ENV{include}
  ${OPENGL_INCLUDE_DIR}
  /usr/include
  /usr/local/include
)

SET(STORE_CMAKE_FIND_FRAMEWORK ${CMAKE_FIND_FRAMEWORK})
SET(CMAKE_FIND_FRAMEWORK NEVER)

FIND_LIBRARY(
  FREEGLUT_LIBRARY
  NAMES freeglut_static freeglut glut
  PATH
    /opt/local/lib
    ${CMAKE_LIBRARY_PATH}
    $ENV{lib}
    /usr/lib
    /usr/local/lib
)

SET(CMAKE_FIND_FRAMEWORK ${STORE_CMAKE_FIND_FRAMEWORK})

IF (FREEGLUT_INCLUDE_DIR AND FREEGLUT_LIBRARY)
   SET(FREEGLUT_FOUND TRUE)
ENDIF (FREEGLUT_INCLUDE_DIR AND FREEGLUT_LIBRARY)

IF (FREEGLUT_FOUND)
   IF (NOT FREEGLUT_FIND_QUIETLY)
      MESSAGE(STATUS "Found FREEGLUT: ${FREEGLUT_LIBRARY}")
   ENDIF (NOT FREEGLUT_FIND_QUIETLY)
ELSE (FREEGLUT_FOUND)
   IF (FREEGLUT_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find FREEGLUT")
   ENDIF (FREEGLUT_FIND_REQUIRED)
ENDIF (FREEGLUT_FOUND)

MARK_AS_ADVANCED(FREEGLUT_INCLUDE_DIRS FREEGLUT_LIBRARIES)
