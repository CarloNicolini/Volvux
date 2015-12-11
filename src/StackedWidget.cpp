#include "QMessageBox"
#include "StackedWidget.h"
#include "VolvuxCalibrationWidget.h"
#include "ui_StackedWidget.h"
#include "StackedWidgetHelper.h"
#include "CalibrationHelper.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWidget)
{
    //Setup ui and Helpers
    helper = new StackedWidgetHelper(this);
    ui->setupUi(this);
    //this->installEventFilter(this);
    timer = new QTimer(this);
    timer->start();
    this->setCurrentIndex(0);

    calibHelper = new CalibrationHelper(this);
    ui->pageMainWindow->setStackedWidgetHelper(helper);
    ui->pageMainWindow->setCalibrationHelper(this->calibHelper);
    ui->volvuxCalibrationWidget->setALP(helper->getALP());

    // Projector navigation buttons
    QObject::connect(ui->pushButtonNextProjector,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelProjector,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));

    // Calibration navigation buttons
    QObject::connect(ui->pushButtonNextCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonNextStackedWidget(bool)));
    QObject::connect(ui->pushButtonPreviousCalibration,SIGNAL(clicked(bool)),this,SLOT(onPushButtonPreviousStackedWidget(bool)));
    QObject::connect(ui->pushButtonCancelCalibration,SIGNAL(clicked(bool)),this,SLOT(onCancelPressed(bool)));
    QObject::connect(ui->volvuxCalibrationWidget,SIGNAL(lastPointPressed(QPoint)),this->calibHelper,SLOT(append2DPoint(QPoint)));
    QObject::connect(ui->volvuxCalibrationWidget,SIGNAL(pointRemoved(QPoint)),this->calibHelper,SLOT(remove2DPoint(QPoint)));

    //Projector control buttons
    QObject::connect(ui->pushButtonProjectorInitialize,SIGNAL(clicked(bool)),this,SLOT(onPushButtonProjectorInitializeClicked(bool)));
    QObject::connect(ui->pushButtonProjectorRelease,SIGNAL(clicked(bool)),this,SLOT(onPushButtonProjectorReleaseClicked(bool)));

    //Projector settings
    QObject::connect(ui->spinBoxProjectorNSlices,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorNSlicesChanged(int)));
    //LED settings
    QObject::connect(ui->spinBoxProjectorLEDcurrent,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorLEDCurrentChanged(int)));
    QObject::connect(ui->doubleSpinBoxProjectorLEDpercentage,SIGNAL(valueChanged(double)),this,SLOT(onSpinboxProjectorLEDPercentageChanged(double)));

    //Motor control buttons
    QObject::connect(ui->pushButtonMotorInitialize,SIGNAL(clicked(bool)),this->ui->spinBoxMotorSpeed,SLOT(setEnabled(bool)));
    QObject::connect(ui->pushButtonMotorInitialize,SIGNAL(clicked(bool)),this,SLOT(onPushButtonMotorInitializeClicked()));
    QObject::connect(this,SIGNAL(motorInitialized(bool)),this->ui->pushButtonMotorStart,SLOT(setEnabled(bool)));
    QObject::connect(ui->pushButtonMotorStart,SIGNAL(clicked(bool)),this,SLOT(onPushButtonMotorStartClicked(bool)));
    QObject::connect(this->ui->pushButtonMotorStop,SIGNAL(clicked(bool)),this,SLOT(onPushButtonMotorStopClicked(bool)));
    QObject::connect(ui->doubleSpinBoxMotorFlickerRate,SIGNAL(valueChanged(double)),this,SLOT(onSpinboxFlickerRateChanged(double)));

    ui->spinBoxProjectorMicrosecondsPerFrame->setReadOnly(true);

    // Call the slots as methods to set default parameters as defined in the corresponding .ui
    onSpinboxFlickerRateChanged(ui->doubleSpinBoxMotorFlickerRate->value());
    onSpinboxProjectorNSlicesChanged(ui->spinBoxProjectorNSlices->value());

    // Calibration helper slots
    QObject::connect(this->calibHelper,SIGNAL(calibrationEmitted(CameraDirectLinearTransformation &)),ui->pageMainWindow,SLOT(onCalibrationEmitted(CameraDirectLinearTransformation &)));

    helper->write3DPoints(calibHelper);

    // Set strong focus on volvuxcalibrationwidget
    this->ui->volvuxCalibrationWidget->setFocusPolicy(Qt::StrongFocus);


    QObject::connect(ui->volvuxCalibrationWidget,SIGNAL(points2Dupdated(QVector<QPoint>)),this->helper,SLOT(update2DPoints(QVector<QPoint>)));
}

