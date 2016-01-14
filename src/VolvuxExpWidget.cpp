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

#include <iostream>
#include "VolvuxExpWidget.h"

// For issues about OpenGL inclusion when glew conflicts with OpenGL I suggest to look:
// http://stackoverflow.com/questions/15048729/where-is-glgenbuffers-in-qt5

/**
 * @brief VolvuxExpWidget::VolvuxExpWidget
 * @param parent
 * @param shareWidget
 */
VolvuxExpWidget::VolvuxExpWidget(QWidget *parent):
    QGLWidget( QGLFormat::defaultFormat(), parent)
{
    // Create the timer for the widget
    QTimer *timer = new QTimer(this); timer->start(0);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    this->resize(QSize(640,480));
    this->setAttribute(Qt::WA_DeleteOnClose);
    //this->setAttribute(Qt::WA_TranslucentBackground,true);
    //this->setWindowOpacity(0.4);
    this->showFullScreen();
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->xRange = 120.0;
    this->trialNumber = 0;
}

/**
 * @brief VolvuxExpWidget::initMonitor
 * @param EXPERIMENT_WINDOW_RESOLUTION_X
 * @param EXPERIMENT_WINDOW_RESOLUTION_Y
 * @param EXPERIMENT_WINDOW_PHYSICAL_SIZE_MM_X
 * @param EXPERIMENT_WINDOW_PHYSICAL_SIZE_MM_Y
 */
void VolvuxExpWidget::initMonitor(int resX, int resY, int sizeX_mm, int sizeY_mm)
{
    this->experimentWindowResolutionX = resX;
    this->experimentWindowResolutionY = resY;

    this->resize(resX,resY);
    // Camera calibrations done on the flight
    //this->cam.init(Screen(sizeX_mm,sizeY_mm,0,0,eyeZ));
    //this->cam.setNearFarPlanes(0.01f,1E5f);
}

/**
 * @brief applyOpenGLCameraFOV
 * @param fieldOfView
 * @param zNear
 * @param zFar
 */
void VolvuxExpWidget::applyOpenGLCameraFOV()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //cam.setEye(Eigen::Vector3d(0,0,0));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief VolvuxExpWidget::~VolvuxExpWidget
 */
VolvuxExpWidget::~VolvuxExpWidget()
{
    //QMessageBox::information(this,"Experiment finished","The experiment is finished.");
    std::cerr << "[VolvuxExpWidget] Destructor" << endl;
}

/**
 * @brief VolvuxExpWidget::minimumSizeHint
 * @return
 */
QSize VolvuxExpWidget::minimumSizeHint() const
{
    return QSize(experimentWindowResolutionX,experimentWindowResolutionY);
}

/**
 * @brief VolvuxExpWidget::sizeHint
 * @return
 */
QSize VolvuxExpWidget::sizeHint() const
{
    return QSize(experimentWindowResolutionX,experimentWindowResolutionY);
}

/**
 * @brief VolvuxExpWidget::setCameraParameters
 * @param FOV
 * @param zNear
 * @param zFar
 */
void VolvuxExpWidget::setCameraParameters(GLfloat _eyeZ, GLfloat _FOV, GLfloat _zNear, GLfloat _zFar)
{
    this->eyeZ = _eyeZ;
    this->FOV = _FOV;
    this->zNear = _zNear;
    this->zFar = _zFar;
}

/**
 * @brief VolvuxExpWidget::initializeGL
 */
void VolvuxExpWidget::initializeGL()
{
    std::cerr << "[VolvuxExpWidget] initializing GL context" << endl;
    this->makeCurrent();
    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set depth buffer clear value
    glClearDepth(1.0);
    // Enable multisample
    glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,eyeZ);
    glPointSize(0.1f);
    glLineWidth(0.1f);
    getGLerrors();
}

/**
 * @brief VolvuxExpWidget::drawSideParabola
 */
void VolvuxExpWidget::drawSideParabola(double xRange, double curvature)
{
    double yPosition = xRange;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_3D);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
    for ( double x=-xRange; x<=xRange; x+=1.0 )
    {
        glVertex3d(x,-curvature*(x*x-(xRange*xRange))-yPosition/2,eyeZ);
    }
    glEnd();
    glPopAttrib();
}

/**
 * @brief VolvuxExpWidget::paintGL
 */
void VolvuxExpWidget::paintGL()
{
    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    applyOpenGLCameraFOV();
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0,0,eyeZ);
    glColor3f(1.0f,1.0f,1.0f);
    glutWireCube(100);
    drawSideParabola(xRange,displayedCurvature/xRange);
    glPopMatrix();
}

/**
 * @brief VolvuxExpWidget::resizeGL
 * @param width
 * @param height
 */
void VolvuxExpWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height); // Set our viewport to the size of our window
    applyOpenGLCameraFOV();
}

/**
 * @brief VolvuxExpWidget::advanceTrial
*/
void VolvuxExpWidget::advanceTrial()
{
	/*
    if ( bal.next() )
    {
        int minRand = 0;
        int maxRand = 0;
        double curvature = bal.getCurrent().at("Curvature");
        this->displayedCurvature = (curvature + qrand() % ((maxRand + 1) - minRand) + minRand);

        QString expInfo = "Trial number = " + QString::number(this->trialNumber) + " \n";
        for (map<string,double>::iterator iter = bal.getCurrent().begin(); iter!=bal.getCurrent().end(); ++iter)
            expInfo+=QString::fromStdString(iter->first) + " = " + QString::number(iter->second) + "\n";
        expInfo+="_____\n";
        emit getExperimentInfo(expInfo);
        emit trialAdvanced(curvature);
        trialNumber++;
    }
    else
    {
        emit experimentFinished();
        this->close();
    }
	*/
}

/**
 * @brief VolvuxExpWidget::initializeExperiment
 */
void VolvuxExpWidget::initializeExperiment()
{
	/*
    if (bal.getCurrent().empty())
        advanceTrial();
	*/
}

/**
 * @brief VolvuxExpWidget::keyPressEvent
 * @param e
 */
void VolvuxExpWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {
    case Qt::Key_Q:
    {
        this->close();
        break;
    }
    case Qt::Key_Plus:
    {
        // change curvature
        this->displayedCurvature +=1.0;
        break;
    }
    case Qt::Key_Minus:
    {
        // change curvature
        this->displayedCurvature -=1.0;
        break;
    }
    case Qt::Key_Enter:
    {
        advanceTrial();
        break;
    }
    }
}
