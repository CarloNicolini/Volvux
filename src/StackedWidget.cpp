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

    //Start timer
    timer = new QTimer(this);
    timer->start();

    //Disable Back button for the first page
    if(this->ui->stackedWidget->currentIndex() == PROJECTORMOTOR_PAGE_INDEX)
    {
        this->ui->pushButtonBack->setEnabled(false);
    }

    //Initialize and add the stacked widget pages
    projectorWidgetpage = new ProjectorWidgetPage(this);
    this->ui->stackedWidget->addWidget(projectorWidgetpage);
    calibrationWidgetpage = new CalibrationWidgetPage(this);
    this->ui->stackedWidget->addWidget(calibrationWidgetpage);
    volvuxWidgetpage = new VolvuxWidgetPage(this);
    this->ui->stackedWidget->addWidget(volvuxWidgetpage);

    //Initialize NSlices and FlickerRate using default value
    projectorWidgetpage->onSpinboxProjectorNSlicesChanged(PROJECTOR_SLICES_NUMBER);
	projectorWidgetpage->onPushButtonMotorInitializeClicked();
	projectorWidgetpage->getMotorAbsolutePosition();
	

    //Connection Menu bar
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

    //Connection status bar
    QObject::connect(volvuxWidgetpage,SIGNAL(writeOnStatusBar(QString,int)),this->ui->statusBar,SLOT(showMessage(QString,int)));


	//Connections Projector Page
    //Projector control buttons
    //Initialize
    QObject::connect(projectorWidgetpage->ui->pushButtonProjectorInitialize,SIGNAL(clicked()),projectorWidgetpage,SLOT(onPushButtonProjectorInitializeClicked()));
    QObject::connect(projectorWidgetpage,SIGNAL(enableNextButton(bool)),this->ui->pushButtonNext,SLOT(setEnabled(bool)));
    //Release
    QObject::connect(projectorWidgetpage->ui->pushButtonProjectorRelease,SIGNAL(clicked()),projectorWidgetpage,SLOT(onpushButtonProjectorReleaseClicked()));
    QObject::connect(projectorWidgetpage,SIGNAL(enableNextButton(bool)),this->ui->pushButtonNext,SLOT(setEnabled(bool)));

    //Projector settings
	QObject::connect(projectorWidgetpage->ui->spinBoxProjectorNSlices,SIGNAL(valueChanged(int)),projectorWidgetpage,SLOT(onSpinboxProjectorNSlicesChanged(int)));
	QObject::connect(projectorWidgetpage->ui->doubleSpinBoxMotorFlickerRate, SIGNAL(valueChanged(double)), projectorWidgetpage, SLOT(onSpinboxFlickerRateChanged(double)));
    //LED settings
    QObject::connect(projectorWidgetpage->ui->spinBoxProjectorLEDcurrent,SIGNAL(valueChanged(int)),projectorWidgetpage,SLOT(onSpinboxProjectorLEDCurrentChanged(int)));
    QObject::connect(projectorWidgetpage->ui->doubleSpinBoxProjectorLEDpercentage,SIGNAL(valueChanged(double)),projectorWidgetpage,SLOT(onSpinboxProjectorLEDPercentageChanged(double)));

    //Motor control buttons
    //Initialize
    QObject::connect(projectorWidgetpage->ui->pushButtonMotorInitialize, SIGNAL(clicked()), projectorWidgetpage, SLOT(onPushButtonMotorInitializeClicked()));
    QObject::connect(projectorWidgetpage->ui->pushButtonMotorStart, SIGNAL(clicked()), projectorWidgetpage, SLOT(onPushButtonMotorStartClicked()));
    QObject::connect(projectorWidgetpage->ui->pushButtonMotorStop, SIGNAL(clicked()), projectorWidgetpage, SLOT(onPushButtonMotorStopClicked()));
	//Motor position
	QObject::connect(projectorWidgetpage->ui->pushButtonMotorStart, SIGNAL(clicked()), projectorWidgetpage, SLOT(getMotorAbsolutePosition()));
	//Set motor position to 0
	QObject::connect(projectorWidgetpage->ui->pushButtonMotorDefault, SIGNAL(clicked()), projectorWidgetpage, SLOT(setMotorDefaultPosition()));


	//Connection Calibration Page
    //Calibration Widget
    //Insert and remove points
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(lastPointPressed(QPoint)),calibrationWidgetpage,SLOT(append2DPoint(QPoint)));
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(pointRemoved(QPoint)),calibrationWidgetpage,SLOT(remove2DPoint(QPoint)));
    QObject::connect(calibrationWidgetpage->ui->volvuxCalibrationWidget,SIGNAL(points2Dupdated(QVector<QPoint>)),calibrationWidgetpage,SLOT(update2DPoints(QVector<QPoint>)));
    QObject::connect(calibrationWidgetpage,SIGNAL(calibrationEmitted(CameraDirectLinearTransformation&)),volvuxWidgetpage->ui->widget,SLOT(setCamera(CameraDirectLinearTransformation&)));
	//Points saving and loading
	QObject::connect(calibrationWidgetpage->ui->pushButtonLoad2DPoints, SIGNAL(clicked()), calibrationWidgetpage, SLOT(load2DpointsFromFile()));
	QObject::connect(calibrationWidgetpage->ui->pushButtonSave2DPoints, SIGNAL(clicked()), calibrationWidgetpage, SLOT(write2DpointsToFile()));


    //Volvux Widget connections
	// Data projection connection
	QObject::connect(this->volvuxWidgetpage->ui->widget, SIGNAL(dataFrameGenerated(unsigned char *)), this->projectorWidgetpage, SLOT(projectDataFrames(unsigned char *)));
    //Scene tab
	//Texture Object Parameters
    QObject::connect(volvuxWidgetpage->ui->doubleSpinBoxOffsetX,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxOffsetChanged(double)));
    QObject::connect(volvuxWidgetpage->ui->doubleSpinBoxOffsetY,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxOffsetChanged(double)));
    QObject::connect(volvuxWidgetpage->ui->doubleSpinBoxOffsetZ,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxOffsetChanged(double)));
	QObject::connect(volvuxWidgetpage->ui->doubleSpinBoxObjectSize, SIGNAL(valueChanged(double)), volvuxWidgetpage, SLOT(onDoubleSpinboxObjectSizeChanged(double)));
	//Surface filter
	QObject::connect(volvuxWidgetpage->ui->doubleSpinBoxSurfaceThickness, SIGNAL(valueChanged(double)), volvuxWidgetpage, SLOT(onDoubleSpinboxSurfaceThicknessChanged(double)));
	QObject::connect(volvuxWidgetpage->ui->doubleSpinBox0thOrderCoeff, SIGNAL(valueChanged(double)), volvuxWidgetpage, SLOT(onDoubleSpinboxSurfaceZeroOrderCoeffChanged(double)));
	QObject::connect(volvuxWidgetpage->ui->doubleSpinBox1stOrderCoeff, SIGNAL(valueChanged(double)), volvuxWidgetpage, SLOT(onDoubleSpinboxSurfaceFirstOrderCoeffChanged(double)));
	QObject::connect(volvuxWidgetpage->ui->doubleSpinBox2ndOrderCoeff, SIGNAL(valueChanged(double)), volvuxWidgetpage, SLOT(onDoubleSpinboxSurfaceSecondOrderCoeffChanged(double)));
	//Helicoid Position Parameters
    QObject::connect(volvuxWidgetpage->ui->doubleSpinboxHelicoidCxMm,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxHelicoidChanged(double)));
    QObject::connect(volvuxWidgetpage->ui->doubleSpinboxHelicoidCyMm,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxHelicoidChanged(double)));
    QObject::connect(volvuxWidgetpage->ui->doubleSpinboxHelicoidCzMm,SIGNAL(valueChanged(double)),volvuxWidgetpage,SLOT(onDoubleSpinboxHelicoidChanged(double)));
    
	//Stimulus tab
	//Job info
    QObject::connect(volvuxWidgetpage->ui->checkBoxUseOffscreenRendering, SIGNAL(stateChanged(int)), volvuxWidgetpage->ui->widget, SLOT(setOffscreenRendering(int)));
    QObject::connect(volvuxWidgetpage->ui->pushButtonStimulusRandomizeSpheres,SIGNAL(clicked()),volvuxWidgetpage,SLOT(onPushButtonRandomizeSpheresPressed()));
    QObject::connect(volvuxWidgetpage->ui->pushButtonGenerateFrames,SIGNAL(clicked()),volvuxWidgetpage,SLOT(onPushButtonGenerateFramesPressed()));

	//Projector Sequence tab
	QObject::connect(volvuxWidgetpage->ui->pushButtonProjectorStartProjection, SIGNAL(clicked()), volvuxWidgetpage, SLOT(onPushButtonStartProjectionPressed()));
	QObject::connect(volvuxWidgetpage->ui->pushButtonProjectorStopProjection, SIGNAL(clicked()), volvuxWidgetpage, SLOT(onPushButtonStopProjectionPressed()));

}

