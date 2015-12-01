#include "QMessageBox"
#include "StackedWidget.h"
#include "VolvuxCalibrationWidget.h"
#include "ui_StackedWidget.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWidget)
{
    ui->setupUi(this);
    this->setCurrentIndex(0);
    // Projector buttons
    QObject::connect(ui->pushButtonNextProjector,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelProjector,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));
    // Motor buttons
    QObject::connect(ui->pushButtonNextMotor,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonPreviousMotor,SIGNAL(clicked(bool)),this,SLOT(onPushButtonPreviousStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelMotor,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));
    // Calibration buttons
    QObject::connect(ui->pushButtonNextCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonPreviousCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonPreviousStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelCalibration,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));
}

StackedWidget::~StackedWidget()
{
    delete ui;
}

void StackedWidget::onPushButtonNextStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    if (curIndex==2)
        ui->volvuxCalibrationWidget->resize(1024,768);
    this->setCurrentIndex(curIndex+1);
}

void StackedWidget::onPushButtonPreviousStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    this->setCurrentIndex(curIndex-1);
}

void StackedWidget::onCancelPressed(bool value)
{
    QMessageBox::warning(this,"Leaving Volvux","You are now exiting...");
    QApplication::exit(0);
}

/**
 * @brief StackedWidget::keyPressEvent
 * @param e
 */
void StackedWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_T:
    {
        ui->volvuxCalibrationWidget->toggleText();
        break;
    }
    case Qt::Key_Up:
    {
        ui->volvuxCalibrationWidget->moveCursor(0,-1);
        break;
    }
    case Qt::Key_Down:
    {
        ui->volvuxCalibrationWidget->moveCursor(0,-1);
        break;
    }
    case Qt::Key_Right:
    {
        ui->volvuxCalibrationWidget->moveCursor(-1,0);
        break;
    }
    case Qt::Key_Left:
    {
        ui->volvuxCalibrationWidget->moveCursor(-1,0);
        break;
    }
    case Qt::Key_R:
    {
        ui->volvuxCalibrationWidget->addPoint();
        break;
    }
    case Qt::Key_S:
    {
        ui->volvuxCalibrationWidget->saveData();
        break;
    }
    case Qt::Key_Escape :
    {
        ui->volvuxCalibrationWidget->saveData();
        QApplication::quit();
        break;
    }
    }
}
