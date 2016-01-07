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
#include <GL/glew.h>
#include "Homography.h"
#include "VolvuxWidget.h"
#include "VolumetricMeshIntersection.h"
#include "Timer.h"

#ifdef __APPLE__
std::string baseDir("/Users/rs/workspace/Volvux/");
std::string objPath("/Users/rs/workspace/VolvobjPatux/data/objmodels/helicoid.obj");
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
    //cerr << "[VolvuxWidget] Constructor" << endl;
    currentGLColor = Qt::gray;
    // Create the timer for the widget
    QTimer *timer = new QTimer(this); timer->start(0);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));

    drawTextureCube=true;
    useCalibratedGLView=true;
    useOffscreenRendering=false;

    this->slicesNumber=PROJECTOR_SLICES_NUMBER;
    this->resize(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);

    // Setup the calibration camera
    //loadCameraSettings();
    //this->setCameraParameters(3.0f,200.0f,30000.0f);
    // Set the current focus in this OpenGL window
    //this->setFocus();
    this->curvature=240.0;
    this->initVolume();
    //this->volume = NULL;
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
        delete fbo;

    if (volume)
        delete volume;
}

void VolvuxWidget::setCamera(CameraDirectLinearTransformation &cam)
{
    this->camCalibration = &cam;
}


/**
 * @brief applyOpenGLCameraFOV
 * @param fieldOfView
 * @param zNear
 * @param zFar
 */
void VolvuxWidget::applyOpenGLCameraFOV()
{
    // TO IMPLEMENT
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
    glewInit();
    initializeGLFunctions();
    volume->resize(TEXTURE_RESOLUTION_X,TEXTURE_RESOLUTION_Y,TEXTURE_RESOLUTION_Z);
    //volume->loadObj("C:\workspace\Volvux\data\objmodels\helicoid.obj");
    volume->loadObj(objPath);
    volume->setTexture3DfillValue(0);
    volume->fillVolumeWithSpheres(VOLUME_N_SPHERES,SPHERES_MIN_RADIUS,SPHERES_MAX_RADIUS);
    volume->meshStruct.showMesh=true;
    volume->initializeTexture();

    ////////////////////////////
    const GLcharARB vertexShader[] = STATIC_STRINGIFY(
                uniform float step;
            varying vec3 texture_coordinate;
    uniform float objSize;
    uniform float thickness;
    uniform float curvature;
    varying vec4 pvertex;
    uniform vec3 objOffset;
    void main()
    {
        vec4 v=gl_Vertex;
        // This is to rotate the object
        v.xz = vec2(cos(step)*v.x+sin(step)*v.z,-sin(step)*v.x+cos(step)*v.z);
        // Compute the z position given x and y on a circular domain of radius 1 (diameter 2)
        //texture_coordinate= vec3(((v.xz/radius+1.0)*0.5),(v.y-objOffset.y)/objSize);
        texture_coordinate= vec3(   ((v.xz-objOffset.xz)/objSize+1.0)*0.5, ((v.y-objOffset.y)/objSize+1.0)*0.5);
        gl_Position = gl_ModelViewProjectionMatrix*v;
        pvertex = v;
    }
    );

    const GLcharARB fragmentShader[] = STATIC_STRINGIFY(
    varying vec3 texture_coordinate;
    uniform sampler3D my_color_texture;
    uniform vec4 uniformColor;
    varying vec4 pvertex;
    uniform float thickness;
    uniform float curvature;
    void main()
    {
        vec4 finalColor = uniformColor*texture3D(my_color_texture, texture_coordinate);
        // Filter out the vertices outside a given surface normal
        float parametricSurfaceEquation = (pvertex.x*pvertex.x)/curvature;
        float normalLength = sqrt(1.0+(2.0*pvertex.x/curvature)*(2.0*pvertex.x/curvature));
        if ( abs((pvertex.z - parametricSurfaceEquation)/normalLength) <= thickness)
        {
            gl_FragColor = finalColor;
        }
        else
        {
            // color the vertices outside that small volume around the surface to black
            gl_FragColor = vec4(0.0,0.0,0.0,1.0);
        }
    }
    );

    volume->initializeSurfaceShaders(vertexShader,fragmentShader);
    ////////////////////////////
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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
        applyOpenGLCameraFOV();
    }


    volume->meshStruct.shader->setUniform4f(static_cast<GLcharARB*>((char*)"uniformColor"),1.0f,1.0f,1.0f,1.0f);
    volume->meshStruct.shader->setUniform1f(static_cast<GLcharARB*>((char*)"step"),volume->meshStruct.rotationAngle);
    volume->meshStruct.shader->setUniform3f(static_cast<GLcharARB*>((char*)"objOffset"),volume->meshStruct.offsetX,volume->meshStruct.offsetY,volume->meshStruct.offsetZ);
    volume->meshStruct.shader->setUniform1f(static_cast<GLcharARB*>((char*)"objSize"),volume->meshStruct.radius);
    volume->meshStruct.shader->setUniform1f(static_cast<GLcharARB*>((char*)"thickness"),volume->meshStruct.thickness);
    volume->meshStruct.shader->setUniform1f(static_cast<GLcharARB*>((char*)"curvature"),this->curvature);

    // Draw the helicoid
    glPushMatrix();
    glRotated(-90,1,0,0);
    glTranslated(volume->meshStruct.x,volume->meshStruct.y,volume->meshStruct.z);
    volume->draw();
    glPopMatrix();


}

