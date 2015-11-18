#include "ProjectorPageWidget.h"



//Constructor
ProjectorPageWidget::ProjectorPageWidget(QWidget *parent) :
    QWizardPage(parent)
{
    //WizardPage Title
    setTitle("Projector Initialization");


    //Layout initialization
    projectorLayout = new QGridLayout(this);
    button_groupbox = new QGroupBox(this);
    spinbox_groupbox = new QGroupBox(this);
    verticalLayout = new QVBoxLayout(button_groupbox);
    formLayout = new QFormLayout(spinbox_groupbox);

    //Label initialization
    /*Deprecated
    microsecondsPerRound_label = new QLabel("us per round: ");
    */
    welcome = new QLabel("Welcome to Volvux!");
    projectorInstructions = new QLabel("First, initialize and setup the projector: ");
    ledCurrent_label = new QLabel("LED Current [mA]: ");
    ledPercentage_label = new QLabel("LED Percentage: ");
    nSlicesProjector_label = new QLabel("# Slices: ");
    projectorFrequency_label = new QLabel("Bit depth: ");
    projectorMicrosecPerFrame_label = new QLabel("us per frame: ");

    //Button initialization
    initilizeProjector = new QPushButton(button_groupbox);
    releaseProjector = new QPushButton(button_groupbox);

    //Spinbox initialization
    /*Deprecated
    microsecondsPerRound = new QSpinBox(); */
    ledCurrent = new QSpinBox();
    projectorBitDepth = new QSpinBox();
    microsecondsPerFrame = new QSpinBox();
    projectorNSlices = new QSpinBox();

    //Doublespinbox initialization
    projectorLEDPercentage = new QDoubleSpinBox();



    //Label properties settings
    QFont font;
    font.setPointSize(10);
    projectorInstructions->setFont(font);

    //Button properties settings
    //Visualized name
    initilizeProjector->setText("Initialize Projector");
    releaseProjector->setText("Release Projector");
    //Set default enabled buttons
    releaseProjector->setEnabled(false);
    //Set toolTip buttons
    releaseProjector->setToolTip("To enable it, please initialize the projector");


    //Spinbox properties settings
    /*Deprecated
    microsecondsPerRound ->setEnabled(false);*/

    //Projector LED current settings
    ledCurrent->setRange(0,10000);
    ledCurrent->setEnabled(false);
    //Bit Depth settings
    projectorBitDepth->setEnabled(false);
    //Microseconds per frame settings
    microsecondsPerFrame->setEnabled(false);
    //Number of slices settings
    projectorNSlices->setRange(0,1000);
    projectorNSlices->setValue(400);
    projectorNSlices->setEnabled(false);
    registerField("NSlices",projectorNSlices);
    //Projector LED percentage settings
    projectorLEDPercentage->setEnabled(false);


    //Groupbox properties settings
    button_groupbox->setTitle("Projector controls");
    spinbox_groupbox->setTitle("Settings");



    //Vertical layout buttons
    microsecondsPerRound_label =  verticalLayout->addWidget(initilizeProjector);
    verticalLayout->addWidget(releaseProjector);

    //Form layout
    /*Deprecated
    formLayout->setWidget(3,QFormLayout::LabelRole, projectorFrequency_label);
    formLayout->setWidget(3,QFormLayout::FieldRole, projectorBitDepth);
    formLayout->setWidget(4,QFormLayout::LabelRole, microsecondsPerRound_label);
    formLayout->setWidget(4,QFormLayout::FieldRole, microsecondsPerRound);
    */
    formLayout->setWidget(0,QFormLayout::LabelRole, ledCurrent_label);
    formLayout->setWidget(0,QFormLayout::FieldRole, ledCurrent);
    formLayout->setWidget(1,QFormLayout::LabelRole, ledPercentage_label);
    formLayout->setWidget(1,QFormLayout::FieldRole, projectorLEDPercentage);
    formLayout->setWidget(2,QFormLayout::LabelRole, nSlicesProjector_label);
    formLayout->setWidget(2,QFormLayout::FieldRole, projectorNSlices);
    formLayout->setWidget(3,QFormLayout::LabelRole, projectorMicrosecPerFrame_label);
    formLayout->setWidget(3,QFormLayout::FieldRole, microsecondsPerFrame);

    //GridLayout Headers
    projectorLayout->addWidget(welcome,0,0);
    projectorLayout->addWidget(projectorInstructions,1,0);
    QSpacerItem* horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    projectorLayout->addItem(horizontalSpacer,0,1);
    projectorLayout->addItem(horizontalSpacer,1,1);

    //GridLayout buttons
    projectorLayout->addWidget(button_groupbox,3,0);

    //GridLayout spinbox
    //projectorLayout->addLayout(formLayout,3,1); //uncomment if you don't want to group them in a groupbox
    projectorLayout->addWidget(spinbox_groupbox,3,1); //comment if you don't want to group them in a groupbox


    //               Enable button after a signal
    QObject::connect(this->initilizeProjector,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorInitializeClicked()));
    QObject::connect(this->releaseProjector,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorReleaseClicked()));
    QObject::connect(this->projectorNSlices,SIGNAL(valueChanged(int)),this,SLOT(onSpinboxProjectorNSlicesChanged(int)));
    //QObject::connect(this->ui->spinBoxProjectorLEDcurrent,SIGNAL(valueChanged(int)),this,SLOT(onspinBoxProjectorLEDcurrentChanged(int)));
    //QObject::connect(this->doubleSpinBoxProjectorLEDpercentage,SIGNAL(valueChanged(double)),this,SLOT(onSpinBoxProjectorLEDpercentageChanged(double)));

    //Set Layout QWizardPage
    setLayout(projectorLayout);

}

