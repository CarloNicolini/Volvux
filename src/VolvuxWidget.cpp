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

#include "VolvuxWidget.h"
#include "Homography.h"
#include "VolumetricSurfaceIntersection.h"
#include "ObjLoader.h"
// These files have been embedded from the corresponding Texture3DShader.frag and HelicoidPositionShader.vert
// with the command xxd -i (see http://stackoverflow.com/questions/410980/include-a-text-file-in-a-c-program-as-a-char )
#include "Texture3DShader_frag.h"
#include "HelicoidPositionShader_vert.h"

#ifdef __APPLE__
std::string baseDir("/Users/rs/workspace/Volvux/");
std::string objPath("/Users/rs/workspace/Volvux/data/objmodels/helicoid_mws.obj");
#endif

#ifdef __linux__
std::string baseDir("~/workspace/Volvux/");
std::string objPath("../data/objmodels/helicoid_mws.obj");
#endif

#ifdef WIN32
std::string baseDir("C:\\workspace\\Volvux\\");
std::string objPath("C:\\workspace\\Volvux\\data\\objmodels\\helicoid_mws.obj");
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

// This is helpful to understand how to draw off-screen with OpenGL
// http://stackoverflow.com/questions/14785007/can-i-use-opengl-for-off-screen-rendering?rq=1

/**
 * @brief VolvuxWidget::VolvuxWidget
 * @param parent
 * @param shareWidget
 */
VolvuxWidget::VolvuxWidget(QWidget *parent) :
    //    QGLWidget(parent)
    QGLWidget( parent)
{
    currentGLColor = Qt::gray;
    // Create the timer for the widget
    QTimer *timer = new QTimer(this); timer->start(0);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    drawTextureCube=true;
    useCalibratedGLView=true;
    useOffscreenRendering=false;

    this->slicesNumber=PROJECTOR_SLICES_NUMBER;
    this->resize(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);

    this->initVolume();
    this->obj = new ObjLoader(objPath.c_str());
    this->meshStruct.curvature=240.0;

    this->fbo = NULL;
    // Setup the visualization volume
    this->camCalibration = NULL;
}

/**
 * @brief VolvuxWidget::~VolvuxWidget
 */
VolvuxWidget::~VolvuxWidget()
{
    cerr << "[VolvuxWidget] Destructor" << endl;
    if (fbo)
      delete fbo; // no worry it's a QPointer
    if (obj)
        delete obj;
    if (volume2)
        delete volume2;
}

void VolvuxWidget::setCamera(CameraDirectLinearTransformation &cam)
{
    this->camCalibration = &cam;
}


/**
 * @brief VolvuxWidget::minimumSizeHint
 * @return
 */
QSize VolvuxWidget::minimumSizeHint() const
{
    return QSize(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);

}

/**
 * @brief VolvuxWidget::sizeHint
 * @return
 */
QSize VolvuxWidget::sizeHint() const
{
    return QSize(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);
}

/**
 * @brief VolvuxWidget::initializeGL
 */