//Methods

StackedWidget::~StackedWidget()
{
    delete helper;
    delete ui;
}


//SLOTS

//Navigation buttons
//Next
void StackedWidget::onPushButtonNextStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    curIndex = curIndex + 1;
    this->setCurrentIndex(curIndex);
    if (curIndex == CALIBRATION_INDEX_PAGE)
    {
        //ui->volvuxCalibrationWidget->resize(1024, 768);
        //To send frame to the projector only after widget has been correctly initialized via initializeGL
        QObject::connect(this->timer, SIGNAL(timeout()), ui->volvuxCalibrationWidget, SLOT(transferFrame()));
    }
}

//Previous
void StackedWidget::onPushButtonPreviousStackedWidget(bool value)
{
    int curIndex = this->currentIndex();
    curIndex = curIndex - 1;
    this->setCurrentIndex(curIndex);
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
    ui->pushButtonProjectorInitialize->setEnabled(false);

    //Initialize ALP projector

    //if (helper->getALP()->m_bAlpInit)
    //return;

    int nSlices = ui->spinBoxProjectorNSlices->value();
    //unsigned char *data = this->ui->volumetricGLWidget->allFrames.data();
    try
    {
        helper->getALP()->init();
        helper->getALP()->initLED();
        helper->getALP()->setLED(ui->spinBoxProjectorLEDcurrent->value(),ui->doubleSpinBoxProjectorLEDpercentage->value());
        helper->getALP()->inquire();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP initialization",QString(e.what()));
    }

    //Enables next button
    ui->pushButtonNextProjector->setEnabled(true);
}

//Release
void StackedWidget::onPushButtonProjectorReleaseClicked(bool value){
    //Release ALP projector
    try
    {
        helper->getALP()->cleanup();
        helper->getALP()->m_AlpSeqId.clear();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector",QString(e.what()));
    }

    //this->ui->listWidgetSequences->clear();
    //Enable and disable buttons and spinbox
    ui->spinBoxProjectorNSlices->setEnabled(false);
    ui->spinBoxProjectorLEDcurrent->setEnabled(false);
    ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(false);
    ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(false);
    ui->pushButtonProjectorRelease->setEnabled(false);
    ui->pushButtonProjectorInitialize->setEnabled(true);
    ui->pushButtonNextProjector->setEnabled(false);
}


/**
 * @brief StackedWidget::onSpinboxProjectorNSlicesChanged
 * @param nSlices
 */
void StackedWidget::onSpinboxProjectorNSlicesChanged(int nSlices)
{
    //Calculates the number of slices
    double flickerRateHz = ui->doubleSpinBoxMotorFlickerRate->value();
    double tFrameSec = 1.0/(nSlices*flickerRateHz);
    double tFrameMicroSeconds = 1E6*tFrameSec;
    ui->spinBoxProjectorMicrosecondsPerFrame->setValue( static_cast<int>(tFrameMicroSeconds) );

    //The number must be an int
    if ( std::fabs(fmod(tFrameMicroSeconds,1.0)) <= std::numeric_limits<double>::epsilon() )
    {
        ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(true);
    }
    else
    {
        ui->spinBoxProjectorMicrosecondsPerFrame->setDisabled(true);
    }
    this->helper->updateMotorRate(nSlices,tFrameMicroSeconds);
}

//LED current
void StackedWidget::onSpinboxProjectorLEDCurrentChanged(int current)
{
    //Initialize ALP LED
    if (helper->getALP()->m_bAlpInit)
    {
        if (!helper->getALP()->m_bAlpLEDInit)
        {
            helper->getALP()->initLED();
            helper->getALP()->setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
        }
        else
            helper->getALP()->setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
    }

}

//LED percentage
void StackedWidget::onSpinboxProjectorLEDPercentageChanged(double percentage)
{
    if (helper->getALP()->m_bAlpInit)
    {
        if (!helper->getALP()->m_bAlpLEDInit)
        {
            helper->getALP()->initLED();
            helper->getALP()->setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
        }
        else
            helper->getALP()->setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
    }
}

//Motor buttons
//Start
void StackedWidget::onPushButtonMotorStartClicked(bool value)
{
    ui->pushButtonMotorStart->setEnabled(false);
    /*
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
    */
    ui->pushButtonMotorStop->setEnabled(true);
}

//Stop
void StackedWidget::onPushButtonMotorStopClicked(bool value)
{
    ui->pushButtonMotorStart->setEnabled(true);
    /*
#if defined (SMI_SUPPORT) && (WIN32)
    cerr << "[MainWindow] Stopping motor" << endl;
    this->startRotation(0);
#endif
    */
    ui->pushButtonMotorStop->setEnabled(false);
}

