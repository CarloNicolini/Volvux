#include <iostream>
#include <fstream>
#include <stdexcept>
#include "CalibrationHelper.h"

using std::ifstream;
using std::vector;

/**
 * @brief CalibrationHelper::CalibrationHelper
 * @param parent
 */
CalibrationHelper::CalibrationHelper(QObject *parent) : QObject(parent)
{
    for (int i=0; i<9; ++i)
    {
        Eigen::Vector4d p;
        p << calibrationtoy[i*3],calibrationtoy[i*3+1],calibrationtoy[i*3+2],1;
        points3D.push_back(p);
    }
}

/**
 * @brief CalibrationHelper::~CalibrationHelper
 */
CalibrationHelper::~CalibrationHelper()
{
}

/**
 * @brief CalibrationHelper::append2DPoint
 * @param p
 */
void CalibrationHelper::append2DPoint(const QPoint &p)
{
    points2D.push_back(Vector3d(p.x(),p.y(),1));
    if (points2D.size() == points3D.size())
    {
        this->computeHomography(points2D);
        this->CDLT.info();
    }
}

/**
 * @brief CalibrationHelper::remove2DPoint
 * @param p
 */
void CalibrationHelper::remove2DPoint(const QPoint &p)
{
    Vector3d x(p.x(),p.y(),1.0);
    std::vector<Vector3d>::iterator it = std::find(points2D.begin(),points2D.end(),x);
    points2D.erase(it);
}

/**
 * @brief CalibrationHelper::loadPoints2D
 * @param filename
 */
void CalibrationHelper::loadPoints2D(const QString &filename)
{
    ifstream is;
    is.open(filename.toStdString().c_str());
    this->points2D.clear();
    double x,y;
    while( (is >> x ) &&  (is >> y) )
    {
        points2D.push_back(Vector3d(x,y,1.0));
    }
}

/**
 * @brief CalibrationHelper::loadPoints3D
 * @param filename
 */
void CalibrationHelper::loadPoints3D(const QString &filename)
{
    ifstream is;
    is.open(filename.toStdString().c_str());
    this->points3D.clear();
    double x,y,z;
    while( (is >> x ) &&  (is >> y) && (is>>z) )
    {
        points3D.push_back(Vector4d(x,y,z,1.0));
    }
}

/**
 * @brief CalibrationHelper::computeHomography
 * @param points
 */
void CalibrationHelper::computeHomography(const vector<Vector3d> &points)
{
    CDLT.init(points2D,points3D,true,true,0,0,PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);
    CDLT.info();
}

/**
 * @brief CalibrationHelper::getPoints3D
 * @return
 */
const stlalignedvector4d &CalibrationHelper::getPoints3D() const
{
    return points3D;
}

/**
 * @brief CalibrationHelper::getPoints2D
 * @return
 */
const std::vector<Vector3d> &CalibrationHelper::getPoints2D() const
{
    return points2D;
}
