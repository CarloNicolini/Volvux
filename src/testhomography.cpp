#include <iostream>
#include <vector>
#include <Eigen/Core>
#include "Homography.h"

using namespace Eigen;
using namespace std;


#define CALIBRECT_EDGE_BOTTOM 7.1
#define CALIBRECT_EDGE_TOP 5
#define CALIBRECT_HEIGHT 1.5

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


int main()
{

    vector<Vector4d> points3D;
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

    CameraDirectLinearTransformation cam;
    cam.init(points2d,points3D,true,true,0,0,1024,768,0.1,1000);
    cam.info();
    return 0;
}
