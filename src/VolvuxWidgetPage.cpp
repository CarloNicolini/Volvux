#include "VolvuxWidgetPage.h"
#include "ui_VolvuxWidgetPage.h"

VolvuxWidgetPage::VolvuxWidgetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolvuxWidgetPage)
{
    ui->setupUi(this);
}

VolvuxWidgetPage::~VolvuxWidgetPage()
{
    delete ui;
}

//SLOTS
//Scene tab
//Offset SLOT
void VolvuxWidgetPage::onDoubleSpinboxOffsetChanged(double)
{
    this->ui->widget->setObjectOffset(this->ui->doubleSpinBoxOffsetX->value(),this->ui->doubleSpinBoxOffsetY->value(),this->ui->doubleSpinBoxOffsetZ->value());
    this->ui->widget->update();
}

//Helicoid SLOT
void VolvuxWidgetPage::onDoubleSpinboxHelicoidChanged(double)
{
    this->ui-> widget->setHelicoidOffset(this->ui->doubleSpinboxHelicoidCxMm->value(),this->ui->doubleSpinboxHelicoidCyMm->value(),this->ui->doubleSpinboxHelicoidCzMm->value());
    this->ui->widget->update();
}

//Object size SLOT
void VolvuxWidgetPage::onDoubleSpinboxObjectSizeChanged(double)
{
    this->ui->widget->setObjectScale(this->ui->doubleSpinBoxObjectSize->value());
	
}

//Stimulus tab
//Randomize sphere SLOT
void VolvuxWidgetPage::onPushButtonRandomizeSpheresPressed(){
    bool useRandomDots = this->ui->randomDotsCheckBox->isChecked();
    this->ui->widget->randomizeSpheres(useRandomDots,this->ui->spinBoxStimulusNSpheres->value(),this->ui->spinBoxStimulusSpheresRadiusMin->value(),this->ui->spinBoxStimulusSpheresRadiusMax->value());
}

//Generate frames SLOT
void VolvuxWidgetPage::onPushButtonGenerateFramesPressed()
{
    if (this->ui->checkBoxUseOffscreenRendering->isChecked())
    {
        QObject::connect(this->ui->widget,SIGNAL(memoryAllocatedMegaBytes(int)),this->ui->spinBoxMemoryAllocated,SLOT(setValue(int)));
    }

	QString message = "Generating " + QString::number(this->ui->widget->slicesNumber) + " frames...";
    emit writeOnStatusBar(message,0);

    this->ui->widget->updateGL();
	QObject::connect(this->ui->widget, SIGNAL(memoryAllocatedMegaBytes(int)), this->ui->spinBoxMemoryAllocated, SLOT(setValue(int)));
    this->ui->widget->generateFrames();

    message = "Frames generation done";
    emit writeOnStatusBar(message,2000);
}


void VolvuxWidgetPage::onPushButtonStartProjectionPressed()
{
	if (!this->ui->widget->allFrames.empty())
	{
		auto *curdata = this->ui->widget->allFrames.data();
		emit this->ui->widget->dataFrameGenerated(curdata);
	}
}

void VolvuxWidgetPage::onPushButtonStopProjectionPressed()
{
	emit this->ui->widget->dataFrameGenerated(NULL);
}

void VolvuxWidgetPage::onDoubleSpinboxSurfaceSecondOrderCoeffChanged(double val)
{
	this->ui->widget->meshStruct.curvature = val;
}

void VolvuxWidgetPage::onDoubleSpinboxSurfaceFirstOrderCoeffChanged(double val)
{
	this->ui->widget->meshStruct.firstOrderCoeff = val;
}

void VolvuxWidgetPage::onDoubleSpinboxSurfaceZeroOrderCoeffChanged(double val)
{
	this->ui->widget->meshStruct.zeroOrderCoeff = val;
}

void VolvuxWidgetPage::onDoubleSpinboxSurfaceThicknessChanged(double val)
{
	this->ui->widget->meshStruct.thickness = val;
}