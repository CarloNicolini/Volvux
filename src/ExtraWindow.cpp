#include "ExtraWindow.h"
#include "ui_ExtraWindow.h"
#include "ui_ProjectorWidgetPage.h"


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ExtraWindow::ExtraWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ExtraWindow)
{
  ui->setupUi(this);
  grabbedWidget=0;
}

ExtraWindow::~ExtraWindow()
{
  delete ui;
}

void ExtraWindow::receiveWidget(ProjectorWidgetPage *projectorMotorSettings){
  if(grabbedWidget != 0)
      qWarning() << "You might have lost a widget just now.";

  grabbedWidget = projectorMotorSettings;
  QVBoxLayout *verticalLayoutProjPage = new QVBoxLayout;
  QLabel *title1 = new QLabel("Projector Settings");
  verticalLayoutProjPage->addWidget(title1);
  verticalLayoutProjPage->addLayout(projectorMotorSettings->ui->horizontalLayout_6);
  QLabel *title2 = new QLabel("Motor Settings");
  verticalLayoutProjPage->addWidget(title2);
  verticalLayoutProjPage->addLayout(projectorMotorSettings->ui->horizontalLayout_4);
}

void ExtraWindow::receiveWidget(VolvuxWidget *helicoidWidget) {
	grabbedWidget = helicoidWidget;
	helicoidWidget->setMinimumSize(1024, 768);
	helicoidWidget->setMaximumSize(1024, 768);
	QHBoxLayout *horizontalLayoutHelicoid = new QHBoxLayout;
	horizontalLayoutHelicoid->addWidget(helicoidWidget);
}




