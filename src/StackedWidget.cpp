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

    // Projector navigation buttons
    QObject::connect(ui->pushButtonNextProjector,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelProjector,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));

    // Motor navigation buttons
    QObject::connect(ui->pushButtonNextMotor,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonPreviousMotor,SIGNAL(clicked(bool)),this,SLOT(onPushButtonPreviousStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelMotor,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));

    // Calibration navigation buttons
    QObject::connect(ui->pushButtonNextCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonPreviousCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonPreviousStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelCalibration,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));

    //Projector control buttons
    QObject::connect(ui->pushButtonProjectorInitialize,SIGNAL(clicked(bool)),this,SLOT(onPushButtonProjectorInitializeClicked(bool)));
    QObject::connect(ui->pushButtonProjectorRelease,SIGNAL(clicked(bool)),this,SLOT(onPushButtonProjectorReleaseClicked(bool)));

    //Projector settings
    QObject::connect(ui->spinBoxProjectorMicrosecondsPerFrame,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorMicrosecondsPerFrameChanged(int)));
    QObject::connect(ui->spinBoxProjectorNSlices,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorNSlicesChanged(int)));
        //LED settings
    QObject::connect(ui->spinBoxProjectorLEDcurrent,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorLEDCurrentChanged(int)));
    QObject::connect(ui->doubleSpinBoxProjectorLEDpercentage,SIGNAL(valueChanged(double)),this,SLOT(onSpinboxProjectorLEDPercentageChanged(double)));

    //Motor control buttons
    QObject::connect(ui->pushButtonMotorStart,SIGNAL(clicked(bool)),this,SLOT(onPushButtonMotorStartClicked(bool)));
}

//Methods

StackedWidget::~StackedWidget()
{
    delete ui;
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

//SLOTS

//Navigation buttons
    //Next
void StackedWidget::onPushButtonNextStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    if (curIndex==2)
        ui->volvuxCalibrationWidget->resize(1024,768);
    this->setCurrentIndex(curIndex+1);
}

    //Previous
void StackedWidget::onPushButtonPreviousStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    this->setCurrentIndex(curIndex-1);
}

    //Cancel
void StackedWidget::onCancelPressed(bool value)
{
    QMessageBox::warning(this,"Leaving Volvux","You are now exiting...");
    QApplication::exit(0);
}

//Projector buttons
    //Initilize
void StackedWidget::onPushButtonProjectorInitializeClicked(bool value){
    //Enables other buttons
    ui->pushButtonProjectorRelease->setEnabled(true);
    ui->spinBoxProjectorNSlices->setEnabled(true);
    ui->spinBoxProjectorLEDcurrent->setEnabled(true);
    ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(true);
    ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(true);
    ui->pushButtonProjectorInitialize->setEnabled(false);

    //Initialize ALP projector
    #ifdef ALP_SUPPORT
    if (alp.m_bAlpInit)
        return;
    int nSlices = ui->spinBoxProjectorNSlices->value();
    //unsigned char *data = this->ui->volumetricGLWidget->allFrames.data();
    try
    {
        alp.init();
        alp.initLED();
        alp.setLED(ui->spinBoxProjectorLEDcurrent->value(),ui->doubleSpinBoxProjectorLEDpercentage->value());
        alp.inquire();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP initialization",QString(e.what()));
    }
    #endif

    //Enables next button
    ui->pushButtonNextProjector->setEnabled(true);
}

    //Release
void StackedWidget::onPushButtonProjectorReleaseClicked(bool value){
    #ifdef ALP_SUPPORT
    try
    {
        alp.cleanup();
        alp.m_AlpSeqId.clear();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector",QString(e.what()));
    }
    #endif
    //this->ui->listWidgetSequences->clear();
    ui->spinBoxProjectorNSlices->setEnabled(false);
    ui->spinBoxProjectorLEDcurrent->setEnabled(false);
    ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(false);
    ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(false);
    ui->pushButtonProjectorRelease->setEnabled(false);
    ui->pushButtonProjectorInitialize->setEnabled(true);
}

//Projector settings
    //us per frame
void StackedWidget::onSpinboxProjectorMicrosecondsPerFrameChanged(int value){
    double flickerRate = 1E6/((double)(value*ui->spinBoxProjectorNSlices->value()));
    this->ui->doubleSpinBoxMotorFlickerRate->setValue(flickerRate);
}

    //n slices
