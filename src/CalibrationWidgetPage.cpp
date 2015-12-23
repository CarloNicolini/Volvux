#include "CalibrationWidgetPage.h"
#include "ui_CalibrationWidgetPage.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

using std::ifstream;
using std::vector;

CalibrationWidgetPage::CalibrationWidgetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationWidgetPage)
{
    ui->setupUi(this);
    //Set 3D points
    for (int i=0; i<9; ++i)
    {
        Eigen::Vector4d p;
        p << calibrationtoy[i*3],calibrationtoy[i*3+1],calibrationtoy[i*3+2],1;
        points3D.push_back(p);
    }
    //Write 3D points
    this->write3DPoints();
    //Set ALP projector

}

CalibrationWidgetPage::~CalibrationWidgetPage()
{
    delete ui;
}

/**
 * @brief CalibrationWidgetPage::getPoints3D
 * @return
 */
//Get points 3D
const stlalignedvector4d &CalibrationWidgetPage::getPoints3D() const
{
    return points3D;
}

/**
 * @brief CalibrationWidgetPage::getPoints2D
 * @return
 */
//Get points 2D
const std::vector<Vector3d> &CalibrationWidgetPage::getPoints2D() const
{
    return points2D;
}

/**
 * @brief CalibrationWidgetPage::computeHomography
 * @param points
 */
//Compute Homography
void CalibrationWidgetPage::computeHomography(const vector<Vector3d> &points)
{
    points2D.clear();
    CDLT.init(points2D,points3D,Vector4i(0,0,PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT),1,1E4);
    emit calibrationEmitted(CDLT);
}

//Write 3D points
void CalibrationWidgetPage::write3DPoints()
{
    for (size_t i=0; i<9; i++)
    {
        QString valuePoint3D = QString::number(this->getPoints3D().at(i).x(),'g',2) + QString(",") +
                QString::number(this->getPoints3D().at(i).y(),'g',2) + QString(",") +
                QString::number(this->getPoints3D().at(i).z(),'g',2) + QString(",");
        QLabel *lab = new QLabel(valuePoint3D,this);
        this->ui->verticalLayout3Dpoints->addWidget(lab);
    }
}

//Clear layout function
void CalibrationWidgetPage::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

//SLOTS
/**
 * @brief CalibrationWidgetPage::append2DPoint
 * @param p
 */
//Append 2D Points SLOT
void CalibrationWidgetPage::append2DPoint(const QPoint &p)
{
    points2D.push_back(Vector3d(p.x(),p.y(),1));
    if (points2D.size() == points3D.size())
    {
        this->computeHomography(points2D);
        this->CDLT.info();
    }
}

/**
 * @brief CalibrationWidgetPage::remove2DPoint
 * @param p
 */
//Remove 2D Point SLOT
void CalibrationWidgetPage::remove2DPoint(const QPoint &p)
{
    Vector3d x(p.x(),p.y(),1.0);
    std::vector<Vector3d>::iterator it = std::find(points2D.begin(),points2D.end(),x);
    points2D.erase(it);
}

//Update 2D Points SLOT
void CalibrationWidgetPage::update2DPoints(const QVector<QPoint> &points2D){
    clearLayout(this->ui->verticalLayout2Dpoints,true);

    for (int i=0; i<points2D.size(); i++)
    {
        QString valuePoint2D = QString::number(QPoint(points2D.at(i)).x()) + "," + QString::number(QPoint(points2D.at(i)).y());
        QLabel *lab = new QLabel(valuePoint2D,this);
        this->ui->verticalLayout2Dpoints->addWidget(lab);
    }
}

