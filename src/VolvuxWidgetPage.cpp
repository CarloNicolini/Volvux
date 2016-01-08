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
//Offset SLOT
void VolvuxWidgetPage::onDoubleSpinboxOffsetChanged(double){
    this->ui->widget->setObjectOffset(this->ui->doubleSpinBoxOffsetX->value(),this->ui->doubleSpinBoxOffsetY->value(),this->ui->doubleSpinBoxOffsetZ->value());
    this->ui->widget->update();
}

//Helicoid SLOT
void VolvuxWidgetPage::onDoubleSpinboxHelicoidChanged(double){
    this->ui->widget->setHelicoidOffset(this->ui->doubleSpinboxHelicoidCxMm->value(),this->ui->doubleSpinboxHelicoidCyMm->value(),this->ui->doubleSpinboxHelicoidCzMm->value());
    this->ui->widget->update();
}

//Object size SLOT
void VolvuxWidgetPage::onDoubleSpinboxObjectSizeChanged(double){
    this->ui->widget->setObjectScale(this->ui->doubleSpinBoxObjectSize->value());
}

