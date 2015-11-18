#ifndef ProjectorPage_H
#define ProjectorPage_H

#include <QWizardPage>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSpacerItem>




class ProjectorPage : public QWizardPage
{
    Q_OBJECT

public:
    ProjectorPage(QWidget *parent=0);

private:
    //Buttons
    QPushButton* initilizeProjector;
    QPushButton* releaseProjector;
    QPushButton* uploadSequenceProjector;

    //Labels
    QLabel* ledCurrent_label;
    QLabel* ledPercentage_label;
    QLabel* microsecondsPerRound_label;
    QLabel* nSlicesProjector_label;
    QLabel* projectorFrequency_label;
    QLabel* projectorMicrosecPerFrame_label;
    QLabel* welcome;
    QLabel* projectorInstructions;

    //Spinbox
    QSpinBox* projectorBitDepth;
    QSpinBox* ledCurrent;
    QSpinBox* microsecondsPerFrame;
    QSpinBox* microsecondsPerRound;
    QSpinBox* projectorNSlices;

    //Double spinbox
    QDoubleSpinBox* projectorLEDPercentage;

    //GridLayout
    QGridLayout* projectorLayout;

    //VerticalLayout
    QVBoxLayout* verticalLayout;

    //FormLayout
    QFormLayout* formLayout;

    //GroupBox
    QGroupBox* button_groupbox;
    QGroupBox* spinbox_groupbox;

private slots:
    void onPushButtonProjectorInitializeClicked();


};

#endif // ProjectorPage_H
