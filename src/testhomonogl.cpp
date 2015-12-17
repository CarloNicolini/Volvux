#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

#include "Homography.h"

using namespace Eigen;
using namespace std;

#ifndef CALIBRECT_EDGE_BOTTOM
#define CALIBRECT_EDGE_BOTTOM 71.0
#endif

#ifndef CALIBRECT_EDGE_TOP
#define CALIBRECT_EDGE_TOP 50.0
#endif
#ifndef CALIBRECT_HEIGHT
#define CALIBRECT_HEIGHT 15.0
#endif
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

int main()
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
    for (int i=0; i<9; i++)
    {
        cout << points2d.at(i).transpose() << endl;
    }
    cout << endl;
    for (int i=0; i<9; i++)
    {
        cout << points3D.at(i).transpose() << endl;
    }
    return 0;
    */

    CameraDirectLinearTransformation cdlt;
    double znear=10.0;
    double zfar = 800;
    cdlt.init(points2d,points3D,true,true,0,0,1024,768,znear,zfar);
    
    cdlt.info();

    return 0;
}