void VolvuxWidget::initializeGL()
{

    this->makeCurrent();
    cerr << "[VolvuxWidget] initializing GL context" << endl;
    int argc = 1;
    char *argv[] = {"1","2"};

    qglClearColor(this->currentGLColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set depth buffer clear value
    glClearDepth(1.0);

    // Enable multisample
    //glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-10);
    // Get the informations about the size of texture3D ram
    GLint result;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &result);
    cerr << "[VolvuxWidget] Available GPU memory for texture 3D is " << result << " [MB]" << endl;

    initializeGLFunctions();
    volume2->resize(TEXTURE_RESOLUTION_X,TEXTURE_RESOLUTION_Y,TEXTURE_RESOLUTION_Z);
    volume2->setTexture3DfillValue(0);
    volume2->fillVolumeWithSpheres(VOLUME_N_SPHERES,SPHERES_MIN_RADIUS,SPHERES_MAX_RADIUS);
    volume2->initializeTexture();

    // HERE MUST LOAD THE SHADERS WITH QGLSHADERPROGRAM
    //shader.addShaderFromSourceCode(QGLShader::Vertex, src_HelicoidPositionShader_vert);
    //shader.addShaderFromSourceCode(QGLShader::Fragment, src_Texture3DShader_frag);
    //shader.addShaderFromSourceFile(QGLShader::Vertex,"../src/HelicoidPositionShader.vert");
    //shader.addShaderFromSourceFile(QGLShader::Fragment,"../src/Texture3DShader.frag");

	shader.addShaderFromSourceFile(QGLShader::Vertex, "C://workspace//Volvux//src//HelicoidPositionShader.vert");
	shader.addShaderFromSourceFile(QGLShader::Fragment, "C://workspace//Volvux//src//Texture3DShader.frag");
	
    if (!shader.link())
        qWarning() << "Shader Program Linker Error" << shader.log();

    glPointSize(0.1f);
    glLineWidth(0.1f);

    // Initializing frame buffer object
    // Here we create a framebuffer object with the smallest necessary precision, i.e. GL_RED in order to make
    // the subsequent calls to glReadPixels MUCH faster!
    QGLFramebufferObjectFormat fboFormat;
    fboFormat.setMipmap(false);
    fboFormat.setSamples(0);
    fboFormat.setInternalTextureFormat(GL_LUMINANCE);
    //fboFormat.setAttachment(QGLFramebufferObject::Depth); // It makes Win32 version crash
    fbo = new QGLFramebufferObject(QSize(PROJECTOR_RESOLUTION_WIDTH, PROJECTOR_RESOLUTION_HEIGHT),fboFormat);
    cerr << "[VolvuxWidget] FBO depth= " << fbo->depth() << endl;
    cerr << "[VolvuxWidget] num colors= " << fbo->colorCount() << endl;
    getGLerrors();
}

/**
 * @brief VolvuxWidget::draw
 */
