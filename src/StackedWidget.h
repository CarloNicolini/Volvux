#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#define PROJECTORMOTOR_PAGE_INDEX 0
#define CALIBRATION_PAGE_INDEX 1
#define MAINWINDOW_PAGE_INDEX 2

#include <QMainWindow>
#include <QMessageBox>
#include "ProjectorWidgetPage.h"
#include "CalibrationWidgetPage.h"
#include "VolvuxWidgetPage.h"
#include "ExtraWindow.h"

namespace Ui {
class StackedWidget;
}

class ProjectorWidgetPage;

class StackedWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = 0);
    ~StackedWidget();
    ProjectorWidgetPage *projectorWidgetpage;
    CalibrationWidgetPage *calibrationWidgetpage;
    VolvuxWidgetPage *volvuxWidgetpage;
    QTimer *timer;
	ExtraWindow *extraWindow;

private:
    Ui::StackedWidget *ui;
    QList<QWidget *> widgets;
    void showCurrentWidget(int curr_index);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    //Navigation buttons
    void onQuitButtonPressed();
    void onNextButtonPressed();
    void onBackButtonPressed();


private slots:
    //Menu bar actions
    void onActionExitTriggered();
    void onActionProjectorMotorTriggered();
    void onActionCalibrationTriggered();
};

#endif // STACKEDWIDGET_H
