#ifndef STACKEDWIDGETHELPER_H
#define STACKEDWIDGETHELPER_H

#define MOTOR_UNITS_TO_REV_MIN 65536

#include <vector>
#include <Eigen/Core>
#include "StackedWidget.h"

class StackedWidgetHelper
{
public:
    StackedWidgetHelper(StackedWidget *parent)
    {
        _parent = parent;
        ui = parent->getUi();
    }
    ~StackedWidgetHelper(){};

    void updateMotorRate(int nSlices, double tFrameMicroSeconds);
    void write3DPoints(CalibrationHelper *c);
#ifdef ALP_SUPPORT
    ALPProjector alp;
#endif

#if defined (SMI_SUPPORT) && (WIN32)
    INTEGMOTORINTERFACELib::ISMICommPtr CommInterface;
#endif
protected:
    StackedWidget *_parent;
    Ui::StackedWidget *ui;
};

#endif // STACKEDWIDGETHELPER_H
