#ifndef STACKEDWIDGETHELPER_H
#define STACKEDWIDGETHELPER_H

#define MOTOR_UNITS_TO_REV_MIN 65536

#include "StackedWidget.h"

class StackedWidgetHelper : public StackedWidget
{
public:
    void updateMotorRate(int nSlices, double tFrameMicroSeconds);

#ifdef ALP_SUPPORT
    ALPProjector alp;
#endif

#if defined (SMI_SUPPORT) && (WIN32)
    INTEGMOTORINTERFACELib::ISMICommPtr CommInterface;
#endif
};

#endif // STACKEDWIDGETHELPER_H