/**
 * @brief VolvuxWidget::getVolume
 * @return
 */
VolumetricMeshIntersection *VolvuxWidget::getVolume() const
{
    return volume;
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
    volume->setTexture3DfillValue(value);
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
    volume->meshStruct.rotationAngle=0;
    Timer timer; timer.start();
    double deltaAngle = (2.0*M_PI)/this->slicesNumber;
    // Start the loop of frames generation
    if ( !useOffscreenRendering )
    {
        for ( unsigned int i=0; i<slicesNumber; i++ )
        {
            int percentage = static_cast<int>(std::ceil(100.0/slicesNumber*(i+1)));
            emit framePercentageGenerated(percentage);
            this->repaint();
            volume->meshStruct.rotationAngle += deltaAngle;
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
            volume->meshStruct.rotationAngle += deltaAngle;
        }
        fbo->release();
    }
    getGLerrors();

    cerr << "[VolvuxWidget] " << slicesNumber <<" frames generated, [ms]/frame = " << timer.getElapsedTimeInMilliSec()/slicesNumber << endl;
    this->setHelicoidZeroColor(volume->getTexture3DfillValue());
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
    this->volume->meshStruct.offsetX=x;
    this->volume->meshStruct.offsetY=y;
    this->volume->meshStruct.offsetZ=z;
}

/**
 * @brief VolvuxWidget::setHelicoidOffset
 * @param x
 * @param y
 * @param z
 */
void VolvuxWidget::setHelicoidOffset(double x, double y, double z)
{
    this->volume->meshStruct.x = x;
    this->volume->meshStruct.y = y;
    this->volume->meshStruct.z = z;
}

/**
 * @brief VolvuxWidget::setObjectScale
 * @param objScale
 */
void VolvuxWidget::setObjectScale(double objScale)
{
    this->volume->meshStruct.radius=objScale;
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
    volume->setTexture3DfillValue(0);
    if (useRandomDots)
        volume->fillVolumeWithRandomDots(nSpheres,minRadius);
    else
        volume->fillVolumeWithSpheres(nSpheres,minRadius,maxRadius);

    volume->meshStruct.showMesh=true;
    volume->initializeTexture();
}

/**
 * @brief VolvuxWidget::setOffscreenRendering
 * @param val
 */
void VolvuxWidget::setOffscreenRendering(bool val)
{
    this->useOffscreenRendering = val;
}


void VolvuxWidget::onSurfaceThicknessChanged(double val)
{
    this->update();
    this->volume->meshStruct.thickness=val;
}

void VolvuxWidget::onSurfaceCurvatureChanged(double val)
{
    this->curvature=val;
}

void VolvuxWidget::initVolume()
{
    this->volume = new VolumetricMeshIntersection(TEXTURE_RESOLUTION_X, TEXTURE_RESOLUTION_Y, TEXTURE_RESOLUTION_Z);
    this->volume->setUniformColor(glWhite);
    this->volume->meshStruct.radius = 110.0;
    this->volume->meshStruct.height = 1.0;
    this->volume->meshStruct.rotationAngle = 0.0;
    this->volume->meshStruct.offsetX = 0.0;
    this->volume->meshStruct.offsetY = 0.0;
    this->volume->meshStruct.offsetZ = 0.0;
    this->volume->meshStruct.x = 0.0;
    this->volume->meshStruct.y = 0.0;
    this->volume->meshStruct.z = 0.0;
    this->volume->meshStruct.thickness = 500.0f;
}

/*
void VolvuxWidget::loadBinvox(const string &filename)
{
    volume->setTexture3DfillValue(0);
    volume->loadTexture3DFile(filename);
    QString informations("Texture size ");
    informations += "[ "+QString::number(this->volume->getTextureSizeX())+","+QString::number(this->volume->getTextureSizeY())+","+QString::number(this->volume->getTextureSizeZ())+ "]";
    emit binVoxLoaded(informations);
    volume->initializeTexture();
}
*/
