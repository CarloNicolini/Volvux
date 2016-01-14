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

#include "VolumetricSurfaceIntersection.h"
// Needed for fast generation of grid of points as domain for the surfaces
#include "Grid.h"
// Needed for fast generation of an Icosphere, triangulated sphere

// The constructor allocates the memory once, which is the heaviest operation
/**
 * @brief VolumetricSurfaceIntersection::VolumetricSurfaceIntersection
 * @param _sizeX
 * @param _sizeY
 * @param _sizeZ
 */
VolumetricSurfaceIntersection::VolumetricSurfaceIntersection(unsigned int _sizeX, unsigned int _sizeY, unsigned int _sizeZ) : textureSizeX(_sizeX),textureSizeY(_sizeY),textureSizeZ(_sizeZ),volume3DTextureID(0),uniformColor(NULL),currentSurface(-1)
{
    useRandomSpheresColor=false;
    texture3DfillValue=0;
    this->uniformColor = new GLfloat[4];

    for (int i=0; i<4;i++)
        this->uniformColor[i]=1.0;

    // http://pinyotae.blogspot.it/2009/06/note-on-boost-multidimensional-array.html
    texture3DVolume.resize(textureSizeX*textureSizeY*textureSizeZ);

    memset(&(texture3DVolume.at(0)),texture3DfillValue,sizeof(GLubyte)*textureSizeX*textureSizeY*textureSizeZ);
}

/**
 * @brief VolumetricSurfaceIntersection::VolumetricSurfaceIntersection
 */
VolumetricSurfaceIntersection::VolumetricSurfaceIntersection() : volume3DTextureID(0), uniformColor(NULL), currentSurface(-1)
{
    useRandomSpheresColor=false;
    texture3DfillValue=0;
    this->uniformColor = new GLfloat[4];
    for (int i=0; i<4;i++)
        this->uniformColor[i]=1.0;

    this->volume3DTextureID=0;
}

/**
 * @brief VolumetricSurfaceIntersection::resize
 * @param sizeX
 * @param sizeY
 * @param sizeZ
 */
void VolumetricSurfaceIntersection::resize(unsigned int _sizeX, unsigned int _sizeY, unsigned int _sizeZ)
{
    this->textureSizeX = _sizeX;
    this->textureSizeY = _sizeY;
    this->textureSizeZ = _sizeZ;
    texture3DVolume.clear();
    texture3DVolume.resize(textureSizeX*textureSizeY*textureSizeZ);
    memset(&(texture3DVolume.at(0)),texture3DfillValue,sizeof(GLubyte)*textureSizeX*textureSizeY*textureSizeZ);
}

/**
 * @brief VolumetricSurfaceIntersection::~VolumetricSurfaceIntersection
 */
VolumetricSurfaceIntersection::~VolumetricSurfaceIntersection()
{
    if (this->volume3DTextureID)
        glDeleteTextures(1,&(this->volume3DTextureID));
    //    if (texture3DVolume)
    //        delete texture3DVolume;
    if (uniformColor)
        delete[] uniformColor;
}

/**
* @brief  VolumetricSurfaceIntersection::setUniformColor
* @param color
**/
void VolumetricSurfaceIntersection::setUniformColor(const GLfloat color[4])
{
    if (!uniformColor)
    {
        uniformColor = new GLfloat[4];
    }
    for (int i=0; i<4;i++)
        this->uniformColor[i]=color[i];
}

/**
 * @brief VolumetricSurfaceIntersection::fillVolumeWithSpheres
 * @param nSpheres
 * @param minRadius
 * @param maxRadius
 */
