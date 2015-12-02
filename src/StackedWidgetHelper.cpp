#include "StackedWidgetHelper.h"
#include "ui_StackedWidget.h"


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

void StackedWidgetHelper::fillWorldCoordinates()
{
    worldCalibrationCoordinates.push_back(Vector4d(0,0,0,1));
    worldCalibrationCoordinates.push_back(Vector4d(1,0,0,1));
    worldCalibrationCoordinates.push_back(Vector4d(0,1,0,1));
    worldCalibrationCoordinates.push_back(Vector4d(0,0,1,1));
    worldCalibrationCoordinates.push_back(Vector4d(1,1,0,1));
    worldCalibrationCoordinates.push_back(Vector4d(0,1,1,1));
    worldCalibrationCoordinates.push_back(Vector4d(1,0,1,1));
    worldCalibrationCoordinates.push_back(Vector4d(1,0,1,1));
    worldCalibrationCoordinates.push_back(Vector4d(1,0,1,1));
}
