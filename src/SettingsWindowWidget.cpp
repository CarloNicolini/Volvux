#include "SettingsWindowWidget.h"
#include "ui_SettingsWindowWidget.h"

SettingsWindowWidget::SettingsWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindowWidget)
{
    ui->setupUi(this);
    grabbedWidget = 0;
}

SettingsWindowWidget::~SettingsWindowWidget()
{
    delete ui;
}

void SettingsWindowWidget::receiveWidget(QWidget *widget)
{
    if(grabbedWidget != 0)
        //qWarning() << "You might have lost a widget just now.";

    grabbedWidget = widget;
    this->ui->SettingsStackedWidget->addWidget(widget);
}