void StackedWidget::onSpinboxProjectorNSlicesChanged(int value){
    ui->spinBoxMotorNSlices->setValue(value);
    double flickerPersistenceMicroSec = ui->doubleSpinBoxMotorFlickerRate->value();//*1E-6;
    qDebug("%d FlickerPersistence - Flicker Rate",flickerPersistenceMicroSec);
    int usPerFrame = flickerPersistenceMicroSec/value;
    qDebug("%d usPerFrame",usPerFrame);
    ui->spinBoxProjectorMicrosecondsPerFrame->setValue(usPerFrame);
    double motorRate = (1E-6/((double)value*usPerFrame))*MOTOR_UNITS_TO_REV_MIN;
    qDebug("%d Motor speed",motorRate);
    ui->spinBoxMotorSpeed->setValue(motorRate);
}

    //LED current
void StackedWidget::onSpinboxProjectorLEDCurrentChanged(int current){
    #ifdef ALP_SUPPORT
    if (alp.m_bAlpInit)
    {
        if (!alp.m_bAlpLEDInit)
        {
            alp.initLED();
            alp.setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
        }
        else
            alp.setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
        }
    #endif
}

    //LED percentage
void StackedWidget::onSpinboxProjectorLEDPercentageChanged(double percentage){
    #ifdef ALP_SUPPORT
    if (alp.m_bAlpInit)
    {
        if (!alp.m_bAlpLEDInit)
        {
            alp.initLED();
            alp.setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
        }
        else
            alp.setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
    }
    #endif
}

//Motor buttons
    //Start
void StackedWidget::onPushButtonMotorStartClicked(bool value){
    ui->pushButtonMotorStop->setEnabled(true);
    #if defined (SMI_SUPPORT) && (WIN32)
        cerr << "[MainWindow] Starting motor" << endl;
        long Version = 0;
        Version = CommInterface->EngineVersion;
        if ( this->ui->spinBoxMotorSpeed->isEnabled() )
        {
            int speed = this->ui->spinBoxMotorSpeed->value();
            this->startRotation(speed);
        }
        else
        {
            QMessageBox::warning(this,"!!! WARNING !!!","This speed is not safe for the system");
        }
    #endif
    ui->pushButtonMotorStart->setEnabled(false);
}
    //Stop
void StackedWidget::onPushButtonMotorStopClicked(bool value){
    #if defined (SMI_SUPPORT) && (WIN32)
        cerr << "[MainWindow] Stopping motor" << endl;
        this->startRotation(0);
    #endif
}
//Motor settings
    //Flicker Rate
void StackedWidget::onSpinboxFlickerRateChanged(double flickerRate){
    // The persistence of the stimulus on the eye in microseconds
    double flickerPersistence_microSec = 1E6/flickerRate;
    double nSlices = ui->spinBoxProjectorNSlices->value();
    double microSecPerFrame = flickerPersistence_microSec/nSlices;
    if ( std::fmod(microSecPerFrame,1.0) == 0.0)
    {
        //cerr << "consistent frame per microsecond" << endl;
        this->ui->spinBoxProjectorMicrosecondsPerFrame->setValue((int)microSecPerFrame);
    }
    else
    {
        //cerr << "inconsistent frame per microsecond" << endl;
    }

    double motorRate = (1E6/(nSlices*std::floor(microSecPerFrame))) * MOTOR_UNITS_TO_REV_MIN;
    if ( motorRate > this->ui->spinBoxMotorSpeed->maximum() )
    {
        this->ui->spinBoxMotorSpeed->setValue((int)motorRate);
        this->ui->spinBoxMotorSpeed->setEnabled(false);
    }
    else
    {
        //if ( std::fmod(motorRate,1.0) == 0)
        if (true)
        {
            this->ui->spinBoxMotorSpeed->setEnabled(true);
            this->ui->spinBoxMotorSpeed->setValue((int)motorRate);
            //this->onPushButtonMotorStartClicked();
        }
        else
        {
            this->ui->spinBoxMotorSpeed->setEnabled(false);
        }
        //this->ui->spinBoxMotorRevMin->setValue(motorRate/8000);
    }
}

