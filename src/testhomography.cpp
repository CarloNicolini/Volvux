#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Timer.h"
#include "Homography.h"
#include "VRCamera.h"
#include "ObjLoader2.h"
#include "VolumetricMeshIntersection.h"

using namespace Eigen;
using namespace std;

#define CALIBRECT_EDGE_BOTTOM 71.0
#define CALIBRECT_EDGE_TOP 50.0
#define CALIBRECT_HEIGHT 10.0

#define ZNEAR 0.1
#define ZFAR 1E6

ObjLoader2 *obj;

stlalignedvector4d points3D;

static const double calibrationtoy[]  = {0,0,0,
                                         -CALIBRECT_EDGE_BOTTOM/2, CALIBRECT_EDGE_BOTTOM/2,0,
                                         CALIBRECT_EDGE_BOTTOM/2, CALIBRECT_EDGE_BOTTOM/2,0,
                                         CALIBRECT_EDGE_BOTTOM/2, -CALIBRECT_EDGE_BOTTOM/2,0,
                                         -CALIBRECT_EDGE_BOTTOM/2, -CALIBRECT_EDGE_BOTTOM/2,0,
                                         -CALIBRECT_EDGE_TOP/2, CALIBRECT_EDGE_TOP/2, CALIBRECT_HEIGHT,
                                         CALIBRECT_EDGE_TOP/2, CALIBRECT_EDGE_TOP/2, CALIBRECT_HEIGHT,
                                         CALIBRECT_EDGE_TOP/2, -CALIBRECT_EDGE_TOP/2, CALIBRECT_HEIGHT,
                                         -CALIBRECT_EDGE_TOP/2, -CALIBRECT_EDGE_TOP/2, CALIBRECT_HEIGHT,
                                        };

int iWidth=256;
int iHeight=256;
int iDepth=256;

double spheresize=120;

VolumetricMeshIntersection surface;

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    cerr << xpos << " " << ypos << endl;
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ( (key == GLFW_KEY_ESCAPE || key==GLFW_KEY_Q) && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if ( (key == GLFW_KEY_A ) && action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        surface.meshStruct.rotationAngle += 0.05;
    }
    if ( (key == GLFW_KEY_Z ) && action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        surface.meshStruct.rotationAngle -= 0.05;
    }
    if ( (key == GLFW_KEY_S ) && action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        spheresize += 10;
    }
    if ( (key == GLFW_KEY_X ) && action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        spheresize -= 10;
    }
    cout << "spheresize=" << spheresize << endl;
}

static void mouse_entered_callback(GLFWwindow *window, int entered)
{
    printf("%d\n",entered);
}

GLFWwindow *initOpenGLContext(const int width=1024, const int height=768, const int refreshRate=60, const bool gamemode=false, const bool stereo=false, const int fsaaSamples=0)
{
    GLFWwindow* window;
    int widthMM=0;
    int heightMM=0;
    int count=-1;
    int sizeX=0;
    int sizeY=0;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        throw std::runtime_error("[GLFW] Can't initialize a valid GLFW context here");
        exit(EXIT_FAILURE);
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
    glfwWindowHint(GLFW_REFRESH_RATE,refreshRate);
    glfwWindowHint(GLFW_RED_BITS,8);
    glfwWindowHint(GLFW_GREEN_BITS,8);
    glfwWindowHint(GLFW_BLUE_BITS,8);
    glfwWindowHint(GLFW_ALPHA_BITS,8);
    glfwWindowHint(GLFW_SAMPLES,fsaaSamples);
    if (stereo)
        glfwWindowHint(GLFW_STEREO,stereo);
    if (gamemode)
        window = glfwCreateWindow(width,height, "GLFW", monitor, NULL);
    else
        window = glfwCreateWindow(width,height, "GLFW", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window,&sizeX,&sizeY);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

#ifdef _DEBUG
    const GLFWvidmode *currentMode= glfwGetVideoMode(monitor);
    const GLFWvidmode *allModes = glfwGetVideoModes(monitor, &count);
    cerr << "[GLFW] Current video mode [" << currentMode->width << "x" << currentMode->height << "]" << currentMode->redBits << " " << currentMode->greenBits << " " << currentMode->blueBits << endl;
    cerr << "[GLFW] Detected monitor size [" << widthMM  << "x" << "]" << heightMM << endl;
    cerr << "[GLFW] All possible video modes: " << endl;
    for(int i = 0; i < count; i++)
    {
        cerr << "\t" << allModes[i].width << "x" << allModes[i].height << " (" << allModes[i].redBits << "," << allModes[i].greenBits << "," << allModes[i].blueBits << ") @" << allModes[i].refreshRate << endl;
    }
    cerr << "[GLFW Current fullscreen window size= [" << sizeX << "x" << sizeY << "]" << endl;
#endif
    glfwSwapInterval(1);

#ifdef _WIN32
    // Turn on vertical screen sync under Windows.
    // (I.e. it uses the WGL_EXT_swap_control extension)
    typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if(wglSwapIntervalEXT)
        wglSwapIntervalEXT(1);
#endif

    // Disable mouse cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return window;
}

