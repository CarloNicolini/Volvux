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

// Only include GLEW in this way in order to ensure compatibility with QT OpenGL widget

#include "VolvuxWidget.h"
#include "Homography.h"
#include "VolumetricSurfaceIntersection.h"
#include "ObjLoader.h"

#ifdef __APPLE__
std::string baseDir("/Users/rs/workspace/Volvux/");
std::string objPath("/Users/rs/workspace/Volvux/data/objmodels/helicoid.obj");
#endif

#ifdef __linux__
std::string baseDir("~/workspace/Volvux/");
std::string objPath("../data/objmodels/helicoid.obj");
#endif

#ifdef WIN32
std::string baseDir("C:\\workspace\\Volvux\\");
std::string objPath("C:\\workspace\\Volvux\\data\\objmodels\\helicoid.obj");
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

// This is helpful to understand how to draw off-screen with OpenGL
// http://stackoverflow.com/questions/14785007/can-i-use-opengl-for-off-screen-rendering?rq=1

// For issues about OpenGL inclusion when glew conflicts with OpenGL I suggest to look:
// http://stackoverflow.com/questions/15048729/where-is-glgenbuffers-in-qt5

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
    //if (fbo)
      //  delete fbo; // no worry it's a QPointer

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX ); // Set up a basic display buffer (only single buffered for now)

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

    // VERY IMPORTANT TO INITIALIZE GLEW BEFORE THE GLSL SHADERS
    //glewInit();
    initializeGLFunctions();
    //volume->resize(TEXTURE_RESOLUTION_X,TEXTURE_RESOLUTION_Y,TEXTURE_RESOLUTION_Z);
    volume2->resize(TEXTURE_RESOLUTION_X,TEXTURE_RESOLUTION_Y,TEXTURE_RESOLUTION_Z);
    //volume->loadObj("C:\workspace\Volvux\data\objmodels\helicoid.obj");
    //volume->loadObj(objPath);
    volume2->setTexture3DfillValue(0);
    volume2->fillVolumeWithSpheres(VOLUME_N_SPHERES,SPHERES_MIN_RADIUS,SPHERES_MAX_RADIUS);
    volume2->initializeTexture();
	
    // HERE MUST LOAD THE SHADERS WITH QGLSHADERPROGRAM
    shader.addShaderFromSourceFile(QGLShader::Vertex,QString(baseDir.c_str())+QString("\\src\\HelicoidPositionShader.vert"));
	shader.addShaderFromSourceFile(QGLShader::Fragment, QString(baseDir.c_str()) + QString("\\src\\Texture3DShader.frag"));

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
        glLoadMatrixd(camCalibration->getOpenGLModelViewMatrix().data());
    }
    else
    {
        qDebug("non implemented gl camera FOV");
    }

    if (!shader.link())
    {
        qWarning() << "Shader Program Linker Error" << shader.log();
    }
    else
        shader.bind();



    // Set the shader parameters
    shader.setUniformValue("uniformColor",1.0f,1.0f,1.0f,1.0f);
    shader.setUniformValue("step",(float)meshStruct.rotationAngle);
    shader.setUniformValue("objOffset",meshStruct.offsetX,meshStruct.offsetY,meshStruct.offsetZ);
    shader.setUniformValue("objSize",meshStruct.radius);
    shader.setUniformValue("thickness",meshStruct.thickness);
    shader.setUniformValue("curvature",meshStruct.curvature);

    // Enable GL_TEXTURE3D for the visualization of ball field and finally draw the helicoid on it
    glEnable(GL_TEXTURE_3D);
    glPushMatrix();
    glRotated(-90,1,0,0);
    glTranslated(meshStruct.x,meshStruct.y,meshStruct.z);
    // Draw the helicoid
    obj->draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_3D);
}

/**
 * @brief VolvuxWidget::paintGL
 */
void VolvuxWidget::paintGL()
{
    qglClearColor(this->currentGLColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    meshStruct.showMesh=false;
    volume2->initializeTexture();
}

/**
 * @brief VolvuxWidget::setOffscreenRendering
 * @param val
 */
void VolvuxWidget::setOffscreenRendering(bool val)
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
