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

VolvuxWidgetPage::onDoubleSpinboxOffsetXChanged(double)
{

}


VolvuxWidgetPage::onDoubleSpinboxOffsetYChanged(double)
{

}

VolvuxWidgetPage::onDoubleSpinboxOffsetZChanged(double)
{

}
