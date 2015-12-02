#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>

#define MOTOR_UNITS_TO_REV_MIN 65536

namespace Ui {
class StackedWidget;
}

class StackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = 0);
    ~StackedWidget();

private slots:
    void onPushButtonNextStackedWidget(bool value);
    void onPushButtonPreviousStackedWidget(bool value);
    void onCancelPressed(bool value);
    //Projector Slots
    void onPushButtonProjectorInitializeClicked(bool value);
    void onPushButtonProjectorReleaseClicked(bool value);
    void onSpinboxProjectorMicrosecondsPerFrameChanged(int value);
    void onSpinboxProjectorNSlicesChanged(int value);
    void onSpinboxProjectorLEDCurrentChanged(int current);
    void onSpinboxProjectorLEDPercentageChanged(double percentage);
    //Motor Slots
    void onPushButtonMotorStartClicked(bool value);
    void onPushButtonMotorStopClicked(bool value);
    void onSpinboxFlickerRateChanged(double flickerRate);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::StackedWidget *ui;
};

#endif // STACKEDWIDGET_H
