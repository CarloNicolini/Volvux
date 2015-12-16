#ifndef CALIBRATIONWIDGETPAGE_H
#define CALIBRATIONWIDGETPAGE_H


#include <QWidget>
#include <QPoint>
#include <QLabel>
#include <vector>
#include "Homography.h"

#define PROJECTOR_RESOLUTION_WIDTH 1024
#define PROJECTOR_RESOLUTION_HEIGHT 768


namespace Ui {
class CalibrationWidgetPage;
}

class CalibrationWidgetPage : public QWidget
{
    Q_OBJECT

public:
    explicit CalibrationWidgetPage(QWidget *parent = 0);
    ~CalibrationWidgetPage();
    Ui::CalibrationWidgetPage *ui;

    const std::vector<Vector3d> &getPoints2D() const;
    const stlalignedvector4d &getPoints3D() const;

private:
    std::vector<Vector3d> points2D;
    stlalignedvector4d points3D;
    CameraDirectLinearTransformation CDLT;

    void computeHomography(const vector<Vector3d> &points);
    void clearLayout(QLayout* layout, bool deleteWidgets);
    void write3DPoints();

signals:
    void calibrationEmitted(CameraDirectLinearTransformation &cam);

public slots:
    void append2DPoint(const QPoint &p);
    void remove2DPoint(const QPoint &p);
    void update2DPoints(const QVector<QPoint> &points2D);
};

#define CALIBRECT_EDGE_BOTTOM 7.1
#define CALIBRECT_EDGE_TOP 5
#define CALIBRECT_HEIGHT 1.5

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

#endif // CALIBRATIONWIDGETPAGE_H