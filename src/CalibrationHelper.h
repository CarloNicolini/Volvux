#ifndef CALIBRATIONHELPER_H
#define CALIBRATIONHELPER_H

#include <QObject>
#include <QPoint>
#include <vector>
#include "Homography.h"

#define PROJECTOR_RESOLUTION_WIDTH 1024
#define PROJECTOR_RESOLUTION_HEIGHT 768

class CalibrationHelper : public QObject
{
    Q_OBJECT
public:
    explicit CalibrationHelper(QObject *parent = 0);
    ~CalibrationHelper();
    void loadPoints3D(const QString &filename);
    void loadPoints2D(const QString &filename);

    const std::vector<Vector3d> &getPoints2D() const;
    const std::vector<Vector4d> &getPoints3D() const;

signals:

public slots:
    void append2DPoint(const QPoint &p);
    void remove2DPoint(const QPoint &p);

private:
    void computeHomography(const vector<Vector3d> &points);
    std::vector<Vector3d> points2D;
    std::vector<Vector4d> points3D;
    CameraDirectLinearTransformation CDLT;
};


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


#endif // CALIBRATIONHELPER_H