void drawCalibrations3D()
{
    glPushMatrix();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3d(0,0,1);
    for (int i=0; i<9; i++)
        glVertex3dv(points3D.at(i).data());
    glEnd();
    glPopMatrix();
}

void drawFrame(GLFWwindow *window, CameraDirectLinearTransformation &cdlt)
{
    double ratio;
    double width=1024;
    double height=768;

    //glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height*100;

    Projective3d P = cdlt.getOpenGLProjectionMatrix();
    Affine3d MV = cdlt.getOpenGLModelViewMatrix();

    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, 1024, 768);
    glDepthRange(ZNEAR,ZFAR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0,0,0,0);
    // Apply GL_PROJECTION matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(P.data());

    // Apply modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(MV.data());
    obj->draw();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    // DRAW THE AXES
    // Draw arrows
    glLineWidth(5);
    glBegin(GL_LINES);
    // red X axis
    glColor3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(50,0,0);
    // blue Y axis
    glColor3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,50,0);
    // green Z axis
    glColor3d(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(0,0,50);
    glEnd();
    glPopAttrib();

    drawCalibrations3D();
    /*
    glPushMatrix();
    glColor3d(1,0,0);
    glutWireSphere(spheresize,50,50);
    Eigen::Projective3d X;
    glGetDoublev(GL_MODELVIEW_PROJECTION_NV,X.data());
    //cout << X.matrix() << endl;
    glTranslated(-X.translation().x(),-X.translation().y(),-X.translation().z());
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    // Draw arrows
    glLineWidth(5);
    glBegin(GL_LINES);
    // red axis
    glColor3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(50,0,0);
    // blue axis
    glColor3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,50,0);
    // green axis
    glColor3d(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(0,0,50);
    glEnd();
    glPopAttrib();

    /*
    glEnable(GL_TEXTURE_3D);
    surface.draw();
    glDisable(GL_TEXTURE_3D);
    drawCalibrations3D();
    glPopAttrib();
    glPopMatrix();
    */
}

void init()
{
    obj = new ObjLoader2();
    obj->load("../data/objmodels/helicoid.obj");
    obj->initializeBuffers();
    //obj->getInfo();

    /*
    surface.resize(iWidth,iHeight,iDepth);
    surface.loadObj("../data/objmodels/helicoid.obj");
    const GLfloat white[]={1.0f,0.0f,0.0f,1.0f};
    surface.setUniformColor(white);
    int nspheres=1000;
    int minRadius=1;
    int maxRadius=5;
    surface.fillVolumeWithSpheres(nspheres,minRadius,maxRadius);
    surface.initializeTexture();
    surface.initializeSurfaceShaders();
    surface.meshStruct.showMesh=true;
    surface.meshStruct.radius=120.0;
    surface.meshStruct.height=1.0;
    surface.meshStruct.rotationAngle=0.0;
    surface.meshStruct.offsetX=0.0;
    surface.meshStruct.offsetY=0.0;
    surface.meshStruct.offsetZ=0.0;
    surface.meshStruct.thickness=10000;
    */
}

int main(int argc, char *argv[])
{
    for (int i=0; i<9; ++i)
    {
        Eigen::Vector4d p;
        p << calibrationtoy[i*3],calibrationtoy[i*3+1],calibrationtoy[i*3+2],1;
        points3D.push_back(p);
    }

    vector<Vector3d> points2d;
    points2d.push_back(Vector3d(512,384,1));
    points2d.push_back(Vector3d(419,474,1));
    points2d.push_back(Vector3d(409,294,1));
    points2d.push_back(Vector3d(589,294,1));
    points2d.push_back(Vector3d(589,474,1));
    points2d.push_back(Vector3d(449,441,1));
    points2d.push_back(Vector3d(449,321,1));
    points2d.push_back(Vector3d(569,321,1));
    points2d.push_back(Vector3d(569,441,1));
    /*
    cout << "[ " ;
    for (int i=0; i<9; ++i)
    {
        cout << points2d.at(i).transpose() << " ;" << endl;
    }
    cout << "]" << endl;

    cout << "[ " ;
    for (int i=0; i<9; ++i)
    {
        cout << points3D.at(i).transpose() << " ;" << endl;
    }
    cout << "]" << endl;
    */
    CameraDirectLinearTransformation cdlt;
    cdlt.init(points2d,points3D,Vector4i(0,0,1024,768),ZNEAR,ZFAR);
    cdlt.info();

    GLFWwindow *window = initOpenGLContext(1024,768,60,false,false,0);

    glewInit();
    glutInit(&argc, argv);
    init();
    glfwSetKeyCallback(window, key_callback);
    //glfwSetCursorPosCallback(window, cursor_pos_callback);


    {
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glShadeModel(GL_SMOOTH);
        //glEnable(GL_DEPTH_TEST);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Set depth buffer clear value
        //glClearDepth(0.0);
    }

    while ( !glfwWindowShouldClose(window) )
    {
        drawFrame(window,cdlt);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
