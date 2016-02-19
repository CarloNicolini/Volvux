#include <cmath>
#include <limits>

#include "ProjectorWidgetPage.h"
#include "ui_ProjectorWidgetPage.h"


ProjectorWidgetPage::ProjectorWidgetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectorWidgetPage)
{
    ui->setupUi(this);
    palp = new ALPProjector();
    #ifdef SMI_SUPPORT
    motor = new SmartMotor();
    #endif
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
    this->ui->spinBoxMotorSpeed->setValue((int)motorRate);
    if ( motorRate > this->ui->spinBoxMotorSpeed->maximum() )
    {
        this->ui->spinBoxMotorSpeed->setEnabled(false);
    }
    else
    {
        this->ui->spinBoxMotorSpeed->setEnabled(true);
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
    this->ui->spinBoxProjectorNSlices->setEnabled(false);
    this->ui->spinBoxProjectorLEDcurrent->setEnabled(false);
	this->ui->doubleSpinBoxProjectorLEDpercentage->setEnabled(false);
	this->ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(false);
	this->ui->pushButtonProjectorRelease->setEnabled(false);
	this->ui->pushButtonProjectorInitialize->setEnabled(true);

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
			palp->setLED(current, this->ui->doubleSpinBoxProjectorLEDpercentage->value());
        }
        else
			palp->setLED(current, this->ui->doubleSpinBoxProjectorLEDpercentage->value());
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
			palp->setLED(this->ui->spinBoxProjectorLEDcurrent->value(), static_cast<long int>(std::ceil(percentage)));
        }
        else
			palp->setLED(this->ui->spinBoxProjectorLEDcurrent->value(), static_cast<long int>(std::ceil(percentage)));
    }
}

/**
 * @brief ProjectorWidgetPage::onSpinboxProjectorNSlicesChanged
 * @param int
 */
//Spinbox NSlices SLOT
void ProjectorWidgetPage::onSpinboxProjectorNSlicesChanged(int nSlices){
    //Calculates the number of slices
	double flickerRateHz = this->ui->doubleSpinBoxMotorFlickerRate->value();
    double tFrameSec = 1.0/(nSlices*flickerRateHz);
    double tFrameMicroSeconds = 1E6*tFrameSec;
	this->ui->spinBoxProjectorMicrosecondsPerFrame->setValue(static_cast<int>(tFrameMicroSeconds));

    //The number must be an int
    if ( std::fabs(fmod(tFrameMicroSeconds,1.0)) <= std::numeric_limits<double>::epsilon() )
    {
		this->ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(true);
    }
    else
    {
		this->ui->spinBoxProjectorMicrosecondsPerFrame->setDisabled(true);
    }
    updateMotorRate(nSlices,tFrameMicroSeconds);
}

//Motor buttons
/**
* @brief VolvuxMainWindow::onPushButtonMotorInitializeClicked
*/
void ProjectorWidgetPage::onPushButtonMotorInitializeClicked()
{
	if (this->ui->pushButtonMotorInitialize->isEnabled())
	{
		#if defined (SMI_SUPPORT) && (WIN32)
		//Initilize motor
		motor->initialize();
		//Open port Com4
		motor->openPort();
		// Detect RS232
		motor->detect232();
		// Establish chain
		motor->addressChain();
		#endif
		//emit motorInitialized(true);
		this->ui->pushButtonMotorInitialize->setEnabled(false);
		this->ui->pushButtonMotorStart->setEnabled(true);
	}
	else
	{
		qDebug("already enabled");
	}
}

//Start motor SLOT
void ProjectorWidgetPage::onPushButtonMotorStartClicked()
{
	this->ui->pushButtonMotorStart->setEnabled(false);
	#if defined (SMI_SUPPORT) && (WIN32)
	motor->startMotor();
    if ( this->ui->spinBoxMotorSpeed->isEnabled() )
    {
        int speed = this->ui->spinBoxMotorSpeed->value();
        motor->startRotation(speed);
    }
    else
    {
		//XXX BETTER WARNING IN CASE SPEED IS TOO HIGH
        QMessageBox::warning(this,"!!! WARNING !!!","This speed is not safe for the system");
    }
	#endif
	this->ui->pushButtonMotorStop->setEnabled(true);
}

//Stop motor SLOT
void ProjectorWidgetPage::onPushButtonMotorStopClicked()
{
	this->ui->pushButtonMotorStart->setEnabled(true);
	#if defined (SMI_SUPPORT) && (WIN32)
		cerr << "[Smart Motor] Stopping motor" << endl;
		motor->startRotation(0);
	#endif
	this->ui->pushButtonMotorStop->setEnabled(false);
}

//Motor settings
//Flicker Rate SLOT
void ProjectorWidgetPage::onSpinboxFlickerRateChanged(double flickerRate)
{
	int nSlices = this->ui->spinBoxProjectorNSlices->value();
    double tFrameSeconds = 1.0/(nSlices*flickerRate);
    double tFrameMicroSeconds = tFrameSeconds*1E6;

	this->ui->spinBoxProjectorMicrosecondsPerFrame->setValue(static_cast<int>(tFrameMicroSeconds));
    // Checks the remainder
    if ( std::fabs(fmod(tFrameMicroSeconds,1.0)) <= std::numeric_limits<double>::epsilon() )
    {
		this->ui->spinBoxProjectorMicrosecondsPerFrame->setEnabled(true);
    }
    else
    {
		this->ui->spinBoxProjectorMicrosecondsPerFrame->setDisabled(true);
    }
    updateMotorRate(nSlices,tFrameMicroSeconds);
}

/**
 * @brief ProjectorWidgetPage::projectDataFrames
 */
void ProjectorWidgetPage::projectDataFrames(unsigned char *data)
{
	palp->stop();
	if (data == NULL)
		return;
	int microsec = 125;
	if (this->ui->spinBoxProjectorMicrosecondsPerFrame->isEnabled())
		microsec = this->ui->spinBoxProjectorMicrosecondsPerFrame->value();
	else
		QMessageBox::warning(this, "Timing error","Non correct timing for projector, check flicker rate");
	palp->setPicturesTimeus(microsec);
	palp->cleanAllSequences();
    palp->loadSequence(PROJECTOR_SLICES_NUMBER,data);
    palp->start();
}

//Get motor current position
void ProjectorWidgetPage::getMotorAbsolutePosition(){
	long pos;
	pos = motor->getAbsolutePosition();
	this->ui->spinBoxPosition->setValue(static_cast<int>(pos));
	cerr << "Current position: " << pos << endl;
}

//Set motor position to 0
void ProjectorWidgetPage::setMotorDefaultPosition() {
	/*
	if (!(this->ui->pushButtonMotorStop->isEnabled())){
		this->ui->pushButtonMotorStop->setEnabled(true);
	}*/
	motor->goToDefaultPosition(this->ui->spinBoxMotorSpeed->value());
}