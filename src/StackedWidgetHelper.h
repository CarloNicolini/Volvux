#ifndef STACKEDWIDGETHELPER_H
#define STACKEDWIDGETHELPER_H

#define MOTOR_UNITS_TO_REV_MIN 65536

#include <QObject>
#include <vector>
#include <Eigen/Core>
#include "StackedWidget.h"
#include "ALPProjector.h"

class StackedWidgetHelper : public QObject
{
    Q_OBJECT
public:
    StackedWidgetHelper(StackedWidget *parent);
    ~StackedWidgetHelper();
    void updateMotorRate(int nSlices, double tFrameMicroSeconds);
    void write3DPoints(CalibrationHelper *c);
    ALPProjector* getALP();
	/*
#if defined (SMI_SUPPORT) && (WIN32)
    INTEGMOTORINTERFACELib::ISMICommPtr CommInterface;
#endif
	*/
public slots:
    void update2DPoints(const QVector<QPoint> &points2D);

protected:
    StackedWidget *_parent;
    Ui::StackedWidget *ui;
    ALPProjector *alp;
};

#endif // STACKEDWIDGETHELPER_H