void VolumetricSurfaceIntersection::fillVolumeWithSpheres( int nSpheres, int minRadius, int maxRadius)
{
    this->nSpheres = nSpheres;
    this->sphereRadiusMin = minRadius;
    this->sphereRadiusMax = maxRadius;

    if ( texture3DVolume.empty() )
        this->resize(this->textureSizeX,this->textureSizeY,this->textureSizeZ);
    memset(&(texture3DVolume.at(0)),texture3DfillValue,sizeof(GLubyte)*textureSizeX*textureSizeY*textureSizeZ);
    // This is a bogus algorithm to avoid intersecting spheres, it can be done better by means
    // of intersection graph and maximal independent set but it need a lot of more code!!
    spheres.clear();
    int radius = mathcommon::unifRand(minRadius,maxRadius);
    spheres[0]=Circle3D<int>( mathcommon::unifRand(radius,textureSizeX-radius), mathcommon::unifRand(radius,textureSizeY-radius), mathcommon::unifRand(radius,textureSizeZ-radius),radius);

    int noncoll=0;
    double totalVolume = this->textureSizeX*this->textureSizeY*this->textureSizeZ;
    double spheresVolume=0.0;

    while ( noncoll<nSpheres )
    {
        int radius = mathcommon::unifRand(minRadius,maxRadius);
        int centerx = mathcommon::unifRand(radius,textureSizeX-radius);
        int centery = mathcommon::unifRand(radius,textureSizeY-radius);
        int centerz = mathcommon::unifRand(radius,textureSizeZ-radius);
        Circle3D<int> curSphere(centerx,centery,centerz,radius);
        bool tmpIsCollidingWithSomeOtherElement=false;
        for (map<int, Circle3D<int> >::iterator iter = spheres.begin(); iter!=spheres.end(); ++iter)
        {
            if  ( iter->second.checkCollision(curSphere,2) )
            {
                tmpIsCollidingWithSomeOtherElement=true;
            }
        }
        if ( !tmpIsCollidingWithSomeOtherElement )
        {
            //cout << spheresVolume << "\t" << spheresVolume/totalVolume*100.0 <<  "\t" << noncoll << endl;
            spheresVolume+=4.0/3.0*M_PI*radius*radius*radius;
            spheres[noncoll++]=curSphere;
        }
        if ( spheresVolume/totalVolume > 0.35 ) // http://en.wikipedia.org/wiki/Random_close_pack
        {
            maxRadius-=1;
            if (maxRadius < minRadius)
            {
                cerr << "[VolumetricSurfaceIntersection] Stop adding spheres because total volume is too much, total spheres = " << spheres.size() << endl;
                break;
            }
        }
    }

    writeSpheresToTexture(255);
    spheres.clear();
    //    cerr << "Sphere filling time elapsed " << timer.getElapsedTimeInMilliSec() << " [ms]" << endl;
}

/**
 * @brief VolumetricSurfaceIntersection::fillVolumeWithRandomDots
 * @param nRandomDots
 * @param size
 */
void VolumetricSurfaceIntersection::fillVolumeWithRandomDots(int nRandomDots, int radius)
{
    if ( texture3DVolume.empty() )
        this->resize(this->textureSizeX,this->textureSizeY,this->textureSizeZ);
    memset(&(texture3DVolume.at(0)),texture3DfillValue,sizeof(GLubyte)*textureSizeX*textureSizeY*textureSizeZ);
    for (int i=0; i<nRandomDots;++i)
    {
        int centerx = mathcommon::unifRand(radius,textureSizeX-radius);
        int centery = mathcommon::unifRand(radius,textureSizeY-radius);
        int centerz = mathcommon::unifRand(radius,textureSizeZ-radius);

        for (int z=centerz-radius; z<centerz+radius;++z)
        {

            int tYtXx  = textureSizeY* textureSizeX* z;
            for ( int y=centery-radius; y<centery+radius;++y)
            {
                int tXY = textureSizeX* y;
                for ( int x= centerx-radius; x<centerx+radius; ++x)
                {
                    texture3DVolume[tYtXx+tXY + x] = 255;
                }
            }
        }
    }
}

