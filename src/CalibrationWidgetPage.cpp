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
    CDLT.init(points2D,points3D,Vector4i(0,0,PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT),1,1E6);
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
        //cerr << this->getPoints3D().at(i).transpose() << " ;" << endl;
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
//Append 2D Points
void CalibrationWidgetPage::append2DPoint(const QPoint &p)
{
	// XXX TO CHANGE WITH REAL POINTS
	//qDebug("XXX RIMETTERE I PUNTI ORIGINALI INVECE CHE QUESTI");
	//points2D.clear();
	/*
	points2D.push_back(Vector3d(512,384,1));
	points2D.push_back(Vector3d(419,474,1));
	points2D.push_back(Vector3d(409,294,1));
	points2D.push_back(Vector3d(589,294,1));
	points2D.push_back(Vector3d(589,474,1));
	points2D.push_back(Vector3d(449,441,1));
	points2D.push_back(Vector3d(449,321,1));
	points2D.push_back(Vector3d(569,321,1));
	points2D.push_back(Vector3d(569,441,1));
	*/
	// CALIBRATION 20 JANUARY 2016
	/*
	points2D.push_back(Vector3d(512, 401, 1));
	points2D.push_back(Vector3d(445,334, 1));
	points2D.push_back(Vector3d(573,336, 1));
	points2D.push_back(Vector3d(570,465, 1));
	points2D.push_back(Vector3d(445,465, 1));
	points2D.push_back(Vector3d(409,301, 1));
	points2D.push_back(Vector3d(599,306, 1));
	points2D.push_back(Vector3d(596,500, 1));
	points2D.push_back(Vector3d(406,500, 1));
	*/
	points2D.push_back(Vector3d(p.x(), p.y(), 1));
	if (points2D.size() == points3D.size())
	{
		ofstream p2dtxt; p2dtxt.open("points2d.csv",'w');
		for (int i = 0; i < points2D.size(); ++i)
		{
			p2dtxt << points2D.at(i).transpose() << endl;
		}
		for (int i = 0; i < points2D.size(); ++i)
		{
			Vector3d kk = points2D.at(i);
			p2dtxt << "points2D.push_back(Vector3d(" << kk.x() << "," << kk.y() << "," << "1 ));" << endl;
		}
		this->computeHomography(points2D);
		this->CDLT.info();
	}
    /*
    points2D.push_back(Vector3d(p.x(),p.y(),1));
    if (points2D.size() == points3D.size())
    {

        this->computeHomography(points2D);
        this->CDLT.info();
    }
    */
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

