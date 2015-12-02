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
        fillWorldCoordinates();
    }
    ~StackedWidgetHelper(){};

    void updateMotorRate(int nSlices, double tFrameMicroSeconds);
    void computeHomography(const std::vector<QPoint> &images, const std::vector<Eigen::Vector3d> &world);
    const std::vector<Eigen::Vector4d> getWorldCalibrationCoords() const
    {
        return worldCalibrationCoordinates;
    }
#ifdef ALP_SUPPORT
    ALPProjector alp;
#endif

#if defined (SMI_SUPPORT) && (WIN32)
    INTEGMOTORINTERFACELib::ISMICommPtr CommInterface;
#endif
    void fillWorldCoordinates();
protected:
    StackedWidget *_parent;
    Ui::StackedWidget *ui;

    std::vector<Eigen::Vector4d> worldCalibrationCoordinates;
};

#endif // STACKEDWIDGETHELPER_H
