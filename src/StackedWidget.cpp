#include "StackedWidget.h"
#include "ui_StackedWidget.h"
#include "ui_ProjectorWidgetPage.h"
#include "ui_CalibrationWidgetPage.h"
#include "ui_VolvuxWidgetPage.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StackedWidget)
{

    //Setup Ui
    ui->setupUi(this);

    //Hide menu and status bar
    this->ui->menuBar->hide();
    this->ui->statusBar->hide();

    //Fullscreen
    //this->showFullScreen();

    //Start timer
    timer = new QTimer(this);
    timer->start();

    //Disable Back button for the first page
    if(this->ui->stackedWidget->currentIndex() == PROJECTORMOTOR_PAGE_INDEX)
    {
        ui->pushButtonBack->setEnabled(false);
    }

    //Initialize and add the stacked widget pages
    projectorWidgetpage = new ProjectorWidgetPage(this);
    this->ui->stackedWidget->addWidget(projectorWidgetpage);
    widgets.append(projectorWidgetpage);
    calibrationWidgetpage = new CalibrationWidgetPage(this);
    this->ui->stackedWidget->addWidget(calibrationWidgetpage);
    widgets.append(calibrationWidgetpage);
    volvuxWidgetpage = new VolvuxWidgetPage(this);
    this->ui->stackedWidget->addWidget(volvuxWidgetpage);
    widgets.append(volvuxWidgetpage);


    //Menu bar
    //Exit Action
    QObject::connect(this->ui->actionExit,SIGNAL(triggered()),this,SLOT(onActionExitTriggered()));
    //Projector Action
    QObject::connect(this->ui->actionProjector,SIGNAL(triggered()),this,SLOT(onActionProjectorMotorTriggered()));
    //Motor Action
    QObject::connect(this->ui->actionMotor,SIGNAL(triggered()),this,SLOT(onActionProjectorMotorTriggered()));
    //Calibration Action
    QObject::connect(this->ui->actionCalibration,SIGNAL(triggered()),this,SLOT(onActionCalibrationTriggered()));

    //Connection navigation buttons
    //Quit
    QObject::connect(this->ui->pushButtonQuit,SIGNAL(clicked()),this,SLOT(onQuitButtonPressed()));
    //Next
    QObject::connect(this->ui->pushButtonNext,SIGNAL(clicked()),this,SLOT(onNextButtonPressed()));
    //Back
    QObject::connect(this->ui->pushButtonBack,SIGNAL(clicked()),this,SLOT(onBackButtonPressed()));

    //Projector control buttons
    //Initialize
    QObject::connect(projectorWidgetpage->ui->pushButtonProjectorInitialize,SIGNAL(clicked()),projectorWidgetpage,SLOT(onPushButtonProjectorInitializeClicked()));
    QObject::connect(projectorWidgetpage,SIGNAL(enableNextButton(bool)),this->ui->pushButtonNext,SLOT(setEnabled(bool)));
    //Release
    QObject::connect(projectorWidgetpage->ui->pushButtonProjectorRelease,SIGNAL(clicked()),projectorWidgetpage,SLOT(onpushButtonProjectorReleaseClicked()));
    QObject::connect(projectorWidgetpage,SIGNAL(enableNextButton(bool)),this->ui->pushButtonNext,SLOT(setEnabled(bool)));

    //Projector settings
    //Projector settings
    QObject::connect(projectorWidgetpage->ui->spinBoxProjectorNSlices,SIGNAL(valueChanged(int)),projectorWidgetpage,SLOT(onSpinboxProjectorNSlicesChanged(int)));
    //LED settings
    QObject::connect(projectorWidgetpage->ui->spinBoxProjectorLEDcurrent,SIGNAL(valueChanged(int)),projectorWidgetpage,SLOT(onSpinboxProjectorLEDCurrentChanged(int)));
    QObject::connect(projectorWidgetpage->ui->doubleSpinBoxProjectorLEDpercentage,SIGNAL(valueChanged(double)),projectorWidgetpage,SLOT(onSpinboxProjectorLEDPercentageChanged(double)));

    //Calibration Widget
    //Insert and remove points
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(lastPointPressed(QPoint)),calibrationWidgetpage,SLOT(append2DPoint(QPoint)));
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(pointRemoved(QPoint)),calibrationWidgetpage,SLOT(remove2DPoint(QPoint)));
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(points2Dupdated(QVector<QPoint>)),calibrationWidgetpage,SLOT(update2DPoints(QVector<QPoint>)));

    QObject::connect(calibrationWidgetpage,SIGNAL(calibrationEmitted(CameraDirectLinearTransformation&)),volvuxWidgetpage->ui->widget,SLOT(setCamera(CameraDirectLinearTransformation&)));
}