//Motor settings
//Flicker Rate
void StackedWidget::onSpinboxFlickerRateChanged(double flickerRate)
{
    int nSlices = ui->spinBoxProjectorNSlices->value();
    double tFrameSeconds = 1.0/(nSlices*flickerRate);
    double tFrameMicroSeconds = tFrameSeconds*1E6;

    ui->spinBoxProjectorMicrosecondsPerFrame->setValue( static_cast<int>(tFrameMicroSeconds) );
    // Checks the remainder
    if ( std::fabs(fmod(tFrameMicroSeconds,1.0)) <= std::numeric_limits<double>::epsilon() )
    {
        ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(true);
    }
    else
    {
        ui->spinBoxProjectorMicrosecondsPerFrame->setDisabled(true);
    }
    this->helper->updateMotorRate(nSlices,tFrameMicroSeconds);
}



/**
 * @brief VolvuxMainWindow::onPushButtonMotorInitializeClicked
 */
void StackedWidget::onPushButtonMotorInitializeClicked()
{
    if (ui->pushButtonMotorInitialize->isEnabled())
    {

        //#if defined (SMI_SUPPORT) && (WIN32)
        //CoInitialize(NULL);
        /*
    if(!AfxOleInit())
    {
        throw std::runtime_error("OLE initialization failed.  Make sure that the OLE libraries are the correct version.");
    }
    AfxEnableControlContainer();*/
        /*
        HRESULT hr = CommInterface.CreateInstance(__uuidof(INTEGMOTORINTERFACELib::SMIHost));
        if(FAILED(hr))
        {
            QMessageBox::warning(this,"Error","Cannot create an instance of \"SMIHost\" class!");
            return;
        }

        cerr << "[MainWindow] Starting motor" << endl;
        long portResult=-1;
        try
        {
            CommInterface->BaudRate = 9600;
            portResult = CommInterface->OpenPort("Com4");
        }
        catch (_com_error e)
        {
            throw std::exception("Error opening COM4 port");
        }
        // Detect RS232
        cerr << "[Smart Motor] Detecting RS232...";
        UINT x= 10;//GetDlgItemInt(IDC_MAXADDRESS);
        long MaxAddress=10;
        long flags=0;
        long result = CommInterface->DetectRS232(MaxAddress,flags);
        switch(result)
        {
        case CER_SOMEADDRESSED:
            cerr << "Some Motors are not addressed!"<<" IntegMotorInterface Error!"<< endl;
            break;

        case CER_BIGADDRESS:
            cerr << "Some Motors have big addresses!" <<" IntegMotorInterface Error!" << endl;
            break;

        case CER_DUPLICATEADDR:
            cerr << "Some Motors have duplicate addresses!"<<" IntegMotorInterface Error!"<< endl;
            break;

        case CER_NOTADDRESSED:
            cerr << "Motors are not addressed!"<<" IntegMotorInterface Error!"<< endl;
            break;

        case CER_COMMERROR:
            cerr << "Communication Error!"<<" IntegMotorInterface Error!"<< endl;
            break;

        case CER_NOMOTOR:
            cerr << "No Motor Found!"<<" IntegMotorInterface Error!" << endl;
            break;
        default:
            cerr << CommInterface->NoOfMotors << endl;
            //cerr << CommInterface->DefaultMotor = long(1);//GetDlgItemInt(IDC_CURRENTMOTOR);
        }

        // Establish chain
        cerr << "[Smart Motor] Addressing motor chain...";
        try
        {
            // Establish chain
            CommInterface->AddressMotorChain();
            CommInterface->DefaultMotor = 1;
        }
        catch (_com_error e )
        {
            //AfxMessageBox(e.Description());
            throw std::runtime_error(BSTR2STR(e.Description()));
        }
        cerr << "DONE" << endl;
#endif
        */
        emit motorInitialized(true);
        ui->pushButtonMotorInitialize->setEnabled(false);
    }
    else
    {
        qDebug("already enabled");
    }
}

void StackedWidget::onPoint2DEmitted(const QPoint &point)
{
}

/*
bool StackedWidget::eventFilter(QObject * target, QEvent * event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (target == ui->volvuxCalibrationWidget && event->type() == QEvent::KeyPress)
    {
        //QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        keyPressEvent(keyEvent);
        qDebug() << "key " << keyEvent->key() << "from" << target;
        return true;
    }
    else {
        qDebug("Sono nell'else");
        qDebug() << "from" << target;
        return false;
    }
}
*/