//                      SLOTS


void ProjectorPageWidget::onPushButtonProjectorInitializeClicked() {
    //Enables other buttons
    this->releaseProjector->setEnabled(true);
    //Enables spinboxes
    /*Deprecated
    microsecondsPerRound->setEnabled(true);
    */
    ledCurrent->setEnabled(true);
    projectorBitDepth->setEnabled(true);
    microsecondsPerFrame->setEnabled(true);
    projectorNSlices->setEnabled(true);
    projectorLEDPercentage->setEnabled(true);

    //Initialize APL
    #ifdef ALP_SUPPORT
        if (alp.m_bAlpInit)
            return;
        int nSlices = projectorNSlices->value();
        //unsigned char *data = this->ui->volumetricGLWidget->allFrames.data();
        try
        {
            alp.init();
            alp.initLED();
            alp.setLED(ledCurrent->value(),projectorLEDPercentage->value());
            alp.inquire();
        }
        catch (std::exception &e)
        {
            QMessageBox::warning(this,"Error in ALP initialization",QString(e.what()));
        }
    #endif
}


void ProjectorPageWidget::onPushButtonProjectorReleaseClicked() {
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
    ledCurrent->setEnabled(false);
    projectorLEDPercentage->setEnabled(false);
    microsecondsPerFrame->setEnabled(false);
    projectorNSlices->setEnabled(false);
}

void ProjectorPageWidget::onSpinboxProjectorNSlicesChanged(int){
    //To implement AFTER creating SMIPage
    //Do a WizardPage Field so that the value of
    //Nslices is passed to the next page
    /*
    //this->ui->volumetricGLWidget->setSlicesNumber(value);
    double flickerPersistenceMicroSec = this->ui->doubleSpinBoxFlickerRateHz->value()*1E-6;
    double motorUnitsToRevMin = this->ui->comboBoxMotorUnitsToRevMin->itemData(
    this->ui->comboBoxMotorUnitsToRevMin->currentIndex()).toInt();
    int usPerFrame = flickerPersistenceMicroSec/value;
    this->ui->spinBoxProjectorMicrosecondsPerFrame->setValue(usPerFrame);
    double motorRate = (1E6/((double)value*usPerFrame))*motorUnitsToRevMin;
    this->ui->spinBoxMotorSpeed->setValue(motorRate);
    this->ui->spinBoxProjectorMicrosecondsPerRound->setValue(value*ui->spinBoxProjectorMicrosecondsPerFrame->value());
    */

    QMessageBox::information(this,"WorkInProgress","Da implementare: il valore va passato alla pagina successiva (serve ad aggiornare altri campi)");

}

void ProjectorPageWidget::onspinBoxProjectorLEDcurrentChanged(int) {
    #ifdef ALP_SUPPORT
        if (alp.m_bAlpInit)
        {
            if (!alp.m_bAlpLEDInit)
            {
                alp.initLED();
                alp.setLED(current,projectorLEDPercentage->value());
            }
            else
                alp.setLED(current,ProjectorLEDpercentage->value());
        }
    #endif
}

void ProjectorPageWidget::onSpinBoxProjectorLEDpercentageChanged(double){

    #ifdef ALP_SUPPORT
        if (alp.m_bAlpInit)
        {
            if (!alp.m_bAlpLEDInit)
            {
                alp.initLED();
                alp.setLED(ledCurrent->value(),static_cast<long int>(std::ceil(percentage)));
            }
            else
                alp.setLED(ledCurrent->value(),static_cast<long int>(std::ceil(percentage)));
        }
    #endif

}





