#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>

namespace Ui
{
    class StackedWidget;
}

class StackedWidgetHelper; // forward declaration

class StackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    StackedWidget(QWidget *parent = 0);
    ~StackedWidget();
    Ui::StackedWidget* getUi(){return this->ui;}

private slots:
    void onPushButtonNextStackedWidget(bool value);
    void onPushButtonPreviousStackedWidget(bool value);
    void onCancelPressed(bool value);
    //Projector Slots
    void onPushButtonProjectorInitializeClicked(bool value);
    void onPushButtonProjectorReleaseClicked(bool value);

    void onSpinboxProjectorNSlicesChanged(int nSlices);
    void onSpinboxProjectorLEDCurrentChanged(int current);
    void onSpinboxProjectorLEDPercentageChanged(double percentage);
    //Motor Slots
    void onPushButtonMotorStartClicked(bool value);
    void onPushButtonMotorStopClicked(bool value);
    void onSpinboxFlickerRateChanged(double flickerRate);

protected:
    void keyPressEvent(QKeyEvent *e);
    Ui::StackedWidget *ui;
    StackedWidgetHelper *helper;
};

#endif // STACKEDWIDGET_H