/**
 * @brief VolumetricSurfaceIntersection::writeSpheresToTexture
 * @param value
 */
void VolumetricSurfaceIntersection::writeSpheresToTexture(int value)
{
    for (unsigned int i=0; i<spheres.size(); i++)
    {
        int sphereGrayColor =value;
        if (useRandomSpheresColor)
        {
            if (rand()%2)
                sphereGrayColor = mathcommon::unifRand(0,117);
            else
                sphereGrayColor=mathcommon::unifRand(137,255);
        }

        int radius= spheres[i].radius;
        int centerx = spheres[i].centerx;
        int centery = spheres[i].centery;
        int centerz = spheres[i].centerz;

        int cxmin=centerx-radius;
        int cxmax=centerx+radius;
        int cymin=centery-radius;
        int cymax=centery+radius;
        int czmin = centerz-radius;
        int czmax = centerz+radius;

        int radius2 = SQR(radius);
        for (int z=czmin; z<czmax;++z)
        {
            int z2 = SQR((z-centerz));
            int tYtXx  = textureSizeY* textureSizeX* z;
            for ( int y=cymin; y<cymax;++y)
            {
                int z2y2=z2+SQR(y-centery);
                int tXY = textureSizeX* y;
                for ( int x= cxmin; x<cxmax; ++x)
                {
                    if ( z2y2+SQR(x-centerx) < radius2)
                        texture3DVolume[tYtXx+tXY + x] = sphereGrayColor;
                }
            }
        }
    }
}

/**
 * @brief VolumetricSurfaceIntersection::updateTexture
 */
void VolumetricSurfaceIntersection::initializeTexture()
{
    getGLerrors();
    if (this->volume3DTextureID)
        glDeleteTextures(1,&(this->volume3DTextureID));

    glGenTextures(1, &(this->volume3DTextureID));

    glBindTexture(GL_TEXTURE_3D, this->volume3DTextureID);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    // Important to enable bilinear filtering and smoothing
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    getGLerrors();
    // This disables bilinear filtering
    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, this->textureSizeX, this->textureSizeY, this->textureSizeZ, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE,(GLvoid *) &(texture3DVolume.at(0)));
    // We can clean the volume after it is loaded on GPU
    texture3DVolume.clear();
}

/**
 * @brief VolumetricSurfaceIntersection::setTexture3DfillValue
 * @param val
 */
void VolumetricSurfaceIntersection::setTexture3DfillValue(int val)
{
    this->texture3DfillValue=val;
}

/**
 * @brief VolumetricSurfaceIntersection::getTexture3DfillValue
 * @return
 */
const int VolumetricSurfaceIntersection::getTexture3DfillValue() const
{
    return this->texture3DfillValue;
}

/**
 * @brief VolumetricSurfaceIntersection::getTextureSizeX
 */
const int VolumetricSurfaceIntersection::getTextureSizeX() const
{
    return textureSizeX;
}

/**
 * @brief VolumetricSurfaceIntersection::getTextureSizeY
 */
const int VolumetricSurfaceIntersection::getTextureSizeY() const
{
    return textureSizeY;
}

/**
 * @brief VolumetricSurfaceIntersection::getTextureSizeZ
 */
const int VolumetricSurfaceIntersection::getTextureSizeZ() const
{
    return textureSizeZ;
}


/**
 * @brief VolumetricSurfaceIntersection::getNSpheres
 */
const int VolumetricSurfaceIntersection::getNSpheres() const
{
    return nSpheres;
}

/**
 * @brief VolumetricSurfaceIntersection::getSphereRadiusMin
 */
const int VolumetricSurfaceIntersection::getSphereRadiusMin() const
{
    return sphereRadiusMin;
}

/**
 * @brief VolumetricSurfaceIntersection::getSphereRadiusMax
 */
const int VolumetricSurfaceIntersection::getSphereRadiusMax() const
{
    return sphereRadiusMax;
}

