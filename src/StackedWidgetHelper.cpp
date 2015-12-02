#include "StackedWidgetHelper.h"
#include "ui_StackedWidget.h"

void StackedWidgetHelper::updateMotorRate(int nSlices, double tFrameMicroSeconds)
{
    double motorRate = (1E6/(nSlices*tFrameMicroSeconds)) * MOTOR_UNITS_TO_REV_MIN;
    StackedWidget::ui->spinBoxMotorSpeed->setValue((int)motorRate);
    if ( motorRate > ui->spinBoxMotorSpeed->maximum() )
    {
        ui->spinBoxMotorSpeed->setEnabled(false);
    }
    else
    {
        ui->spinBoxMotorSpeed->setEnabled(true);
    }
}
