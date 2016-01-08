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

#ifndef VOLUMETRICSURFACEINTERSECTION_H
#define VOLUMETRICSURFACEINTERSECTION_H

#include <map>
#include "GLSL.h"
#include "Mathcommon.h"
#include "Util.h"
#include "GLUtils.h"
#include "Circle3D.h"
#include "Icosphere.h"
#include "ObjLoader2.h"

#define ICOSPHERE_LEVEL 6

class VolumetricSurfaceIntersection
{
public:
    VolumetricSurfaceIntersection();
    VolumetricSurfaceIntersection(unsigned int textureSizeX, unsigned int textureSizeY, unsigned int textureSizeZ);
    ~VolumetricSurfaceIntersection();

    // Resize the allocated vector of data and fill it with zeros
    void resize(unsigned int _sizeX, unsigned int _sizeY, unsigned int _sizeZ);
    void initializeSurfaceShaders(int surface);
    void loadSurfaceShaders(const std::string &vertexShaderName, const std::string &fragmentShaderName, const std::string &geometryShaderName);
    void initializeTexture();
    void fillVolumeWithSpheres( int nSpheres, int minRadius, int maxRadius );
    void fillVolumeWithRandomDots(int nRandomDots, int size);
    void setUniformColor(const GLfloat color[4]);
    void setTexture3DfillValue(int val);
    void loadTexture3DFile(const std::string &filename);
    void draw();

    static const int SurfaceParaboloid=0;
    static const int SurfaceEllipticCylinder=1;
    static const int SurfaceParabolicCylinder=2;
    static const int SurfaceEllipsoid=3;
    static const int SurfaceCone=4;
    static const int SurfaceCube=5;

    struct ParabolaParameters
    {
        double curvature;
        double centerX,centerY,centerZ;
        glsl::glShader *shader;
    } parabolaSurface;

    struct ParabolicCylinderParameters
    {
        double curvature;
        double centerX,centerY,centerZ;
        glsl::glShader *shader;
    } parabolicCylinderSurface;

    struct EllipticCylinderParameters
    {
        double axisX,axisZ;
        double height;
        glsl::glShader *shader;
    } ellipticCylinderSurface;

    struct EllipsoidParameters
    {
        double axisX,axisY,axisZ;
        glsl::glShader *shader;
    } ellipsoidSurface;

    struct ConeParameters
    {
        double c;
        glsl::glShader *shader;
    } coneSurface;

    struct CubeParameters
    {
        glsl::glShader *shader;
        double edge;
    } cubeSurface;

    const int getTextureSizeX() const;
    const int getTextureSizeY() const;
    const int getTextureSizeZ() const;
    const int getNSpheres() const;
    const int getSphereRadiusMin() const;
    const int getSphereRadiusMax() const;
    const int getTexture3DfillValue() const;

protected:
    GLfloat* uniformColor;
    vector<GLubyte> texture3DVolume;
    GLuint volume3DTextureID;
    int currentSurface;
    int textureSizeX;
    int textureSizeY;
    int textureSizeZ;
    bool useRandomSpheresColor;
    int texture3DfillValue;
    bool useOcclusionCulling;
    int nSpheres;
    int sphereRadiusMin;
    int sphereRadiusMax;

    std::map<int,Circle3D<int> > spheres;
    // Private methods
    void writeSpheresToTexture(int value);
};

#endif // VOLUMETRICSURFACEINTERSECTION_H

