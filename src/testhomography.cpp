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

using namespace Eigen;
using namespace std;

#define CALIBRECT_EDGE_BOTTOM 7.1
#define CALIBRECT_EDGE_TOP 5
#define CALIBRECT_HEIGHT 1.5

stlalignedvector4d points3D;

static const double calibrationtoy[]  = {0,0,0,
                                         -CALIBRECT_EDGE_BOTTOM/2,0, CALIBRECT_EDGE_BOTTOM/2,
                                         CALIBRECT_EDGE_BOTTOM/2,  0, CALIBRECT_EDGE_BOTTOM/2,
                                         CALIBRECT_EDGE_BOTTOM/2,  0, -CALIBRECT_EDGE_BOTTOM/2,
                                         -CALIBRECT_EDGE_BOTTOM/2, 0, -CALIBRECT_EDGE_BOTTOM/2,
                                         -CALIBRECT_EDGE_TOP/2,CALIBRECT_HEIGHT, CALIBRECT_EDGE_TOP/2,
                                         CALIBRECT_EDGE_TOP/2,  CALIBRECT_HEIGHT, CALIBRECT_EDGE_TOP/2,
                                         CALIBRECT_EDGE_TOP/2,  CALIBRECT_HEIGHT, -CALIBRECT_EDGE_TOP/2,
                                         -CALIBRECT_EDGE_TOP/2, CALIBRECT_HEIGHT, -CALIBRECT_EDGE_TOP/2
                                        };

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
}

static void mouse_entered_callback(GLFWwindow *window, int entered)
{
    printf("%d\n",entered);
}

GLFWwindow *initOpenGLContext(const int width=1024, const int height=768, const int refreshRate=60, const bool gamemode=false, const bool stereo=false, const int fsaaSamples=1)
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

void drawObject()
{
    double e=10;

    glLineWidth(1.0f);
    glPointSize(5);

    glBegin(GL_LINE_LOOP);
    glColor3d(0,0,1);
    glVertex3d(-e,0,e);
    glVertex3d(e,0,e);
    glVertex3d(e,0,-e);
    glVertex3d(-e,0,-e);
    glEnd();

    glBegin(GL_POINTS);
    for (int i=0; i<9; i++)
        glVertex3dv(points3D.at(i).data());
    glEnd();

    glutWireCube(10);
}

void draw2Dpoints()
{

}

void drawFrame(GLFWwindow *window, CameraDirectLinearTransformation &cdlt)
{
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height*100;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixd(cdlt.getOpenGLProjectionMatrix().data());
    //glOrtho(-ratio, ratio, -100.f, 100.f, 100.f, -100.f);
    glMatrixMode(GL_MODELVIEW);

    //glLoadIdentity();
    Affine3d MV = cdlt.getOpenGLModelViewMatrix();

    glLoadMatrixd(MV.data());

    //glRotatef((float) glfwGetTime() * 50.f, 1.0f, 0.f, 1.f);
    drawObject();
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
    points2d.push_back(Vector3d(602,472,1));
    points2d.push_back(Vector3d(591,286,1));
    points2d.push_back(Vector3d(403,293,1));
    points2d.push_back(Vector3d(423,479,1));
    points2d.push_back(Vector3d(573,440,1));
    points2d.push_back(Vector3d(573,310,1));
    points2d.push_back(Vector3d(443,329,1));
    points2d.push_back(Vector3d(448,458,1));

    CameraDirectLinearTransformation cdlt;
    cdlt.init(points2d,points3D,true,true,0,0,1024,768,0.1,1000);
    cdlt.info();

    GLFWwindow *window = initOpenGLContext(1024,768,60,false,false,1);

    glewInit();
    glutInit(&argc, argv);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);


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
