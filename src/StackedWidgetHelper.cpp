#include "StackedWidgetHelper.h"
#include "ui_StackedWidget.h"

StackedWidgetHelper::StackedWidgetHelper(StackedWidget *parent)
{
    _parent = parent;
    ui = parent->getUi();
    alp = new ALPProjector();
}

StackedWidgetHelper::~StackedWidgetHelper()
{
    delete this->alp;
}

ALPProjector* StackedWidgetHelper::getALP()
{
    return this->alp;
}

//Update Motor rate
void StackedWidgetHelper::updateMotorRate(int nSlices, double tFrameMicroSeconds)
{
    double motorRate = (1E6/(nSlices*tFrameMicroSeconds)) * MOTOR_UNITS_TO_REV_MIN;
    ui->spinBoxMotorSpeed->setValue((int)motorRate);
    if ( motorRate > ui->spinBoxMotorSpeed->maximum() )
    {
        ui->spinBoxMotorSpeed->setEnabled(false);
    }
    else
    {
        ui->spinBoxMotorSpeed->setEnabled(true);
    }
}

void StackedWidgetHelper::write3DPoints(CalibrationHelper *c)
{
    for (size_t i=0; i<9; i++)
    {
        QString valuePoint3D = QString::number(c->getPoints3D().at(i).x(),'g',2) + QString(",") +
                QString::number(c->getPoints3D().at(i).y(),'g',2) + QString(",") +
                QString::number(c->getPoints3D().at(i).z(),'g',2) + QString(",");
        QLabel *lab = new QLabel(valuePoint3D,_parent);
        ui->verticalLayout3Dpoints->addWidget(lab);
    }
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
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

void StackedWidgetHelper::update2DPoints(const QVector<QPoint> &points2D)
{
    clearLayout(ui->verticalLayout2Dpoints,true);

    for (int i=0; i<points2D.size(); i++)
    {
        QString valuePoint2D = QString::number(QPoint(points2D.at(i)).x()) + "," + QString::number(QPoint(points2D.at(i)).y());
        QLabel *lab = new QLabel(valuePoint2D,_parent);
        ui->verticalLayout2Dpoints->addWidget(lab);
    }
}