StackedWidget::~StackedWidget()
{
    delete ui;
}

//Show current widget
void StackedWidget::showCurrentWidget(int curr_index){
    if (widgets.count() > 0){
        foreach (QWidget * widget, widgets)
            widget->hide();
        widgets.at(curr_index)->show();
        updateGeometry();
    }
}

void StackedWidget::keyPressEvent(QKeyEvent *event){
    int keypressed = event->key();
    //Handles esc button pression
    switch (keypressed){
    case Qt::Key_Escape :
    {
        //this->saveData();
        QApplication::quit();
        break;
    }
    }
}

//Navigation button
//Quit SLOT
void StackedWidget::onQuitButtonPressed()
{
    QMessageBox::warning(this,"Leaving Volvux","You are now exiting...");
    QApplication::exit(0);
}

//Next SLOT
void StackedWidget::onNextButtonPressed()
{
    //Check stacked widget current index
    int curIndex = this->ui->stackedWidget->currentIndex();
    //Increment index
    curIndex = curIndex + 1;

    //Manage page settings
    switch(curIndex){
    case CALIBRATION_PAGE_INDEX:
        //Set focus on VolvuxCalibrationWidget
        calibrationWidgetpage->ui->volvuxCalibrationWidget->setFocusPolicy(Qt::StrongFocus);
        //Set ALP pointer in Volvux Calibration Widget
        calibrationWidgetpage->ui->volvuxCalibrationWidget->setALP(projectorWidgetpage->palp);
		timer->start(10);
		//To send frame to the projector
		QObject::connect(this->timer, SIGNAL(timeout()), calibrationWidgetpage->ui->volvuxCalibrationWidget, SLOT(transferFrame()));
		//Enable back button
        this->ui->pushButtonBack->setEnabled(true);
        //Hide menu and status bar
        this->ui->menuBar->hide();
        this->ui->statusBar->hide();

        break;
    case MAINWINDOW_PAGE_INDEX:
        //Enable back button
        this->ui->pushButtonBack->setEnabled(true);
        //Show menu and status bar
        this->ui->menuBar->show();
        this->ui->statusBar->show();
        //Disable next button
        this->ui->pushButtonNext->setEnabled(false);
        break;
    }

    //Next action
    this->ui->stackedWidget->setCurrentIndex(curIndex);
}

//Back SLOT
void StackedWidget::onBackButtonPressed()
{
    //Check stacked widget current index
    int curIndex = this->ui->stackedWidget->currentIndex();
    //Decrement index
    curIndex = curIndex - 1;

    //Manage page settings
    switch(curIndex) {
    case PROJECTORMOTOR_PAGE_INDEX:
        //Hide menu and status bar
        this->ui->menuBar->hide();
        this->ui->statusBar->hide();
        //Disable back button
        this->ui->pushButtonBack->setEnabled(false);
        break;
    case CALIBRATION_PAGE_INDEX:
        //Hide menu and status bar
        this->ui->menuBar->hide();
        this->ui->statusBar->hide();
        //Enable next button
        this->ui->pushButtonNext->setEnabled(true);
    }

    //Back action
    this->ui->stackedWidget->setCurrentIndex(curIndex);
}

//Menu bar
//Exit Action SLOT
void StackedWidget::onActionExitTriggered()
{
    QApplication::quit();
}

//Projector and  Motor Action SLOT
void StackedWidget::onActionProjectorMotorTriggered(){
    this->ui->stackedWidget->setCurrentIndex(PROJECTORMOTOR_PAGE_INDEX);
    this->ui->menuBar->hide();
    this->ui->pushButtonBack->setEnabled(false);
    this->ui->pushButtonNext->setEnabled(true);
}

//Calibration
void StackedWidget::onActionCalibrationTriggered() {
    this->ui->stackedWidget->setCurrentIndex(CALIBRATION_PAGE_INDEX);
    this->ui->menuBar->hide();
    this->ui->pushButtonNext->setEnabled(true);
}