StackedWidget::~StackedWidget()
{
    delete ui;
}
/*
//Show current widget
void StackedWidget::showCurrentWidget(int curr_index){
    if (widgets.count() > 0)
    {
        foreach (QWidget * widget, widgets)
            widget->hide();
        widgets.at(curr_index)->show();
        updateGeometry();
    }
}
*/

void StackedWidget::keyPressEvent(QKeyEvent *event){
    int keypressed = event->key();
    //Handles esc button pression
    switch (keypressed)
    {
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
	switch (curIndex)
	{
	case CALIBRATION_PAGE_INDEX:
	{
		this->resize(1353, 876);
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
	}
	case MAINWINDOW_PAGE_INDEX:
	{
		QObject::disconnect(this->timer, SIGNAL(timeout()), calibrationWidgetpage->ui->volvuxCalibrationWidget, SLOT(transferFrame()));
		this->showMaximized();
		//Enable back button
		this->ui->pushButtonBack->setEnabled(true);
		//Show menu and status bar
		this->ui->menuBar->show();
		this->ui->statusBar->show();
		//Disable next button
		this->ui->pushButtonNext->setEnabled(false);
		break;
	}
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
        this->resize(450,590);
        //Hide menu and status bar
        this->ui->menuBar->hide();
        this->ui->statusBar->hide();
        //Disable back button
        this->ui->pushButtonBack->setEnabled(false);
        break;
    case CALIBRATION_PAGE_INDEX:
        this->resize(1353,876);
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

//Calibration SLOT
void StackedWidget::onActionCalibrationTriggered() {
    this->ui->stackedWidget->setCurrentIndex(CALIBRATION_PAGE_INDEX);
    this->ui->menuBar->hide();
    this->ui->pushButtonNext->setEnabled(true);
}

