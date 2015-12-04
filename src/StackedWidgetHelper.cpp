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
    this->alp->stop();
    delete this->alp;
}

ALPProjector* StackedWidgetHelper::getALP()
{
    return this->alp;
}

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
        QString valuePoint3D = QString::number(c->getPoints3D().at(i).x()) + QString(",") +
                QString::number(c->getPoints3D().at(i).y()) + QString(",") +
                QString::number(c->getPoints3D().at(i).z()) + QString(",");
        QLabel *lab = new QLabel(valuePoint3D,_parent);
        ui->verticalLayout3Dpoints->addWidget(lab);
    }
}


