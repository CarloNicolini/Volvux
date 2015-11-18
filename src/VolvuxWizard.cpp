#include "VolvuxWizard.h"
#include "ProjectorPageWidget.h"
#include "SMIPageWidget.h"
#include "ExpPageWidget.h"
#include <QApplication>

VolvuxWizard::VolvuxWizard(QWidget *parent) :
    QWizard(parent)
{
    setWindowTitle("Volvux Wizard");
    addPage(new ProjectorPageWidget);
    addPage(new SMIPageWidget);
    //addPage(new ExpPage);

    QList<QWizard::WizardButton> buttonLayout;
    buttonLayout.append(QWizard::BackButton);
    buttonLayout.append(QWizard::NextButton);
    buttonLayout.append(QWizard::FinishButton);
    //buttonlayout<<QWizard::BackButton <<QWizard::NextButton<<QWizard::CancelButton;
    //qDebug("%d",buttonLayout.isEmpty());
    setButtonLayout(buttonLayout);


    //this->button(QWizard::FinishButton)->connect()
    //QObject::connect(CancelButton,SIGNAL(clicked()),qApp,SLOT(quit()));

}

