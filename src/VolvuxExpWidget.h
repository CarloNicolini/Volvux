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

#ifndef VOLVUX_EXP_WIDGET_H_
#define VOLVUX_EXP_WIDGET_H_

#include <QtGui>
#include <QGLWidget>
#include <QGLFramebufferObject>
#include <Eigen/Core>

#include "GLUtils.h"
//#include "VRCamera.h"
//#include "Screen.h"

template<class T> class BalanceFactor;

class VolvuxExpWidget : public QGLWidget
{
    Q_OBJECT
public:
    VolvuxExpWidget(QWidget *parent = 0);
    ~VolvuxExpWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void initializeExperiment();
    void setCameraParameters(GLfloat _eyeZ, GLfloat _FOV, GLfloat _zNear, GLfloat _zFar);
    void initMonitor(int resX, int resY, int sizeX_mm, int sizeY_mm);

signals:
    void trialAdvanced(double);
    void getExperimentInfo(const QString &);
	void experimentFinished();

    // Inherited QGLWidget methods for GUI control
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
    void applyOpenGLCameraFOV();

    void drawSideParabola(double xRange, double curvature);
    int trialNumber;
    void advanceTrial();

    GLfloat FOV;
    GLfloat zNear;
    GLfloat zFar;
    GLfloat eyeZ;
    GLint experimentWindowResolutionX;
    GLint experimentWindowResolutionY;
    //VRCamera cam;

public:
    //BalanceFactor<double> bal;
    double displayedCurvature;
    double xRange;
};

#endif
