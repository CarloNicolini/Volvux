#include "projectorpage.h"

ProjectorPage::ProjectorPage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle("Projector Initialization");
    //setAttribute(Qt::WA_DeleteOnClose,true);

    //Layout initialization
    projectorLayout = new QGridLayout(this);
    button_groupbox = new QGroupBox(this);
    spinbox_groupbox = new QGroupBox(this);
    verticalLayout = new QVBoxLayout(button_groupbox);
    formLayout = new QFormLayout(spinbox_groupbox);

    //Label initialization
    welcome = new QLabel("Welcome to Volvux!");
    projectorInstructions = new QLabel("First, initialize and setup the projector: ");
    ledCurrent_label = new QLabel("LED Current [mA]: ");
    ledPercentage_label = new QLabel("LED Percentage: ");
    microsecondsPerRound_label = new QLabel("us per round: ");
    nSlicesProjector_label = new QLabel("# Slices: ");
    projectorFrequency_label = new QLabel("Bit depth: ");
    projectorMicrosecPerFrame_label = new QLabel("us per frame: ");

    //Button initialization
    initilizeProjector = new QPushButton(button_groupbox);
    releaseProjector = new QPushButton(button_groupbox);
    uploadSequenceProjector = new QPushButton(button_groupbox);

    //Spinbox initialization
    ledCurrent = new QSpinBox();
    projectorBitDepth = new QSpinBox();
    microsecondsPerFrame = new QSpinBox();
    microsecondsPerRound = new QSpinBox();
    projectorNSlices = new QSpinBox();

    //Doublespinbox initialization
    projectorLEDPercentage = new QDoubleSpinBox();



    //Label properties settings
    QFont font;
    font.setPointSize(10);
    projectorInstructions->setFont(font);

    //Button properties settings

    //               Visualized name
    initilizeProjector->setText("Initialize Projector");
    releaseProjector -> setText("Release Projector");
    uploadSequenceProjector -> setText("Upload Sequence");

    //               Set default enabled buttons
    uploadSequenceProjector->setEnabled(false);
    releaseProjector->setEnabled(false);

    //               Set toolTip buttons
    releaseProjector ->setToolTip("To enable it, please initialize the projector");
    uploadSequenceProjector->setToolTip("To enable it, please initialize the projector");

    //               Enable button after a signal
    QObject::connect(this->initilizeProjector,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorInitializeClicked()));


    //Spinbox properties settings
    ledCurrent ->setEnabled(false);
    projectorBitDepth ->setEnabled(false);
    microsecondsPerFrame ->setEnabled(false);
    microsecondsPerRound ->setEnabled(false);
    projectorNSlices ->setEnabled(false);
    projectorLEDPercentage -> setEnabled(false);


    //Groupbox properties settings
    button_groupbox->setTitle("Projector controls");
    spinbox_groupbox->setTitle("Settings");


    //Vertical layout buttons
    verticalLayout -> addWidget(initilizeProjector);
    verticalLayout -> addWidget(releaseProjector);
    verticalLayout -> addWidget(uploadSequenceProjector);

    //Form layout
    formLayout -> setWidget(0,QFormLayout::LabelRole, ledCurrent_label);
    formLayout -> setWidget(0,QFormLayout::FieldRole, ledCurrent);
    formLayout -> setWidget(1,QFormLayout::LabelRole, ledPercentage_label);
    formLayout -> setWidget(1,QFormLayout::FieldRole, projectorLEDPercentage);
    formLayout -> setWidget(2,QFormLayout::LabelRole, nSlicesProjector_label);
    formLayout -> setWidget(2,QFormLayout::FieldRole, projectorNSlices);
    //Deprecated
    /*
    formLayout -> setWidget(3,QFormLayout::LabelRole, projectorFrequency_label);
    formLayout -> setWidget(3,QFormLayout::FieldRole, projectorBitDepth);
    */
    formLayout -> setWidget(3,QFormLayout::LabelRole, projectorMicrosecPerFrame_label);
    formLayout -> setWidget(3,QFormLayout::FieldRole, microsecondsPerFrame);
    //Deprecated
    /*
    formLayout -> setWidget(4,QFormLayout::LabelRole, microsecondsPerRound_label);
    formLayout -> setWidget(4,QFormLayout::FieldRole, microsecondsPerRound);
    */

    //GridLayout Headers
    projectorLayout -> addWidget(welcome,0,0);
    projectorLayout -> addWidget(projectorInstructions,1,0);
    QSpacerItem* horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    projectorLayout -> addItem(horizontalSpacer,0,1);
    projectorLayout -> addItem(horizontalSpacer,1,1);

    //GridLayout buttons
    projectorLayout -> addWidget(button_groupbox,3,0);

    //GridLayout spinbox
    //projectorLayout ->addLayout(formLayout,3,1); //uncomment if you don't want to group them in a groupbox
    projectorLayout->addWidget(spinbox_groupbox,3,1); //comment if you don't want to group them in a groupbox

    //Set Layout QWizardPage
    setLayout(projectorLayout);

    //QObject::connect(QWizard::button(QWizard::FinishButton),SIGNAL(clicked()),this,SLOT(quit()));

}

//                      SLOTS


void ProjectorPage::onPushButtonProjectorInitializeClicked() {
    //Enables other buttons
    this ->releaseProjector->setEnabled(true);
    this->uploadSequenceProjector ->setEnabled(true);
    //Enables spinboxes
    ledCurrent ->setEnabled(true);
    projectorBitDepth ->setEnabled(true);
    microsecondsPerFrame ->setEnabled(true);
    microsecondsPerRound ->setEnabled(true);
    projectorNSlices ->setEnabled(true);
    projectorLEDPercentage -> setEnabled(true);
}