void VolvuxWidget::draw()
{
    if ( useCalibratedGLView )
    {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(camCalibration->getOpenGLProjectionMatrix().data());
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixd(camCalibration->getOpenGLModelViewMatrix().data());
		//glRotated(180, 1, 0, 0);
    }
    else
    {
        glMatrixMode(GL_PROJECTION);
        glOrtho(-250,250,-250,250,-250,250);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    Eigen::Matrix3d R = camCalibration->getOpenGLModelViewMatrix().rotation().transpose().eval();
    Eigen::AngleAxisd aa(R);
    double angle = aa.angle();
    Vector3d axis = aa.axis();
    shader.bind();
    // Set the shader parameters
    shader.setUniformValue("uniformColor",1.0f,1.0f,1.0f,1.0f);
    shader.setUniformValue("step",meshStruct.rotationAngle);
    shader.setUniformValue("objOffset",meshStruct.offsetX,meshStruct.offsetY,meshStruct.offsetZ);
    shader.setUniformValue("objSize",meshStruct.radius);
    shader.setUniformValue("thickness",meshStruct.thickness);
    shader.setUniformValue("a",meshStruct.curvature);
	shader.setUniformValue("b", meshStruct.firstOrderCoeff);
	shader.setUniformValue("c", meshStruct.zeroOrderCoeff);

    // Enable GL_TEXTURE3D for the visualization of ball field and finally draw the helicoid on it
    glEnable(GL_TEXTURE_3D);
    glPushMatrix();
    glTranslated(meshStruct.x,meshStruct.y,meshStruct.z);
    // Draw the helicoid
    obj->draw();    
    glPopMatrix();
    glDisable(GL_TEXTURE_3D);
	shader.release(); // always remember to release the shader at the end!
	/*
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3d(1, 1, 0);
	glTranslated(meshStruct.x, meshStruct.y, meshStruct.z);
	obj->drawOnlyVertices();
	glPopAttrib();
	glPopMatrix();
	*/
	/*
	double d = 30;
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(d, 0, 0);

	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, d, 0);

	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, d);
	glEnd();
	glPopAttrib();
	glPopMatrix();
	drawCalibration();
	*/
}

/**
 * @brief VolvuxWidget::drawCalibration
 */
void VolvuxWidget::drawCalibration()
{
	static double zp = 0;
	glPushAttrib(GL_POINT_BIT | GL_COLOR_BUFFER_BIT);
    glPointSize(5);
	glColor3d(1, 1, 1);
    glBegin(GL_POINTS);
    for (int i=0; i<9; i++)
    {
        Vector4d v = this->camCalibration->getPoints3D().at(i);
        glVertex3d(v.x(),v.y(),v.z());
		glVertex3d(v.x(), v.y(), v.z() + zp);
    }
    glEnd();
    glPopAttrib();

    zp += 1;
    if (zp > 200)
        zp = 0;

	glPushAttrib(GL_POINT_BIT | GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glColor3d(1, 1, 1);
	glPushMatrix();
	glTranslated(meshStruct.x, meshStruct.y, meshStruct.z);
	//glTranslated(0, 0, -37.5);
	double radius = 25;
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i < 2 * M_PI; i += 0.05)
		glVertex3d(radius*cos(i), radius*sin(i), 0);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

/**
 * @brief VolvuxWidget::paintGL
 */
void VolvuxWidget::paintGL()
{
    qglClearColor(this->currentGLColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

/**
 * @brief VolvuxWidget::setCurrentGLColor
 * @param val
 */
void VolvuxWidget::setCurrentGLColor(Qt::GlobalColor val)
{
    this->currentGLColor=val;
}

/**
 * @brief VolvuxWidget::setHelicoidZeroColor
 * @param value
 */
void VolvuxWidget::setHelicoidZeroColor(int value)
{
    volume2->setTexture3DfillValue(value);
}

#ifdef WIN32
#include <windows.h>
size_t getTotalSystemMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
}
#endif

/**
 * @brief VolvuxWidget::startFramesGeneration
 */
void VolvuxWidget::generateFrames()
{
    this->drawTextureCube=false;
    this->setHelicoidZeroColor(0);
    this->setCurrentGLColor(Qt::black);
    unsigned long int w = static_cast<unsigned long int>(this->width());
    unsigned long int h = static_cast<unsigned long int>(this->height());
    // Important to use unsigned integers to avoid overflow error
    unsigned long int length = w*h*slicesNumber;
	cerr << "W H L =  " << w << " " << h << " " << length << endl;
    // Reset space for all frames sequence
    allFrames.clear();
    emit memoryAllocatedMegaBytes(length*sizeof(unsigned char)/1E6);
    //cerr << "[VolvuxWidget] w,h,slicesNumber=" << w << "," << h << "," << slicesNumber << endl;
    //cerr << "Resizing to " << w*h*slicesNumber*sizeof(unsigned char)/1E6 << " [MB]" << endl;
    try
    {
        allFrames.resize(length,0);
    }
    catch (const std::exception &e)
    {
        QString maximumVectorSize = QString::number(allFrames.max_size()/1E6);
        cerr << e.what() << endl;
        //QMessageBox::warning(this,QString("Error: ")+QString::fromStdString(e.what()),"Too much memory allocated, asked "+QString::number(length/1E6) + " [MB] but " + maximumVectorSize + " [MB] addressable" + "\n"+"User memory= "+QString::number((unsigned int)getTotalSystemMemory()/1E6)+" [MB]");
        return;
    }

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    meshStruct.rotationAngle=0;
    //Timer timer; timer.start();
    double deltaAngle = (2.0*M_PI)/this->slicesNumber;
    // Start the loop of frames generation
    if ( !useOffscreenRendering )
    {
        for ( unsigned int i=0; i<slicesNumber; i++ )
        {
            int percentage = static_cast<int>(std::ceil(100.0/slicesNumber*(i+1)));
            emit framePercentageGenerated(percentage);
            this->repaint();
            meshStruct.rotationAngle += deltaAngle;
        }
    }
    else
    {
        fbo->bind();
        for ( unsigned int i=0; i<slicesNumber; i++ )
        {
            this->paintGL();
            // Read the current frame buffer object
            glReadPixels(0, 0, w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, &allFrames.at(i*w*h));
            //fbo->toImage().save(QDir::currentPath()+"/ciccio_"+QString::number(i,'g',3)+".png","PNG");
            meshStruct.rotationAngle += deltaAngle;
        }
        fbo->release();
        emit dataFrameGenerated(allFrames.data());
    }
    getGLerrors();

    //cerr << "[VolvuxWidget] " << slicesNumber <<" frames generated, [ms]/frame = " << timer.getElapsedTimeInMilliSec()/slicesNumber << endl;
    this->setHelicoidZeroColor(volume2->getTexture3DfillValue());
    glPopAttrib();

    this->drawTextureCube=true;
    this->setCurrentGLColor(Qt::gray);
    this->repaint();
}

/**
 * @brief VolvuxWidget::resizeGL
 * @param width
 * @param height
 */
void VolvuxWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height); // Set our viewport to the size of our window
}

/**
 * @brief VolvuxWidget::setOffset
 * @param x
 * @param y
 * @param z
 */
void VolvuxWidget::setObjectOffset(double x, double y, double z)
{
    this->meshStruct.offsetX=x;
    this->meshStruct.offsetY=y;
    this->meshStruct.offsetZ=z;
}

/**
 * @brief VolvuxWidget::setHelicoidOffset
 * @param x
 * @param y
 * @param z
 */
void VolvuxWidget::setHelicoidOffset(double x, double y, double z)
{
    this->meshStruct.x = x;
    this->meshStruct.y = y;
    this->meshStruct.z = z;
}

/**
 * @brief VolvuxWidget::setObjectScale
 * @param objScale
 */
void VolvuxWidget::setObjectScale(double objScale)
{
    this->meshStruct.radius=objScale;
}

/**
 * @brief VolvuxWidget::setSlicesNumber
 * @param nSlices
 */
void VolvuxWidget::setSlicesNumber(int nSlices)
{
    // This avoids integer overflow when resizing vector!
    this->slicesNumber=static_cast<unsigned int>(nSlices);
}

/**
 * @brief VolvuxWidget::randomizeSpheres
 * @param nSpheres
 * @param minRadius
 * @param maxRadius
 */
void VolvuxWidget::randomizeSpheres(bool useRandomDots, int nSpheres, int minRadius, int maxRadius)
{
    volume2->setTexture3DfillValue(0);
    if (useRandomDots)
        volume2->fillVolumeWithRandomDots(nSpheres,minRadius);
    else
        volume2->fillVolumeWithSpheres(nSpheres,minRadius,maxRadius);
    volume2->initializeTexture();
}

/**
 * @brief VolvuxWidget::setOffscreenRendering
 * @param val
 */
void VolvuxWidget::setOffscreenRendering(int val)
{
    this->useOffscreenRendering = val;
}

/**
 * @brief VolvuxWidget::onSurfaceThicknessChanged
 * @param val
 */
void VolvuxWidget::onSurfaceThicknessChanged(double val)
{
    this->meshStruct.thickness=val;
    this->update();
}

/**
 * @brief VolvuxWidget::onSurfaceCurvatureChanged
 * @param val
 */
void VolvuxWidget::onSurfaceCurvatureChanged(double val)
{
    this->meshStruct.curvature=val;
    this->update();
}

/**
 * @brief VolvuxWidget::initVolume
 */
void VolvuxWidget::initVolume()
{
    this->volume2 = new VolumetricSurfaceIntersection(TEXTURE_RESOLUTION_X, TEXTURE_RESOLUTION_Y, TEXTURE_RESOLUTION_Z);
    //this->setUniformColor(glWhite);
    this->meshStruct.radius = 110.0;
    this->meshStruct.height = 1.0;
    this->meshStruct.rotationAngle = 0.0;
    this->meshStruct.offsetX = 0.0;
    this->meshStruct.offsetY = 0.0;
    this->meshStruct.offsetZ = 0.0;
    this->meshStruct.x = 0.0;
    this->meshStruct.y = 0.0;
    this->meshStruct.z = 0.0;
    this->meshStruct.thickness = 500.0f;
}
