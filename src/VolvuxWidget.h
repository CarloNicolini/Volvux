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

#ifndef VOLVUX_WIDGET_H_
#define VOLVUX_WIDGET_H_

#include <QApplication>
#include <QtGui>
#include <QGLWidget>
#include <QGLFunctions>
#include <QGLFramebufferObject>
#include <Eigen/Core>

#include "Util.h"
#include "GLUtils.h"
#include "Arcball.h"
#include "VRCamera.h"
#include "Screen.h"
#include "ParametersLoader.h"
#include "CalibrationWidgetPage.h"
//#include "CalibrationHelper.h"

#define PROJECTOR_SLICES_NUMBER 16

#define TEXTURE_RESOLUTION_X 512
#define TEXTURE_RESOLUTION_Y 512
#define TEXTURE_RESOLUTION_Z 512

#define VOLUME_N_SPHERES 1000
#define SPHERES_MIN_RADIUS 5
#define SPHERES_MAX_RADIUS 50

#define GL_FRAGMENT_PRECISION_HIGH 1

class QGLShaderProgram;
typedef Eigen::Matrix<GLfloat,3,1> VectorGL3f;
typedef Eigen::Transform<GLfloat,3,Eigen::Affine> AffineGL3f;
typedef Eigen::Transform<GLfloat,3,Eigen::Projective> ProjectiveGL3f;
typedef Eigen::AngleAxis <GLfloat> AngleAxisGLf;

class VolumetricSurfaceIntersection;
class VolumetricMeshIntersection;
class CameraDirectLinearTransformation;


class VolvuxWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    VolvuxWidget(QWidget *parent = 0);
    ~VolvuxWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    // Object methods
    void initVolume();
    //void loadBinvox(const std::string &filename);

    void setHelicoidOffset(double x, double y, double z);
    void setObjectOffset(double x, double y, double z);
    void setObjectScale(double objScale);
    void setHelicoidZeroColor(int value);
    void randomizeSpheres(bool useRandomDots, int nSpheres, int minRadius, int maxRadius);

    // View methods
    void setCameraParameters(double _fieldOfView, double _zNear, double _zFar);
    void setSlicesNumber(int nSlices);
    void setCurrentGLColor(Qt::GlobalColor val);


public slots:

    // Projector methods
    void generateFrames();
    void setOffscreenRendering(bool val);
    void onSurfaceThicknessChanged(double);
    void onSurfaceCurvatureChanged(double);

    // Calibration methods
    void setCamera(CameraDirectLinearTransformation &cam);
signals:
    void framePercentageGenerated(double);
    void memoryAllocatedMegaBytes(int);
    void binVoxLoaded(QString);

    // Inherited QGLWidget methods for GUI control
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);


    void applyOpenGLCameraFOV();
    void draw();

    // Variables for scene and calibration settings
public:
    bool useOffscreenRendering;
    bool drawTextureCube;
    bool useCalibratedGLView;


    // Volumetric mesh intersection instance
    VolumetricMeshIntersection *volume;
    CameraDirectLinearTransformation *camCalibration;
    //VRCamera cam;

    // Background color
    Qt::GlobalColor currentGLColor;

    unsigned int slicesNumber;
    std::vector<unsigned char> allFrames;

    QGLFramebufferObject *fbo;
    VolumetricMeshIntersection *getVolume() const;

    GLfloat curvature;

};

#endif
