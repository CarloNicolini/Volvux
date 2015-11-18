/********************************************************************************
** Form generated from reading UI file 'VolvuxMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLVUXMAINWINDOW_H
#define UI_VOLVUXMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "VolvuxWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VolvuxMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tabScene;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayoutHelicoidParameters;
    QLabel *labelOffsetX;
    QDoubleSpinBox *doubleSpinBoxOffsetX;
    QLabel *labelOffsetY;
    QDoubleSpinBox *doubleSpinBoxOffsetY;
    QLabel *labelOffsetZ;
    QDoubleSpinBox *doubleSpinBoxOffsetZ;
    QLabel *labelObjectSize;
    QDoubleSpinBox *doubleSpinBoxObjectSize;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_12;
    QFormLayout *formLayout_4;
    QLabel *thicknessLabel;
    QDoubleSpinBox *doubleSpinBoxSurfaceThickness;
    QLabel *secondOrderCoeffLabel;
    QDoubleSpinBox *doubleSpinBox2ndOrderCoeff;
    QLabel *firstOrderCoeffLabel;
    QDoubleSpinBox *doubleSpinBox1stOrderCoeff;
    QLabel *zerothOrderCoeffLabel;
    QDoubleSpinBox *doubleSpinBox0thOrderCoeff;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_10;
    QFormLayout *formLayout_3;
    QLabel *labelHelicoidCxMm;
    QDoubleSpinBox *doubleSpinboxHelicoidCxMm;
    QLabel *labelHelicoidCyMm;
    QDoubleSpinBox *doubleSpinboxHelicoidCyMm;
    QLabel *labelHelicoidCzMm;
    QDoubleSpinBox *doubleSpinboxHelicoidCzMm;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayoutStimulusSettings;
    QLabel *labelStimulusSpheresNumber;
    QSpinBox *spinBoxStimulusNSpheres;
    QLabel *labelStimulusRadiusMin;
    QSpinBox *spinBoxStimulusSpheresRadiusMin;
    QLabel *labelStimulusRadiusMax;
    QSpinBox *spinBoxStimulusSpheresRadiusMax;
    QLabel *randomDotsLabel;
    QCheckBox *randomDotsCheckBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QLabel *labelMemoryAllocatedMB;
    QSpinBox *spinBoxMemoryAllocated;
    QCheckBox *checkBoxUseOffscreenRendering;
    QPushButton *pushButtonStimulusRandomizeSpheres;
    QPushButton *pushButtonGenerateFrames;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_11;
    QPushButton *pushButtonLoadBinVox;
    QLabel *labelTextureInformations;
    QLabel *labelTextureInfo;
    QSpacerItem *verticalSpacer;
    QWidget *tabCameracalibration;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxDirectLinearCalibration;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxCameraViewMode;
    QCheckBox *checkBoxUseCalibratedView;
    QPushButton *pushButtonCalibrate;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *labelCameraFOV;
    QDoubleSpinBox *doubleSpinBoxCameraFOV;
    QLabel *labelCameraZNear;
    QDoubleSpinBox *doubleSpinboxCameraZNear;
    QLabel *labelCameraZFar;
    QDoubleSpinBox *doubleSpinboxCameraZFar;
    QDoubleSpinBox *doubleSpinBoxCameraEyeZ;
    QLabel *labelCameraEyeZ;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabProjector;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonProjectorInitialize;
    QPushButton *pushButtonProjectorRelease;
    QPushButton *pushButtonUploadCurrentSequence;
    QFormLayout *formLayout_6;
    QLabel *labelNSlicesProjectorNumSlices;
    QSpinBox *spinBoxProjectorNSlices;
    QLabel *labelLEDCurrent;
    QSpinBox *spinBoxProjectorLEDcurrent;
    QLabel *labelLEDpercentage;
    QDoubleSpinBox *doubleSpinBoxProjectorLEDpercentage;
    QLabel *labelProjectorFrequency;
    QSpinBox *spinBoxProjectorBitDepth;
    QLabel *labelProjectorMicrosecPerFrame;
    QSpinBox *spinBoxProjectorMicrosecondsPerFrame;
    QLabel *labelMicrosecondsPerRound;
    QSpinBox *spinBoxProjectorMicrosecondsPerRound;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_25;
    QPushButton *pushButtonMotorInitialize;
    QPushButton *pushButtonMotorStart;
    QPushButton *pushButtonMotorStop;
    QFormLayout *formLayout_9;
    QLabel *flickerRateHzLabel;
    QDoubleSpinBox *doubleSpinBoxFlickerRateHz;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *revMinLabel;
    QSpinBox *spinBoxMotorRevMin;
    QComboBox *comboBoxMotorUnitsToRevMin;
    QSpinBox *spinBoxMotorSpeed;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidgetSequences;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButtonProjectorStartProjection;
    QPushButton *pushButtonProjectorStopProjection;
    QPushButton *pushButtonProjectorChangeSequence;
    QPushButton *pushButtonRemoveSequence;
    QSpacerItem *verticalSpacer_4;
    QWidget *tabExperiment;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBoxExperiment;
    QVBoxLayout *verticalLayout_14;
    QPushButton *pushButtonStartExperiment;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_23;
    QGroupBox *groupBoxDeBrujinRandomization;
    QVBoxLayout *verticalLayout_15;
    QFormLayout *formLayout_7;
    QLabel *subsequenceLenghtLabel;
    QSpinBox *subsequenceLenghtSpinBox;
    QLabel *subsequenceRepetitionsLabel;
    QSpinBox *subsequenceRepetitionsSpinBox;
    QLabel *preRandomizeLabel;
    QCheckBox *preRandomizeCheckBox;
    QGroupBox *groupBoxExperimentParameters;
    QVBoxLayout *verticalLayout_13;
    QFormLayout *formLayout_5;
    QLabel *factorCurvatureLabel;
    QLineEdit *factorCurvatureLineEdit;
    QLabel *repetitionsLabel;
    QSpinBox *repetitionsSpinBox;
    QLabel *randomizeLabel;
    QVBoxLayout *verticalLayout_17;
    QRadioButton *radioButtonRandomizeNone;
    QRadioButton *radioButtonRandomizeExtrablock;
    QRadioButton *radioButtonRandomizeIntraBlock;
    QRadioButton *radioButtonRandomizeNoConsecutiv;
    QRadioButton *radioButtonDeBrujin;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_24;
    QFormLayout *formLayout_8;
    QLabel *monitorWidthMMLabel;
    QDoubleSpinBox *monitorWidthMMDoubleSpinBox;
    QLabel *monitorHeightMMLabel;
    QDoubleSpinBox *monitorHeightMMDoubleSpinBox;
    QLabel *monitorResolutionXLabel;
    QSpinBox *monitorResolutionXSpinBox;
    QLabel *monitorResolutionYLabel;
    QSpinBox *monitorResolutionYSpinBox;
    QGroupBox *groupBoxExperimentInfo;
    QVBoxLayout *verticalLayout_16;
    QPlainTextEdit *plainTextExperimentInfo;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_22;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    VolvuxWidget *volumetricGLWidget;
    QSpacerItem *verticalSpacer_7;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroupRandomizationMethod;
    QButtonGroup *buttonGroupMotorStartStop;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1600, 1049);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabScene = new QWidget();
        tabScene->setObjectName(QStringLiteral("tabScene"));
        verticalLayout_7 = new QVBoxLayout(tabScene);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBox_3 = new QGroupBox(tabScene);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        formLayoutHelicoidParameters = new QFormLayout();
        formLayoutHelicoidParameters->setObjectName(QStringLiteral("formLayoutHelicoidParameters"));
        formLayoutHelicoidParameters->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelOffsetX = new QLabel(groupBox_3);
        labelOffsetX->setObjectName(QStringLiteral("labelOffsetX"));

        formLayoutHelicoidParameters->setWidget(0, QFormLayout::LabelRole, labelOffsetX);

        doubleSpinBoxOffsetX = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxOffsetX->setObjectName(QStringLiteral("doubleSpinBoxOffsetX"));
        doubleSpinBoxOffsetX->setMouseTracking(true);
        doubleSpinBoxOffsetX->setWrapping(true);
        doubleSpinBoxOffsetX->setMinimum(-500);
        doubleSpinBoxOffsetX->setMaximum(500);

        formLayoutHelicoidParameters->setWidget(0, QFormLayout::FieldRole, doubleSpinBoxOffsetX);

        labelOffsetY = new QLabel(groupBox_3);
        labelOffsetY->setObjectName(QStringLiteral("labelOffsetY"));

        formLayoutHelicoidParameters->setWidget(1, QFormLayout::LabelRole, labelOffsetY);

        doubleSpinBoxOffsetY = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxOffsetY->setObjectName(QStringLiteral("doubleSpinBoxOffsetY"));
        doubleSpinBoxOffsetY->setMouseTracking(true);
        doubleSpinBoxOffsetY->setWrapping(true);
        doubleSpinBoxOffsetY->setMinimum(-500);
        doubleSpinBoxOffsetY->setMaximum(500);

        formLayoutHelicoidParameters->setWidget(1, QFormLayout::FieldRole, doubleSpinBoxOffsetY);

        labelOffsetZ = new QLabel(groupBox_3);
        labelOffsetZ->setObjectName(QStringLiteral("labelOffsetZ"));

        formLayoutHelicoidParameters->setWidget(2, QFormLayout::LabelRole, labelOffsetZ);

        doubleSpinBoxOffsetZ = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxOffsetZ->setObjectName(QStringLiteral("doubleSpinBoxOffsetZ"));
        doubleSpinBoxOffsetZ->setMouseTracking(true);
        doubleSpinBoxOffsetZ->setWrapping(true);
        doubleSpinBoxOffsetZ->setMinimum(-500);
        doubleSpinBoxOffsetZ->setMaximum(500);

        formLayoutHelicoidParameters->setWidget(2, QFormLayout::FieldRole, doubleSpinBoxOffsetZ);

        labelObjectSize = new QLabel(groupBox_3);
        labelObjectSize->setObjectName(QStringLiteral("labelObjectSize"));

        formLayoutHelicoidParameters->setWidget(3, QFormLayout::LabelRole, labelObjectSize);

        doubleSpinBoxObjectSize = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxObjectSize->setObjectName(QStringLiteral("doubleSpinBoxObjectSize"));
        doubleSpinBoxObjectSize->setMaximum(600);
        doubleSpinBoxObjectSize->setValue(110);

        formLayoutHelicoidParameters->setWidget(3, QFormLayout::FieldRole, doubleSpinBoxObjectSize);


        verticalLayout_6->addLayout(formLayoutHelicoidParameters);


        verticalLayout_7->addWidget(groupBox_3);

        groupBox_9 = new QGroupBox(tabScene);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_12 = new QVBoxLayout(groupBox_9);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        thicknessLabel = new QLabel(groupBox_9);
        thicknessLabel->setObjectName(QStringLiteral("thicknessLabel"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, thicknessLabel);

        doubleSpinBoxSurfaceThickness = new QDoubleSpinBox(groupBox_9);
        doubleSpinBoxSurfaceThickness->setObjectName(QStringLiteral("doubleSpinBoxSurfaceThickness"));
        doubleSpinBoxSurfaceThickness->setMaximum(9.9999e+08);
        doubleSpinBoxSurfaceThickness->setValue(0.5);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, doubleSpinBoxSurfaceThickness);

        secondOrderCoeffLabel = new QLabel(groupBox_9);
        secondOrderCoeffLabel->setObjectName(QStringLiteral("secondOrderCoeffLabel"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, secondOrderCoeffLabel);

        doubleSpinBox2ndOrderCoeff = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox2ndOrderCoeff->setObjectName(QStringLiteral("doubleSpinBox2ndOrderCoeff"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, doubleSpinBox2ndOrderCoeff);

        firstOrderCoeffLabel = new QLabel(groupBox_9);
        firstOrderCoeffLabel->setObjectName(QStringLiteral("firstOrderCoeffLabel"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, firstOrderCoeffLabel);

        doubleSpinBox1stOrderCoeff = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox1stOrderCoeff->setObjectName(QStringLiteral("doubleSpinBox1stOrderCoeff"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, doubleSpinBox1stOrderCoeff);

        zerothOrderCoeffLabel = new QLabel(groupBox_9);
        zerothOrderCoeffLabel->setObjectName(QStringLiteral("zerothOrderCoeffLabel"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, zerothOrderCoeffLabel);

        doubleSpinBox0thOrderCoeff = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox0thOrderCoeff->setObjectName(QStringLiteral("doubleSpinBox0thOrderCoeff"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, doubleSpinBox0thOrderCoeff);


        verticalLayout_12->addLayout(formLayout_4);


        verticalLayout_7->addWidget(groupBox_9);

        groupBox_7 = new QGroupBox(tabScene);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_10 = new QVBoxLayout(groupBox_7);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        labelHelicoidCxMm = new QLabel(groupBox_7);
        labelHelicoidCxMm->setObjectName(QStringLiteral("labelHelicoidCxMm"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, labelHelicoidCxMm);

        doubleSpinboxHelicoidCxMm = new QDoubleSpinBox(groupBox_7);
        doubleSpinboxHelicoidCxMm->setObjectName(QStringLiteral("doubleSpinboxHelicoidCxMm"));
        doubleSpinboxHelicoidCxMm->setMinimum(-1e+06);
        doubleSpinboxHelicoidCxMm->setMaximum(1e+06);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, doubleSpinboxHelicoidCxMm);

        labelHelicoidCyMm = new QLabel(groupBox_7);
        labelHelicoidCyMm->setObjectName(QStringLiteral("labelHelicoidCyMm"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, labelHelicoidCyMm);

        doubleSpinboxHelicoidCyMm = new QDoubleSpinBox(groupBox_7);
        doubleSpinboxHelicoidCyMm->setObjectName(QStringLiteral("doubleSpinboxHelicoidCyMm"));
        doubleSpinboxHelicoidCyMm->setMinimum(-1e+06);
        doubleSpinboxHelicoidCyMm->setMaximum(1e+06);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, doubleSpinboxHelicoidCyMm);

        labelHelicoidCzMm = new QLabel(groupBox_7);
        labelHelicoidCzMm->setObjectName(QStringLiteral("labelHelicoidCzMm"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, labelHelicoidCzMm);

        doubleSpinboxHelicoidCzMm = new QDoubleSpinBox(groupBox_7);
        doubleSpinboxHelicoidCzMm->setObjectName(QStringLiteral("doubleSpinboxHelicoidCzMm"));
        doubleSpinboxHelicoidCzMm->setMinimum(-1e+06);
        doubleSpinboxHelicoidCzMm->setMaximum(1e+06);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, doubleSpinboxHelicoidCzMm);


        verticalLayout_10->addLayout(formLayout_3);


        verticalLayout_7->addWidget(groupBox_7);

        groupBox_2 = new QGroupBox(tabScene);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        formLayoutStimulusSettings = new QFormLayout();
        formLayoutStimulusSettings->setObjectName(QStringLiteral("formLayoutStimulusSettings"));
        formLayoutStimulusSettings->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelStimulusSpheresNumber = new QLabel(groupBox_2);
        labelStimulusSpheresNumber->setObjectName(QStringLiteral("labelStimulusSpheresNumber"));

        formLayoutStimulusSettings->setWidget(0, QFormLayout::LabelRole, labelStimulusSpheresNumber);

        spinBoxStimulusNSpheres = new QSpinBox(groupBox_2);
        spinBoxStimulusNSpheres->setObjectName(QStringLiteral("spinBoxStimulusNSpheres"));
        spinBoxStimulusNSpheres->setMaximum(100000);
        spinBoxStimulusNSpheres->setValue(1000);

        formLayoutStimulusSettings->setWidget(0, QFormLayout::FieldRole, spinBoxStimulusNSpheres);

        labelStimulusRadiusMin = new QLabel(groupBox_2);
        labelStimulusRadiusMin->setObjectName(QStringLiteral("labelStimulusRadiusMin"));

        formLayoutStimulusSettings->setWidget(1, QFormLayout::LabelRole, labelStimulusRadiusMin);

        spinBoxStimulusSpheresRadiusMin = new QSpinBox(groupBox_2);
        spinBoxStimulusSpheresRadiusMin->setObjectName(QStringLiteral("spinBoxStimulusSpheresRadiusMin"));
        spinBoxStimulusSpheresRadiusMin->setMaximum(256);
        spinBoxStimulusSpheresRadiusMin->setValue(5);

        formLayoutStimulusSettings->setWidget(1, QFormLayout::FieldRole, spinBoxStimulusSpheresRadiusMin);

        labelStimulusRadiusMax = new QLabel(groupBox_2);
        labelStimulusRadiusMax->setObjectName(QStringLiteral("labelStimulusRadiusMax"));

        formLayoutStimulusSettings->setWidget(2, QFormLayout::LabelRole, labelStimulusRadiusMax);

        spinBoxStimulusSpheresRadiusMax = new QSpinBox(groupBox_2);
        spinBoxStimulusSpheresRadiusMax->setObjectName(QStringLiteral("spinBoxStimulusSpheresRadiusMax"));
        spinBoxStimulusSpheresRadiusMax->setMinimum(1);
        spinBoxStimulusSpheresRadiusMax->setMaximum(512);
        spinBoxStimulusSpheresRadiusMax->setValue(50);

        formLayoutStimulusSettings->setWidget(2, QFormLayout::FieldRole, spinBoxStimulusSpheresRadiusMax);

        randomDotsLabel = new QLabel(groupBox_2);
        randomDotsLabel->setObjectName(QStringLiteral("randomDotsLabel"));

        formLayoutStimulusSettings->setWidget(3, QFormLayout::LabelRole, randomDotsLabel);

        randomDotsCheckBox = new QCheckBox(groupBox_2);
        randomDotsCheckBox->setObjectName(QStringLiteral("randomDotsCheckBox"));

        formLayoutStimulusSettings->setWidget(3, QFormLayout::FieldRole, randomDotsCheckBox);


        verticalLayout_4->addLayout(formLayoutStimulusSettings);


        verticalLayout_7->addWidget(groupBox_2);

        groupBox = new QGroupBox(tabScene);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelMemoryAllocatedMB = new QLabel(groupBox);
        labelMemoryAllocatedMB->setObjectName(QStringLiteral("labelMemoryAllocatedMB"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelMemoryAllocatedMB);

        spinBoxMemoryAllocated = new QSpinBox(groupBox);
        spinBoxMemoryAllocated->setObjectName(QStringLiteral("spinBoxMemoryAllocated"));
        spinBoxMemoryAllocated->setEnabled(true);
        spinBoxMemoryAllocated->setReadOnly(true);
        spinBoxMemoryAllocated->setMaximum(999999999);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxMemoryAllocated);

        checkBoxUseOffscreenRendering = new QCheckBox(groupBox);
        checkBoxUseOffscreenRendering->setObjectName(QStringLiteral("checkBoxUseOffscreenRendering"));

        formLayout->setWidget(1, QFormLayout::LabelRole, checkBoxUseOffscreenRendering);


        verticalLayout_3->addLayout(formLayout);


        verticalLayout_7->addWidget(groupBox);

        pushButtonStimulusRandomizeSpheres = new QPushButton(tabScene);
        pushButtonStimulusRandomizeSpheres->setObjectName(QStringLiteral("pushButtonStimulusRandomizeSpheres"));

        verticalLayout_7->addWidget(pushButtonStimulusRandomizeSpheres);

        pushButtonGenerateFrames = new QPushButton(tabScene);
        pushButtonGenerateFrames->setObjectName(QStringLiteral("pushButtonGenerateFrames"));

        verticalLayout_7->addWidget(pushButtonGenerateFrames);

        groupBox_8 = new QGroupBox(tabScene);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_11 = new QVBoxLayout(groupBox_8);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        pushButtonLoadBinVox = new QPushButton(groupBox_8);
        pushButtonLoadBinVox->setObjectName(QStringLiteral("pushButtonLoadBinVox"));

        verticalLayout_11->addWidget(pushButtonLoadBinVox);

        labelTextureInformations = new QLabel(groupBox_8);
        labelTextureInformations->setObjectName(QStringLiteral("labelTextureInformations"));

        verticalLayout_11->addWidget(labelTextureInformations);

        labelTextureInfo = new QLabel(groupBox_8);
        labelTextureInfo->setObjectName(QStringLiteral("labelTextureInfo"));

        verticalLayout_11->addWidget(labelTextureInfo);

        pushButtonLoadBinVox->raise();
        labelTextureInfo->raise();
        labelTextureInformations->raise();

        verticalLayout_7->addWidget(groupBox_8);

        verticalSpacer = new QSpacerItem(20, 261, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        tabWidget->addTab(tabScene, QString());
        tabCameracalibration = new QWidget();
        tabCameracalibration->setObjectName(QStringLiteral("tabCameracalibration"));
        verticalLayout_5 = new QVBoxLayout(tabCameracalibration);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBoxDirectLinearCalibration = new QGroupBox(tabCameracalibration);
        groupBoxDirectLinearCalibration->setObjectName(QStringLiteral("groupBoxDirectLinearCalibration"));
        horizontalLayout = new QHBoxLayout(groupBoxDirectLinearCalibration);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBoxCameraViewMode = new QCheckBox(groupBoxDirectLinearCalibration);
        checkBoxCameraViewMode->setObjectName(QStringLiteral("checkBoxCameraViewMode"));
        checkBoxCameraViewMode->setChecked(false);

        horizontalLayout->addWidget(checkBoxCameraViewMode);

        checkBoxUseCalibratedView = new QCheckBox(groupBoxDirectLinearCalibration);
        checkBoxUseCalibratedView->setObjectName(QStringLiteral("checkBoxUseCalibratedView"));

        horizontalLayout->addWidget(checkBoxUseCalibratedView);

        pushButtonCalibrate = new QPushButton(groupBoxDirectLinearCalibration);
        pushButtonCalibrate->setObjectName(QStringLiteral("pushButtonCalibrate"));

        horizontalLayout->addWidget(pushButtonCalibrate);


        verticalLayout_5->addWidget(groupBoxDirectLinearCalibration);

        groupBox_4 = new QGroupBox(tabCameracalibration);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelCameraFOV = new QLabel(groupBox_4);
        labelCameraFOV->setObjectName(QStringLiteral("labelCameraFOV"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelCameraFOV);

        doubleSpinBoxCameraFOV = new QDoubleSpinBox(groupBox_4);
        doubleSpinBoxCameraFOV->setObjectName(QStringLiteral("doubleSpinBoxCameraFOV"));
        doubleSpinBoxCameraFOV->setMaximum(180);
        doubleSpinBoxCameraFOV->setSingleStep(1);
        doubleSpinBoxCameraFOV->setValue(3);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, doubleSpinBoxCameraFOV);

        labelCameraZNear = new QLabel(groupBox_4);
        labelCameraZNear->setObjectName(QStringLiteral("labelCameraZNear"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, labelCameraZNear);

        doubleSpinboxCameraZNear = new QDoubleSpinBox(groupBox_4);
        doubleSpinboxCameraZNear->setObjectName(QStringLiteral("doubleSpinboxCameraZNear"));
        doubleSpinboxCameraZNear->setMinimum(0.01);
        doubleSpinboxCameraZNear->setMaximum(1000);
        doubleSpinboxCameraZNear->setSingleStep(1);
        doubleSpinboxCameraZNear->setValue(200);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, doubleSpinboxCameraZNear);

        labelCameraZFar = new QLabel(groupBox_4);
        labelCameraZFar->setObjectName(QStringLiteral("labelCameraZFar"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, labelCameraZFar);

        doubleSpinboxCameraZFar = new QDoubleSpinBox(groupBox_4);
        doubleSpinboxCameraZFar->setObjectName(QStringLiteral("doubleSpinboxCameraZFar"));
        doubleSpinboxCameraZFar->setMaximum(1e+06);
        doubleSpinboxCameraZFar->setSingleStep(10);
        doubleSpinboxCameraZFar->setValue(30000);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, doubleSpinboxCameraZFar);

        doubleSpinBoxCameraEyeZ = new QDoubleSpinBox(groupBox_4);
        doubleSpinBoxCameraEyeZ->setObjectName(QStringLiteral("doubleSpinBoxCameraEyeZ"));
        doubleSpinBoxCameraEyeZ->setMouseTracking(true);
        doubleSpinBoxCameraEyeZ->setMinimum(-1e+06);
        doubleSpinBoxCameraEyeZ->setMaximum(999999);
        doubleSpinBoxCameraEyeZ->setSingleStep(10);
        doubleSpinBoxCameraEyeZ->setValue(-7500);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, doubleSpinBoxCameraEyeZ);

        labelCameraEyeZ = new QLabel(groupBox_4);
        labelCameraEyeZ->setObjectName(QStringLiteral("labelCameraEyeZ"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelCameraEyeZ);


        verticalLayout_2->addLayout(formLayout_2);


        verticalLayout_5->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 267, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        tabWidget->addTab(tabCameracalibration, QString());
        tabProjector = new QWidget();
        tabProjector->setObjectName(QStringLiteral("tabProjector"));
        verticalLayout_21 = new QVBoxLayout(tabProjector);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBox_5 = new QGroupBox(tabProjector);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonProjectorInitialize = new QPushButton(groupBox_5);
        pushButtonProjectorInitialize->setObjectName(QStringLiteral("pushButtonProjectorInitialize"));

        verticalLayout->addWidget(pushButtonProjectorInitialize);

        pushButtonProjectorRelease = new QPushButton(groupBox_5);
        pushButtonProjectorRelease->setObjectName(QStringLiteral("pushButtonProjectorRelease"));

        verticalLayout->addWidget(pushButtonProjectorRelease);

        pushButtonUploadCurrentSequence = new QPushButton(groupBox_5);
        pushButtonUploadCurrentSequence->setObjectName(QStringLiteral("pushButtonUploadCurrentSequence"));

        verticalLayout->addWidget(pushButtonUploadCurrentSequence);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        formLayout_6->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelNSlicesProjectorNumSlices = new QLabel(groupBox_5);
        labelNSlicesProjectorNumSlices->setObjectName(QStringLiteral("labelNSlicesProjectorNumSlices"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, labelNSlicesProjectorNumSlices);

        spinBoxProjectorNSlices = new QSpinBox(groupBox_5);
        spinBoxProjectorNSlices->setObjectName(QStringLiteral("spinBoxProjectorNSlices"));
        spinBoxProjectorNSlices->setMinimum(1);
        spinBoxProjectorNSlices->setMaximum(99999999);
        spinBoxProjectorNSlices->setValue(96);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, spinBoxProjectorNSlices);

        labelLEDCurrent = new QLabel(groupBox_5);
        labelLEDCurrent->setObjectName(QStringLiteral("labelLEDCurrent"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, labelLEDCurrent);

        spinBoxProjectorLEDcurrent = new QSpinBox(groupBox_5);
        spinBoxProjectorLEDcurrent->setObjectName(QStringLiteral("spinBoxProjectorLEDcurrent"));
        spinBoxProjectorLEDcurrent->setEnabled(false);
        spinBoxProjectorLEDcurrent->setMaximum(15000);
        spinBoxProjectorLEDcurrent->setSingleStep(100);
        spinBoxProjectorLEDcurrent->setValue(2000);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, spinBoxProjectorLEDcurrent);

        labelLEDpercentage = new QLabel(groupBox_5);
        labelLEDpercentage->setObjectName(QStringLiteral("labelLEDpercentage"));

        formLayout_6->setWidget(2, QFormLayout::LabelRole, labelLEDpercentage);

        doubleSpinBoxProjectorLEDpercentage = new QDoubleSpinBox(groupBox_5);
        doubleSpinBoxProjectorLEDpercentage->setObjectName(QStringLiteral("doubleSpinBoxProjectorLEDpercentage"));
        doubleSpinBoxProjectorLEDpercentage->setEnabled(false);
        doubleSpinBoxProjectorLEDpercentage->setMaximum(100);
        doubleSpinBoxProjectorLEDpercentage->setSingleStep(5);
        doubleSpinBoxProjectorLEDpercentage->setValue(100);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, doubleSpinBoxProjectorLEDpercentage);

        labelProjectorFrequency = new QLabel(groupBox_5);
        labelProjectorFrequency->setObjectName(QStringLiteral("labelProjectorFrequency"));

        formLayout_6->setWidget(3, QFormLayout::LabelRole, labelProjectorFrequency);

        spinBoxProjectorBitDepth = new QSpinBox(groupBox_5);
        spinBoxProjectorBitDepth->setObjectName(QStringLiteral("spinBoxProjectorBitDepth"));
        spinBoxProjectorBitDepth->setValue(1);

        formLayout_6->setWidget(3, QFormLayout::FieldRole, spinBoxProjectorBitDepth);

        labelProjectorMicrosecPerFrame = new QLabel(groupBox_5);
        labelProjectorMicrosecPerFrame->setObjectName(QStringLiteral("labelProjectorMicrosecPerFrame"));

        formLayout_6->setWidget(4, QFormLayout::LabelRole, labelProjectorMicrosecPerFrame);

        spinBoxProjectorMicrosecondsPerFrame = new QSpinBox(groupBox_5);
        spinBoxProjectorMicrosecondsPerFrame->setObjectName(QStringLiteral("spinBoxProjectorMicrosecondsPerFrame"));
        spinBoxProjectorMicrosecondsPerFrame->setMinimum(1);
        spinBoxProjectorMicrosecondsPerFrame->setMaximum(100000);

        formLayout_6->setWidget(4, QFormLayout::FieldRole, spinBoxProjectorMicrosecondsPerFrame);

        labelMicrosecondsPerRound = new QLabel(groupBox_5);
        labelMicrosecondsPerRound->setObjectName(QStringLiteral("labelMicrosecondsPerRound"));

        formLayout_6->setWidget(5, QFormLayout::LabelRole, labelMicrosecondsPerRound);

        spinBoxProjectorMicrosecondsPerRound = new QSpinBox(groupBox_5);
        spinBoxProjectorMicrosecondsPerRound->setObjectName(QStringLiteral("spinBoxProjectorMicrosecondsPerRound"));
        spinBoxProjectorMicrosecondsPerRound->setMinimum(1);
        spinBoxProjectorMicrosecondsPerRound->setMaximum(999999999);
        spinBoxProjectorMicrosecondsPerRound->setSingleStep(1);
        spinBoxProjectorMicrosecondsPerRound->setValue(37500);

        formLayout_6->setWidget(5, QFormLayout::FieldRole, spinBoxProjectorMicrosecondsPerRound);


        verticalLayout->addLayout(formLayout_6);


        horizontalLayout_4->addWidget(groupBox_5);

        groupBox_11 = new QGroupBox(tabProjector);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        verticalLayout_25 = new QVBoxLayout(groupBox_11);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        pushButtonMotorInitialize = new QPushButton(groupBox_11);
        pushButtonMotorInitialize->setObjectName(QStringLiteral("pushButtonMotorInitialize"));

        verticalLayout_25->addWidget(pushButtonMotorInitialize);

        pushButtonMotorStart = new QPushButton(groupBox_11);
        buttonGroupMotorStartStop = new QButtonGroup(MainWindow);
        buttonGroupMotorStartStop->setObjectName(QStringLiteral("buttonGroupMotorStartStop"));
        buttonGroupMotorStartStop->addButton(pushButtonMotorStart);
        pushButtonMotorStart->setObjectName(QStringLiteral("pushButtonMotorStart"));
        pushButtonMotorStart->setCheckable(true);
        pushButtonMotorStart->setChecked(false);

        verticalLayout_25->addWidget(pushButtonMotorStart);

        pushButtonMotorStop = new QPushButton(groupBox_11);
        buttonGroupMotorStartStop->addButton(pushButtonMotorStop);
        pushButtonMotorStop->setObjectName(QStringLiteral("pushButtonMotorStop"));
        pushButtonMotorStop->setCheckable(true);
        pushButtonMotorStop->setChecked(true);

        verticalLayout_25->addWidget(pushButtonMotorStop);

        formLayout_9 = new QFormLayout();
        formLayout_9->setObjectName(QStringLiteral("formLayout_9"));
        formLayout_9->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        flickerRateHzLabel = new QLabel(groupBox_11);
        flickerRateHzLabel->setObjectName(QStringLiteral("flickerRateHzLabel"));

        formLayout_9->setWidget(0, QFormLayout::LabelRole, flickerRateHzLabel);

        doubleSpinBoxFlickerRateHz = new QDoubleSpinBox(groupBox_11);
        doubleSpinBoxFlickerRateHz->setObjectName(QStringLiteral("doubleSpinBoxFlickerRateHz"));
        doubleSpinBoxFlickerRateHz->setKeyboardTracking(false);
        doubleSpinBoxFlickerRateHz->setMaximum(1e+06);
        doubleSpinBoxFlickerRateHz->setValue(20);

        formLayout_9->setWidget(0, QFormLayout::FieldRole, doubleSpinBoxFlickerRateHz);

        label_2 = new QLabel(groupBox_11);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_9->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox_11);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_9->setWidget(2, QFormLayout::LabelRole, label_3);

        revMinLabel = new QLabel(groupBox_11);
        revMinLabel->setObjectName(QStringLiteral("revMinLabel"));

        formLayout_9->setWidget(3, QFormLayout::LabelRole, revMinLabel);

        spinBoxMotorRevMin = new QSpinBox(groupBox_11);
        spinBoxMotorRevMin->setObjectName(QStringLiteral("spinBoxMotorRevMin"));
        spinBoxMotorRevMin->setKeyboardTracking(false);
        spinBoxMotorRevMin->setMaximum(1000000);

        formLayout_9->setWidget(3, QFormLayout::FieldRole, spinBoxMotorRevMin);

        comboBoxMotorUnitsToRevMin = new QComboBox(groupBox_11);
        comboBoxMotorUnitsToRevMin->setObjectName(QStringLiteral("comboBoxMotorUnitsToRevMin"));

        formLayout_9->setWidget(2, QFormLayout::FieldRole, comboBoxMotorUnitsToRevMin);

        spinBoxMotorSpeed = new QSpinBox(groupBox_11);
        spinBoxMotorSpeed->setObjectName(QStringLiteral("spinBoxMotorSpeed"));
        spinBoxMotorSpeed->setKeyboardTracking(false);
        spinBoxMotorSpeed->setMaximum(2000000);

        formLayout_9->setWidget(1, QFormLayout::FieldRole, spinBoxMotorSpeed);


        verticalLayout_25->addLayout(formLayout_9);


        horizontalLayout_4->addWidget(groupBox_11);


        verticalLayout_21->addLayout(horizontalLayout_4);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        groupBox_6 = new QGroupBox(tabProjector);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        listWidgetSequences = new QListWidget(groupBox_6);
        listWidgetSequences->setObjectName(QStringLiteral("listWidgetSequences"));
        sizePolicy.setHeightForWidth(listWidgetSequences->sizePolicy().hasHeightForWidth());
        listWidgetSequences->setSizePolicy(sizePolicy);
        listWidgetSequences->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(listWidgetSequences);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        pushButtonProjectorStartProjection = new QPushButton(groupBox_6);
        pushButtonProjectorStartProjection->setObjectName(QStringLiteral("pushButtonProjectorStartProjection"));

        verticalLayout_9->addWidget(pushButtonProjectorStartProjection);

        pushButtonProjectorStopProjection = new QPushButton(groupBox_6);
        pushButtonProjectorStopProjection->setObjectName(QStringLiteral("pushButtonProjectorStopProjection"));

        verticalLayout_9->addWidget(pushButtonProjectorStopProjection);

        pushButtonProjectorChangeSequence = new QPushButton(groupBox_6);
        pushButtonProjectorChangeSequence->setObjectName(QStringLiteral("pushButtonProjectorChangeSequence"));

        verticalLayout_9->addWidget(pushButtonProjectorChangeSequence);

        pushButtonRemoveSequence = new QPushButton(groupBox_6);
        pushButtonRemoveSequence->setObjectName(QStringLiteral("pushButtonRemoveSequence"));

        verticalLayout_9->addWidget(pushButtonRemoveSequence);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout_9);


        verticalLayout_20->addWidget(groupBox_6);


        verticalLayout_21->addLayout(verticalLayout_20);

        tabWidget->addTab(tabProjector, QString());
        tabExperiment = new QWidget();
        tabExperiment->setObjectName(QStringLiteral("tabExperiment"));
        horizontalLayout_5 = new QHBoxLayout(tabExperiment);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBoxExperiment = new QGroupBox(tabExperiment);
        groupBoxExperiment->setObjectName(QStringLiteral("groupBoxExperiment"));
        verticalLayout_14 = new QVBoxLayout(groupBoxExperiment);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        pushButtonStartExperiment = new QPushButton(groupBoxExperiment);
        pushButtonStartExperiment->setObjectName(QStringLiteral("pushButtonStartExperiment"));

        verticalLayout_14->addWidget(pushButtonStartExperiment);


        horizontalLayout_6->addWidget(groupBoxExperiment);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_18->addLayout(horizontalLayout_6);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        groupBoxDeBrujinRandomization = new QGroupBox(tabExperiment);
        groupBoxDeBrujinRandomization->setObjectName(QStringLiteral("groupBoxDeBrujinRandomization"));
        verticalLayout_15 = new QVBoxLayout(groupBoxDeBrujinRandomization);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        formLayout_7 = new QFormLayout();
        formLayout_7->setObjectName(QStringLiteral("formLayout_7"));
        subsequenceLenghtLabel = new QLabel(groupBoxDeBrujinRandomization);
        subsequenceLenghtLabel->setObjectName(QStringLiteral("subsequenceLenghtLabel"));

        formLayout_7->setWidget(0, QFormLayout::LabelRole, subsequenceLenghtLabel);

        subsequenceLenghtSpinBox = new QSpinBox(groupBoxDeBrujinRandomization);
        subsequenceLenghtSpinBox->setObjectName(QStringLiteral("subsequenceLenghtSpinBox"));
        subsequenceLenghtSpinBox->setValue(1);

        formLayout_7->setWidget(0, QFormLayout::FieldRole, subsequenceLenghtSpinBox);

        subsequenceRepetitionsLabel = new QLabel(groupBoxDeBrujinRandomization);
        subsequenceRepetitionsLabel->setObjectName(QStringLiteral("subsequenceRepetitionsLabel"));

        formLayout_7->setWidget(1, QFormLayout::LabelRole, subsequenceRepetitionsLabel);

        subsequenceRepetitionsSpinBox = new QSpinBox(groupBoxDeBrujinRandomization);
        subsequenceRepetitionsSpinBox->setObjectName(QStringLiteral("subsequenceRepetitionsSpinBox"));
        subsequenceRepetitionsSpinBox->setValue(1);

        formLayout_7->setWidget(1, QFormLayout::FieldRole, subsequenceRepetitionsSpinBox);

        preRandomizeLabel = new QLabel(groupBoxDeBrujinRandomization);
        preRandomizeLabel->setObjectName(QStringLiteral("preRandomizeLabel"));

        formLayout_7->setWidget(2, QFormLayout::LabelRole, preRandomizeLabel);

        preRandomizeCheckBox = new QCheckBox(groupBoxDeBrujinRandomization);
        preRandomizeCheckBox->setObjectName(QStringLiteral("preRandomizeCheckBox"));
        preRandomizeCheckBox->setChecked(true);

        formLayout_7->setWidget(2, QFormLayout::FieldRole, preRandomizeCheckBox);


        verticalLayout_15->addLayout(formLayout_7);


        verticalLayout_23->addWidget(groupBoxDeBrujinRandomization);

        groupBoxExperimentParameters = new QGroupBox(tabExperiment);
        groupBoxExperimentParameters->setObjectName(QStringLiteral("groupBoxExperimentParameters"));
        verticalLayout_13 = new QVBoxLayout(groupBoxExperimentParameters);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        factorCurvatureLabel = new QLabel(groupBoxExperimentParameters);
        factorCurvatureLabel->setObjectName(QStringLiteral("factorCurvatureLabel"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, factorCurvatureLabel);

        factorCurvatureLineEdit = new QLineEdit(groupBoxExperimentParameters);
        factorCurvatureLineEdit->setObjectName(QStringLiteral("factorCurvatureLineEdit"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, factorCurvatureLineEdit);

        repetitionsLabel = new QLabel(groupBoxExperimentParameters);
        repetitionsLabel->setObjectName(QStringLiteral("repetitionsLabel"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, repetitionsLabel);

        repetitionsSpinBox = new QSpinBox(groupBoxExperimentParameters);
        repetitionsSpinBox->setObjectName(QStringLiteral("repetitionsSpinBox"));
        repetitionsSpinBox->setMinimum(1);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, repetitionsSpinBox);

        randomizeLabel = new QLabel(groupBoxExperimentParameters);
        randomizeLabel->setObjectName(QStringLiteral("randomizeLabel"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, randomizeLabel);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        radioButtonRandomizeNone = new QRadioButton(groupBoxExperimentParameters);
        buttonGroupRandomizationMethod = new QButtonGroup(MainWindow);
        buttonGroupRandomizationMethod->setObjectName(QStringLiteral("buttonGroupRandomizationMethod"));
        buttonGroupRandomizationMethod->addButton(radioButtonRandomizeNone);
        radioButtonRandomizeNone->setObjectName(QStringLiteral("radioButtonRandomizeNone"));
        radioButtonRandomizeNone->setChecked(true);

        verticalLayout_17->addWidget(radioButtonRandomizeNone);

        radioButtonRandomizeExtrablock = new QRadioButton(groupBoxExperimentParameters);
        buttonGroupRandomizationMethod->addButton(radioButtonRandomizeExtrablock);
        radioButtonRandomizeExtrablock->setObjectName(QStringLiteral("radioButtonRandomizeExtrablock"));

        verticalLayout_17->addWidget(radioButtonRandomizeExtrablock);

        radioButtonRandomizeIntraBlock = new QRadioButton(groupBoxExperimentParameters);
        buttonGroupRandomizationMethod->addButton(radioButtonRandomizeIntraBlock);
        radioButtonRandomizeIntraBlock->setObjectName(QStringLiteral("radioButtonRandomizeIntraBlock"));

        verticalLayout_17->addWidget(radioButtonRandomizeIntraBlock);

        radioButtonRandomizeNoConsecutiv = new QRadioButton(groupBoxExperimentParameters);
        buttonGroupRandomizationMethod->addButton(radioButtonRandomizeNoConsecutiv);
        radioButtonRandomizeNoConsecutiv->setObjectName(QStringLiteral("radioButtonRandomizeNoConsecutiv"));

        verticalLayout_17->addWidget(radioButtonRandomizeNoConsecutiv);

        radioButtonDeBrujin = new QRadioButton(groupBoxExperimentParameters);
        buttonGroupRandomizationMethod->addButton(radioButtonDeBrujin);
        radioButtonDeBrujin->setObjectName(QStringLiteral("radioButtonDeBrujin"));

        verticalLayout_17->addWidget(radioButtonDeBrujin);


        formLayout_5->setLayout(2, QFormLayout::FieldRole, verticalLayout_17);


        verticalLayout_13->addLayout(formLayout_5);


        verticalLayout_23->addWidget(groupBoxExperimentParameters);


        verticalLayout_18->addLayout(verticalLayout_23);


        verticalLayout_19->addLayout(verticalLayout_18);

        groupBox_10 = new QGroupBox(tabExperiment);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        verticalLayout_24 = new QVBoxLayout(groupBox_10);
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        formLayout_8 = new QFormLayout();
        formLayout_8->setObjectName(QStringLiteral("formLayout_8"));
        formLayout_8->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        monitorWidthMMLabel = new QLabel(groupBox_10);
        monitorWidthMMLabel->setObjectName(QStringLiteral("monitorWidthMMLabel"));

        formLayout_8->setWidget(0, QFormLayout::LabelRole, monitorWidthMMLabel);

        monitorWidthMMDoubleSpinBox = new QDoubleSpinBox(groupBox_10);
        monitorWidthMMDoubleSpinBox->setObjectName(QStringLiteral("monitorWidthMMDoubleSpinBox"));
        monitorWidthMMDoubleSpinBox->setMaximum(10000);
        monitorWidthMMDoubleSpinBox->setValue(300);

        formLayout_8->setWidget(0, QFormLayout::FieldRole, monitorWidthMMDoubleSpinBox);

        monitorHeightMMLabel = new QLabel(groupBox_10);
        monitorHeightMMLabel->setObjectName(QStringLiteral("monitorHeightMMLabel"));

        formLayout_8->setWidget(1, QFormLayout::LabelRole, monitorHeightMMLabel);

        monitorHeightMMDoubleSpinBox = new QDoubleSpinBox(groupBox_10);
        monitorHeightMMDoubleSpinBox->setObjectName(QStringLiteral("monitorHeightMMDoubleSpinBox"));
        monitorHeightMMDoubleSpinBox->setMaximum(10000);
        monitorHeightMMDoubleSpinBox->setValue(200);

        formLayout_8->setWidget(1, QFormLayout::FieldRole, monitorHeightMMDoubleSpinBox);

        monitorResolutionXLabel = new QLabel(groupBox_10);
        monitorResolutionXLabel->setObjectName(QStringLiteral("monitorResolutionXLabel"));

        formLayout_8->setWidget(2, QFormLayout::LabelRole, monitorResolutionXLabel);

        monitorResolutionXSpinBox = new QSpinBox(groupBox_10);
        monitorResolutionXSpinBox->setObjectName(QStringLiteral("monitorResolutionXSpinBox"));
        monitorResolutionXSpinBox->setMaximum(10000);
        monitorResolutionXSpinBox->setValue(1280);

        formLayout_8->setWidget(2, QFormLayout::FieldRole, monitorResolutionXSpinBox);

        monitorResolutionYLabel = new QLabel(groupBox_10);
        monitorResolutionYLabel->setObjectName(QStringLiteral("monitorResolutionYLabel"));

        formLayout_8->setWidget(3, QFormLayout::LabelRole, monitorResolutionYLabel);

        monitorResolutionYSpinBox = new QSpinBox(groupBox_10);
        monitorResolutionYSpinBox->setObjectName(QStringLiteral("monitorResolutionYSpinBox"));
        monitorResolutionYSpinBox->setMaximum(10000);
        monitorResolutionYSpinBox->setValue(1024);

        formLayout_8->setWidget(3, QFormLayout::FieldRole, monitorResolutionYSpinBox);


        verticalLayout_24->addLayout(formLayout_8);


        verticalLayout_19->addWidget(groupBox_10);

        groupBoxExperimentInfo = new QGroupBox(tabExperiment);
        groupBoxExperimentInfo->setObjectName(QStringLiteral("groupBoxExperimentInfo"));
        verticalLayout_16 = new QVBoxLayout(groupBoxExperimentInfo);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        plainTextExperimentInfo = new QPlainTextEdit(groupBoxExperimentInfo);
        plainTextExperimentInfo->setObjectName(QStringLiteral("plainTextExperimentInfo"));

        verticalLayout_16->addWidget(plainTextExperimentInfo);


        verticalLayout_19->addWidget(groupBoxExperimentInfo);


        horizontalLayout_5->addLayout(verticalLayout_19);

        tabWidget->addTab(tabExperiment, QString());
        splitter->addWidget(tabWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_22 = new QVBoxLayout(layoutWidget);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        volumetricGLWidget = new VolvuxWidget(frame);
        volumetricGLWidget->setObjectName(QStringLiteral("volumetricGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(volumetricGLWidget->sizePolicy().hasHeightForWidth());
        volumetricGLWidget->setSizePolicy(sizePolicy1);
        volumetricGLWidget->setMinimumSize(QSize(1024, 768));
        volumetricGLWidget->setMaximumSize(QSize(1024, 768));
        volumetricGLWidget->setBaseSize(QSize(1024, 768));
        volumetricGLWidget->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(volumetricGLWidget);


        verticalLayout_22->addWidget(frame);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_22->addItem(verticalSpacer_7);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("VolvuxMainWindow", "Volvux", 0));
        groupBox_3->setTitle(QApplication::translate("VolvuxMainWindow", "Texture Object Parameters", 0));
        labelOffsetX->setText(QApplication::translate("VolvuxMainWindow", "OffsetX [mm]", 0));
        labelOffsetY->setText(QApplication::translate("VolvuxMainWindow", "OffsetY [mm]", 0));
        labelOffsetZ->setText(QApplication::translate("VolvuxMainWindow", "OffsetZ [mm]", 0));
        labelObjectSize->setText(QApplication::translate("VolvuxMainWindow", "ObjectSize [mm]", 0));
        groupBox_9->setTitle(QApplication::translate("VolvuxMainWindow", "Surface filter", 0));
        thicknessLabel->setText(QApplication::translate("VolvuxMainWindow", "Thickness", 0));
        secondOrderCoeffLabel->setText(QApplication::translate("VolvuxMainWindow", "2nd order coeff", 0));
        firstOrderCoeffLabel->setText(QApplication::translate("VolvuxMainWindow", "1st order coeff", 0));
        zerothOrderCoeffLabel->setText(QApplication::translate("VolvuxMainWindow", "0th order coeff", 0));
        groupBox_7->setTitle(QApplication::translate("VolvuxMainWindow", "Helicoid Position Parameters", 0));
        labelHelicoidCxMm->setText(QApplication::translate("VolvuxMainWindow", "Helicoid Cx [mm]", 0));
        labelHelicoidCyMm->setText(QApplication::translate("VolvuxMainWindow", "Helicoid Cy [mm]", 0));
        labelHelicoidCzMm->setText(QApplication::translate("VolvuxMainWindow", "Helicoid Cz [mm]", 0));
        groupBox_2->setTitle(QApplication::translate("VolvuxMainWindow", "Stimulus", 0));
        labelStimulusSpheresNumber->setText(QApplication::translate("VolvuxMainWindow", "#Spheres", 0));
        labelStimulusRadiusMin->setText(QApplication::translate("VolvuxMainWindow", "RadiusMin", 0));
        labelStimulusRadiusMax->setText(QApplication::translate("VolvuxMainWindow", "RadiusMax", 0));
        randomDotsLabel->setText(QApplication::translate("VolvuxMainWindow", "Random Dots", 0));
        groupBox->setTitle(QApplication::translate("VolvuxMainWindow", "Job info", 0));
        labelMemoryAllocatedMB->setText(QApplication::translate("VolvuxMainWindow", "Memory allocated [MB]", 0));
#ifndef QT_NO_STATUSTIP
        spinBoxMemoryAllocated->setStatusTip(QApplication::translate("VolvuxMainWindow", "Size of current frames on client", 0));
#endif // QT_NO_STATUSTIP
        checkBoxUseOffscreenRendering->setText(QApplication::translate("VolvuxMainWindow", "Offscreen rendering", 0));
        pushButtonStimulusRandomizeSpheres->setText(QApplication::translate("VolvuxMainWindow", "Randomize spheres", 0));
        pushButtonGenerateFrames->setText(QApplication::translate("VolvuxMainWindow", "Generate frames", 0));
        groupBox_8->setTitle(QApplication::translate("VolvuxMainWindow", "Volume data", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonLoadBinVox->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p>Load a volumetric dataset in .binvox format ( http://www.cs.princeton.edu/~min/binvox/ )</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonLoadBinVox->setText(QApplication::translate("VolvuxMainWindow", "Load .binvox model...", 0));
        labelTextureInformations->setText(QApplication::translate("VolvuxMainWindow", "Texture informations:", 0));
        labelTextureInfo->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabScene), QApplication::translate("VolvuxMainWindow", "Scene", 0));
        groupBoxDirectLinearCalibration->setTitle(QApplication::translate("VolvuxMainWindow", "Direct camera calibration", 0));
        checkBoxCameraViewMode->setText(QApplication::translate("VolvuxMainWindow", "Camera view mode", 0));
        checkBoxUseCalibratedView->setText(QApplication::translate("VolvuxMainWindow", "Use calibrated view", 0));
        pushButtonCalibrate->setText(QApplication::translate("VolvuxMainWindow", "Make calibration...", 0));
        groupBox_4->setTitle(QApplication::translate("VolvuxMainWindow", "Standard GL Camera control", 0));
        labelCameraFOV->setText(QApplication::translate("VolvuxMainWindow", "FOV", 0));
        labelCameraZNear->setText(QApplication::translate("VolvuxMainWindow", "zNear", 0));
        labelCameraZFar->setText(QApplication::translate("VolvuxMainWindow", "zFar", 0));
        labelCameraEyeZ->setText(QApplication::translate("VolvuxMainWindow", "EyeZ", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabCameracalibration), QApplication::translate("VolvuxMainWindow", "Camera calibration", 0));
        groupBox_5->setTitle(QApplication::translate("VolvuxMainWindow", "Projector Control", 0));
        pushButtonProjectorInitialize->setText(QApplication::translate("VolvuxMainWindow", "Initialize projector", 0));
        pushButtonProjectorRelease->setText(QApplication::translate("VolvuxMainWindow", "Release projector", 0));
        pushButtonUploadCurrentSequence->setText(QApplication::translate("VolvuxMainWindow", "Upload sequence to projector", 0));
        labelNSlicesProjectorNumSlices->setText(QApplication::translate("VolvuxMainWindow", "# Slices", 0));
        labelLEDCurrent->setText(QApplication::translate("VolvuxMainWindow", "LED current [mA]", 0));
        labelLEDpercentage->setText(QApplication::translate("VolvuxMainWindow", "LED percentage", 0));
        labelProjectorFrequency->setText(QApplication::translate("VolvuxMainWindow", "Bit depth", 0));
        labelProjectorMicrosecPerFrame->setText(QApplication::translate("VolvuxMainWindow", "us per frame", 0));
        labelMicrosecondsPerRound->setText(QApplication::translate("VolvuxMainWindow", "us Per Round", 0));
        groupBox_11->setTitle(QApplication::translate("VolvuxMainWindow", "Motor control", 0));
        pushButtonMotorInitialize->setText(QApplication::translate("VolvuxMainWindow", "Address Motor", 0));
        pushButtonMotorStart->setText(QApplication::translate("VolvuxMainWindow", "Start Motor", 0));
        pushButtonMotorStop->setText(QApplication::translate("VolvuxMainWindow", "Stop Motor", 0));
        flickerRateHzLabel->setText(QApplication::translate("VolvuxMainWindow", "Flicker Rate [Hz]", 0));
        label_2->setText(QApplication::translate("VolvuxMainWindow", "Speed [Units/min]", 0));
        label_3->setText(QApplication::translate("VolvuxMainWindow", "Units to rev/min", 0));
        revMinLabel->setText(QApplication::translate("VolvuxMainWindow", "Rev/Min", 0));
        comboBoxMotorUnitsToRevMin->clear();
        comboBoxMotorUnitsToRevMin->insertItems(0, QStringList()
         << QApplication::translate("VolvuxMainWindow", "65536", 0)
         << QApplication::translate("VolvuxMainWindow", "32768", 0)
         << QApplication::translate("VolvuxMainWindow", "131072", 0)
        );
        groupBox_6->setTitle(QApplication::translate("VolvuxMainWindow", "Projector current sequences", 0));
        pushButtonProjectorStartProjection->setText(QApplication::translate("VolvuxMainWindow", "Start projection", 0));
        pushButtonProjectorStopProjection->setText(QApplication::translate("VolvuxMainWindow", "Stop projection", 0));
        pushButtonProjectorChangeSequence->setText(QApplication::translate("VolvuxMainWindow", "Change to sequence", 0));
        pushButtonRemoveSequence->setText(QApplication::translate("VolvuxMainWindow", "Remove sequence", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabProjector), QApplication::translate("VolvuxMainWindow", "Projector/Motor", 0));
        groupBoxExperiment->setTitle(QApplication::translate("VolvuxMainWindow", "Experiment control", 0));
        pushButtonStartExperiment->setText(QApplication::translate("VolvuxMainWindow", "Start Experiment", 0));
        groupBoxDeBrujinRandomization->setTitle(QApplication::translate("VolvuxMainWindow", "DeBrujin Randomization Parameters", 0));
        subsequenceLenghtLabel->setText(QApplication::translate("VolvuxMainWindow", "Subsequence lenght", 0));
#ifndef QT_NO_TOOLTIP
        subsequenceLenghtSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The lenght of a subsequence of trials.", 0));
#endif // QT_NO_TOOLTIP
        subsequenceRepetitionsLabel->setText(QApplication::translate("VolvuxMainWindow", "Subsequence repetitions", 0));
#ifndef QT_NO_TOOLTIP
        subsequenceRepetitionsSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The repetition of a given subsequence.", 0));
#endif // QT_NO_TOOLTIP
        preRandomizeLabel->setText(QApplication::translate("VolvuxMainWindow", "Pre Randomize", 0));
#ifndef QT_NO_TOOLTIP
        preRandomizeCheckBox->setToolTip(QApplication::translate("VolvuxMainWindow", "Prerandomize the subsequence. It allows to have different debrujin sequences for every experiment otherwise the same standard sequence is created.", 0));
#endif // QT_NO_TOOLTIP
        groupBoxExperimentParameters->setTitle(QApplication::translate("VolvuxMainWindow", "Experiment parameters", 0));
        factorCurvatureLabel->setText(QApplication::translate("VolvuxMainWindow", "Factor Curvature", 0));
#ifndef QT_NO_TOOLTIP
        factorCurvatureLineEdit->setToolTip(QApplication::translate("VolvuxMainWindow", "Insert the curvatures separated by spaces, the factors are then generated.", 0));
#endif // QT_NO_TOOLTIP
        factorCurvatureLineEdit->setText(QApplication::translate("VolvuxMainWindow", "60 120 240", 0));
        repetitionsLabel->setText(QApplication::translate("VolvuxMainWindow", "Repetitions", 0));
        randomizeLabel->setText(QApplication::translate("VolvuxMainWindow", "Randomize", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonRandomizeNone->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p>Present trials in the same order as specified in the factor levels.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        radioButtonRandomizeNone->setText(QApplication::translate("VolvuxMainWindow", "No randomization", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonRandomizeExtrablock->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p>Randomize over the blocks (over the whole experiment). It is possible that two consecutive trials have the same factors.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        radioButtonRandomizeExtrablock->setText(QApplication::translate("VolvuxMainWindow", "Extra-block", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonRandomizeIntraBlock->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p>Randomize within the block. Factor levels are shuffled within the repetition block.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        radioButtonRandomizeIntraBlock->setText(QApplication::translate("VolvuxMainWindow", "Intra-block", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonRandomizeNoConsecutiv->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p align=\"justify\">Randomize the trials in such a way that no two consecutive trials have the same factor levels.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        radioButtonRandomizeNoConsecutiv->setText(QApplication::translate("VolvuxMainWindow", "No consecutive", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonDeBrujin->setToolTip(QApplication::translate("VolvuxMainWindow", "<html><head/><body><p align=\"justify\">The trials are presented in such a order that every possible combination of<br/><span style=\" font-style:italic;\">subsequence length</span> factors is presented <span style=\" font-style:italic;\">subsequence repetitions </span>times. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        radioButtonDeBrujin->setText(QApplication::translate("VolvuxMainWindow", "De Brujin", 0));
        groupBox_10->setTitle(QApplication::translate("VolvuxMainWindow", "External Monitor Settings", 0));
        monitorWidthMMLabel->setText(QApplication::translate("VolvuxMainWindow", "Monitor Width MM", 0));
#ifndef QT_NO_TOOLTIP
        monitorWidthMMDoubleSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The width of stimuli presentation monitor in millimeters.", 0));
#endif // QT_NO_TOOLTIP
        monitorHeightMMLabel->setText(QApplication::translate("VolvuxMainWindow", "Monitor Height MM", 0));
#ifndef QT_NO_TOOLTIP
        monitorHeightMMDoubleSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The height of stimuli presentation monitor in millimeters.", 0));
#endif // QT_NO_TOOLTIP
        monitorResolutionXLabel->setText(QApplication::translate("VolvuxMainWindow", "Monitor Resolution X", 0));
#ifndef QT_NO_TOOLTIP
        monitorResolutionXSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The horizontal resolution of stimuli presentation monitor in pixels.", 0));
#endif // QT_NO_TOOLTIP
        monitorResolutionYLabel->setText(QApplication::translate("VolvuxMainWindow", "Monitor Resolution Y", 0));
#ifndef QT_NO_TOOLTIP
        monitorResolutionYSpinBox->setToolTip(QApplication::translate("VolvuxMainWindow", "The vertical resolution of stimuli presentation monitor in pixels.", 0));
#endif // QT_NO_TOOLTIP
        groupBoxExperimentInfo->setTitle(QApplication::translate("VolvuxMainWindow", "Running experiment information", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabExperiment), QApplication::translate("VolvuxMainWindow", "Experiment", 0));
    } // retranslateUi

};

namespace Ui {
    class VolvuxMainWindow: public Ui_VolvuxMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLVUXMAINWINDOW_H
