#include "ProjectorWidgetPage.h"
#include "ui_ProjectorWidgetPage.h"
#include "cmath"
#include "limits"

ProjectorWidgetPage::ProjectorWidgetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectorWidgetPage)
{
    ui->setupUi(this);
    palp = new ALPProjector();
}

ProjectorWidgetPage::~ProjectorWidgetPage()
{
    delete ui;
}

//Get ALP pointer
ALPProjector *ProjectorWidgetPage::getALP(){
    return this->palp;
}

//Update Motor Rate
void ProjectorWidgetPage::updateMotorRate(int nSlices, double tFrameMicroSeconds){
    double motorRate = (1E6/(nSlices*tFrameMicroSeconds)) * MOTOR_UNITS_TO_REV_MIN;
    ui->spinBoxMotorSpeed->setValue((int)motorRate);
    if ( motorRate > ui->spinBoxMotorSpeed->maximum() )
    {
        ui->spinBoxMotorSpeed->setEnabled(false);
    }
    else
    {
        ui->spinBoxMotorSpeed->setEnabled(true);
    }
}

//SLOT
/**
 * @brief ProjectorWidgetPage::onPushButtonProjectorInitializeClicked
 * @param
 */
//Initialize projector SLOT
void ProjectorWidgetPage::onPushButtonProjectorInitializeClicked()
{
    //Enables other buttons
    this->ui->pushButtonProjectorRelease->setEnabled(true);
    this->ui->spinBoxProjectorNSlices->setEnabled(true);
    this->ui->spinBoxProjectorLEDcurrent->setEnabled(true);
    this->ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(true);
    this->ui->pushButtonProjectorInitialize->setEnabled(false);

    //Initialize ALP Projector
    try
    {
        palp->init();
        palp->initLED();
        palp->setLED(this->ui->spinBoxProjectorLEDcurrent->value(),this->ui->doubleSpinBoxProjectorLEDpercentage->value());
        palp->inquire();
    }
    catch (std::exception &e) {
        QMessageBox::warning(this,"Error in ALP initialization", QString(e.what()));
    }
    //Send signal to MainWindow to enable next button
    emit enableNextButton(true);

}

/**
 * @brief ProjectorWidgetPage::onPushButtonProjectorReleaseClicked
 * @param
 */
//Release projector SLOT
void ProjectorWidgetPage::onpushButtonProjectorReleaseClicked()
{
    //Release ALP projector
    try
    {
        palp->cleanup();
        palp->m_AlpSeqId.clear();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector",QString(e.what()));
    }
    //Enable and disable buttons and spinboxes
    ui->spinBoxProjectorNSlices->setEnabled(false);
    ui->spinBoxProjectorLEDcurrent->setEnabled(false);
    ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(false);
    ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(false);
    ui->pushButtonProjectorRelease->setEnabled(false);
    ui->pushButtonProjectorInitialize->setEnabled(true);

    //Send signal to MainWindow to disable next button
    emit enableNextButton(false);
}

/**
 * @brief ProjectorWidgetPage::onSpinboxProjectorLEDCurrentChanged
 * @param int
 */
//Spinbox LED Current SLOT
void ProjectorWidgetPage::onSpinboxProjectorLEDCurrentChanged(int current){
    //Initialize ALP LED
    if (palp->m_bAlpInit)
    {
        if (!palp->m_bAlpLEDInit)
        {
            palp->initLED();
            palp->setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
        }
        else
           palp->setLED(current,ui->doubleSpinBoxProjectorLEDpercentage->value());
    }
}

/**
 * @brief ProjectorWidgetPage::onSpinboxProjectorLEDPercentageChanged
 * @param double
 */
//Spinbox LED Percentage SLOT
void ProjectorWidgetPage::onSpinboxProjectorLEDPercentageChanged(double percentage) {
    if (palp->m_bAlpInit)
    {
        if (!palp->m_bAlpLEDInit)
        {
            palp->initLED();
            palp->setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
        }
        else
            palp->setLED(ui->spinBoxProjectorLEDcurrent->value(),static_cast<long int>(std::ceil(percentage)));
    }
}

/**
 * @brief ProjectorWidgetPage::onSpinboxProjectorNSlicesChanged
 * @param int
 */
//Spinbox NSlices SLOT
void ProjectorWidgetPage::onSpinboxProjectorNSlicesChanged(int nSlices){
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
    updateMotorRate(nSlices,tFrameMicroSeconds);
}

//Motor buttons
//Start motor SLOT
void ProjectorWidgetPage::onPushButtonMotorStartClicked(bool value)
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

//Stop motor SLOT
void ProjectorWidgetPage::onPushButtonMotorStopClicked(bool value)
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
//Flicker Rate SLOT
void ProjectorWidgetPage::onSpinboxFlickerRateChanged(double flickerRate)
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
    updateMotorRate(nSlices,tFrameMicroSeconds);
}



/**
 * @brief VolvuxMainWindow::onPushButtonMotorInitializeClicked
 */
void ProjectorWidgetPage::onPushButtonMotorInitializeClicked()
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
        //emit motorInitialized(true);
        ui->pushButtonMotorInitialize->setEnabled(false);
    }
    else
    {
        qDebug("already enabled");
    }
}

/**
 * @brief ProjectorWidgetPage::projectDataFrames
 */
void ProjectorWidgetPage::projectDataFrames(unsigned char *data)
{
    palp->cleanAllSequences();
    palp->loadSequence(PROJECTOR_SLICES_NUMBER,data);
    palp->start();
}
