// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2010-2014 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.


#include "GLUtils.h"

#include "Util.h"
#include "Mathcommon.h"
#include "Imageloader.h"
#include "Grid.h"
#include "Circle.h"
#include "Circle3D.h"


/**
 * @brief glError Query GL status and get an error, the error with name a filename+line is printed on standard error
 * @param file
 * @param line
 */
void glError(const char *file, int line)
{
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {  const GLubyte* sError = gluErrorString(glErr);

        if (sError)
            cerr << "GL Error #" << glErr << "(" << gluErrorString(glErr) << ") " << " in File " << file << " at line: " << line << endl;
        else
            cerr << "GL Error #" << glErr << " (no message available)" << " in File " << file << " at line: " << line << endl;

        retCode = 1;
        glErr = glGetError();
    }
}
