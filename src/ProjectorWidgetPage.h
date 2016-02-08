#ifndef PROJECTORWIDGETPAGE_H
#define PROJECTORWIDGETPAGE_H

#define MOTOR_UNITS_TO_REV_MIN 65536

#include <QWidget>
#include <QMessageBox>
#include "ALPProjector.h"
#include "CalibrationWidgetPage.h"
#if defined (SMI_SUPPORT) && (WIN32)
#include "SmartMotor.h"
#endif

namespace Ui {
class ProjectorWidgetPage;
}

class ProjectorWidgetPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectorWidgetPage(QWidget *parent = 0);
    ~ProjectorWidgetPage();
    Ui::ProjectorWidgetPage *ui;
    //ALP Projector
    ALPProjector *palp;
    ALPProjector* getALP();
#if defined (SMI_SUPPORT) && (WIN32)
	SmartMotor *motor;
#endif

private:
    void updateMotorRate(int nSlices, double tFrameMicroSeconds);

public slots:
    //Projector control buttons
    void onPushButtonProjectorInitializeClicked();
    void onpushButtonProjectorReleaseClicked();
    //Projector settings
    void onSpinboxProjectorNSlicesChanged(int nSlices);
    void onSpinboxProjectorLEDCurrentChanged(int current);
    void onSpinboxProjectorLEDPercentageChanged(double percentage);

    //Motor control buttons
    void onPushButtonMotorStartClicked();
    void onPushButtonMotorStopClicked();
    void onPushButtonMotorInitializeClicked();
    //Motor settings
    void onSpinboxFlickerRateChanged(double flickerRate);
    void projectDataFrames(unsigned char *data);
	
signals:
    void enableNextButton(bool);

private:
	unsigned char *lastframe;
};

#endif // PROJECTORWIDGETPAGE_H
