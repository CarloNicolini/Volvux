// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2010-2014 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.

#include <QObject>
#include <QListWidget>
#include <QtGui>
#include <QSlider>
#include "VolvuxMainWindow.h"
#include "ui_VolvuxMainWindow.h"

#ifdef COMPILE_GLFW
#include <GLFW/glfw3.h>
#endif
#ifndef BSTR2STR
#define BSTR2STR(X) std::string(const_cast<char *>(_com_util::ConvertBSTRToString( X )))
#endif
#ifndef STR2BSTR
#define STR2BSTR(X) _com_util::ConvertStringToBSTR(const_cast<const char*>(X.c_str()))
#endif

/**
 * @brief VolvuxMainWindow::MainWindow
 * @param parent
 */
VolvuxMainWindow::VolvuxMainWindow(QWidget *parent ):
    QMainWindow(parent),
    ui(new Ui::VolvuxMainWindow)
{
    ui->setupUi(this);
    this->initializeTabSceneQConnections();
    this->initializeTabProjectorQConnections();
    this->initializeTabExperimentQConnections();

    this->resize(minimumSizeHint());
    cerr << "[MAINWINDOW] QtConnections done" << endl;
    cerr << "[MAINWINDOW] User interface successfully setup" << endl;

    // Initialization of OpenGL Widget scene
    //this->ui->volumetricGLWidget->setCameraParameters(ui->doubleSpinBoxCameraFOV->value(),ui->doubleSpinboxCameraZNear->value(),ui->doubleSpinboxCameraZFar->value());
    this->update();

    this->loadSettings();
#ifdef COMPILE_GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("[GLFW] Can't initialize a valid GLFW context here");
        exit(EXIT_FAILURE);
    }
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mode = glfwGetVideoMode(monitor);
    monitorResolutionX = mode->width;
    monitorResolutionY = mode->height;
    glfwGetMonitorPhysicalSize(monitor, &monitorWidthMM, &monitorHeightMM);
#endif
}

/**
 * @brief VolvuxMainWindow::setStackedWidgetHelper
 * @param palp
 */
void VolvuxMainWindow::setStackedWidgetHelper(StackedWidgetHelper *swhelper)
{
    this->helper = swhelper;
}

/**
 * @brief VolvuxMainWindow::setCalibrationHelper
 * @param calibhelper
 */
void VolvuxMainWindow::setCalibrationHelper(CalibrationHelper *calibhelper)
{
    this->calib = calibhelper;
}

/**
 * @brief VolvuxMainWindow::saveSettings
 */
void VolvuxMainWindow::saveSettings()
{
    QSettings settings("Volvux","QtVolumetrixALPExperiment");

    // Scene tab
    settings.beginGroup("Scene");
    settings.setValue("Offset_X",this->ui->doubleSpinBoxOffsetX->value());
    settings.setValue("Offset_Y",this->ui->doubleSpinBoxOffsetY->value());
    settings.setValue("Offset_Z",this->ui->doubleSpinBoxOffsetZ->value());
    settings.setValue("Object_Size",this->ui->doubleSpinBoxObjectSize->value());
    // Suface
    settings.setValue("Thickness",this->ui->doubleSpinBoxSurfaceThickness->value());
    // Helicoid position
    settings.setValue("Tx_MM",this->ui->doubleSpinboxHelicoidCxMm->value());
    settings.setValue("Ty_MM",this->ui->doubleSpinboxHelicoidCyMm->value());
    settings.setValue("Tz_MM",this->ui->doubleSpinboxHelicoidCzMm->value());
    settings.endGroup();

    // Stimulus settings
    settings.beginGroup("Stimulus");
    settings.setValue("N_spheres",this->ui->spinBoxStimulusNSpheres->value());
    settings.setValue("Min_Radius",this->ui->spinBoxStimulusSpheresRadiusMin->value());
    settings.setValue("Max_Radius",this->ui->spinBoxStimulusSpheresRadiusMax->value());
    settings.endGroup();

    // Experiment settigns
    settings.beginGroup("Monitor");
    settings.setValue("Resolution_X",this->ui->monitorResolutionXSpinBox->value());
    settings.setValue("Resolution_Y",this->ui->monitorResolutionYSpinBox->value());
    settings.setValue("Physical_Size_Horizontal_MM",this->ui->monitorWidthMMDoubleSpinBox->value());
    settings.setValue("Physical_Size_Vertical_MM",this->ui->monitorHeightMMDoubleSpinBox->value());
    settings.endGroup();

}

/**
 * @brief VolvuxMainWindow::loadSettings
 */
void VolvuxMainWindow::loadSettings()
{

    QSettings settings("Volvux","QtVolumetrixALPExperiment");
    QFile settingsFile(settings.fileName());
    if (!settingsFile.exists())
        return;
    /*
    foreach (const QString &childKey, settings.allKeys())
        qDebug() << childKey << " " << settings.value(childKey);
    */
    // Scene
    this->ui->doubleSpinBoxOffsetX->setValue(settings.value("Scene/Offset_X").toDouble());
    this->ui->doubleSpinBoxOffsetY->setValue(settings.value("Scene/Offset_Y").toDouble());
    this->ui->doubleSpinBoxOffsetZ->setValue(settings.value("Scene/Offset_Z").toDouble());
    this->ui->doubleSpinBoxSurfaceThickness->setValue(settings.value("Scene/Thickness").toDouble());
    // Helicoid position
    this->ui->doubleSpinboxHelicoidCxMm->setValue(settings.value("Scene/Tx_MM").toDouble());
    this->ui->doubleSpinboxHelicoidCyMm->setValue(settings.value("Scene/Ty_MM").toDouble());
    this->ui->doubleSpinboxHelicoidCzMm->setValue(settings.value("Scene/Tz_MM").toDouble());

    // Stimulus
    this->ui->spinBoxStimulusNSpheres->setValue(settings.value("Stimulus/N_spheres").toInt());
    this->ui->spinBoxStimulusSpheresRadiusMin->setValue(settings.value("Stimulus/Min_Radius").toInt());
    this->ui->spinBoxStimulusSpheresRadiusMax->setValue(settings.value("Stimulus/Max_Radius").toInt());

    // Monitor
    this->ui->monitorResolutionXSpinBox->setValue(settings.value("Monitor/Resolution_X").toInt());
    this->ui->monitorResolutionYSpinBox->setValue(settings.value("Monitor/Resolution_Y").toInt());
    this->ui->monitorWidthMMDoubleSpinBox->setValue(settings.value("Monitor/Physical_Size_Horizontal_MM").toDouble());
    this->ui->monitorHeightMMDoubleSpinBox->setValue(settings.value("Monitor/Physical_Size_Vertical_MM").toInt());
#ifdef COMPILE_GLFW
    this->ui->monitorResolutionXSpinBox->setValue(this->monitorResolutionX);
    this->ui->monitorResolutionYSpinBox->setValue(this->monitorResolutionY);
    this->ui->monitorWidthMMDoubleSpinBox->setValue(this->monitorWidthMM);
    this->ui->monitorHeightMMDoubleSpinBox->setValue(this->monitorHeightMM);
#endif
}

/**
 * @brief VolvuxMainWindow::initializeTabProjectorQConnections
 */
void VolvuxMainWindow::initializeTabProjectorQConnections()
{
    // Projector tab connections
    QObject::connect(this->ui->pushButtonProjectorStartProjection,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorStartProjectionClicked()));
    QObject::connect(this->ui->pushButtonProjectorStopProjection,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorStopProjectionClicked()));
    QObject::connect(this->ui->pushButtonUploadCurrentSequence,SIGNAL(clicked()),this,SLOT(onPushButtonUploadSequenceClicked()));
    QObject::connect(this->ui->pushButtonProjectorChangeSequence,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorSequenceChanged()));
    QObject::connect(this->ui->pushButtonRemoveSequence,SIGNAL(clicked()),this,SLOT(onPushButtonProjectorRemoveSequencePressed()));

    //this->repaint();
}

/**
 * @brief VolvuxMainWindow::initializeTabSceneQConnections
 */
void VolvuxMainWindow::initializeTabSceneQConnections()
{
    // Scene tab connections
    QObject::connect(this->ui->doubleSpinBoxOffsetX,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxOffsetXChanged(double)));
    QObject::connect(this->ui->doubleSpinBoxOffsetY,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxOffsetYChanged(double)));
    QObject::connect(this->ui->doubleSpinBoxOffsetZ,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxOffsetZChanged(double)));

    QObject::connect(this->ui->doubleSpinboxHelicoidCxMm,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxHelicoidXChanged(double)));
    QObject::connect(this->ui->doubleSpinboxHelicoidCyMm,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxHelicoidYChanged(double)));
    QObject::connect(this->ui->doubleSpinboxHelicoidCzMm,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxHelicoidZChanged(double)));

    QObject::connect(this->ui->doubleSpinBoxObjectSize,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinboxObjectSizeChanged(double)));

    // Stimulus tab connections
    QObject::connect(this->ui->pushButtonStimulusRandomizeSpheres,SIGNAL(clicked()),this,SLOT(onPushButtonRandomizeSpheresPressed()));
    QObject::connect(this->ui->pushButtonGenerateFrames,SIGNAL(clicked()),this,SLOT(onPushButtonGenerateFramesPressed()));

    // Enable/disable offscreen rendering
    QObject::connect(this->ui->checkBoxUseOffscreenRendering,SIGNAL(clicked(bool)),this->ui->volumetricGLWidget,SLOT(setOffscreenRendering(bool)));
    QObject::connect(this->ui->pushButtonLoadBinVox,SIGNAL(clicked(bool)),this,SLOT(onPushButtonLoadBinVoxPressed()));

    QObject::connect(this->ui->volumetricGLWidget,SIGNAL(binVoxLoaded(QString)),this->ui->labelTextureInfo,SLOT(setText(QString)));
    // Connection for filtered parametric surface thickness
    QObject::connect(this->ui->doubleSpinBoxSurfaceThickness,SIGNAL(valueChanged(double)),this->ui->volumetricGLWidget,SLOT(onSurfaceThicknessChanged(double)));
}

/**
 * @brief VolvuxMainWindow::initializeTabExperimentQConnections
 */
void VolvuxMainWindow::initializeTabExperimentQConnections()
{
    // Experiment connections
    QObject::connect(this->ui->pushButtonStartExperiment,SIGNAL(clicked()),this,SLOT(onPushButtonExperimentStartClicked()));

    // Disable/enable debrujin window
    this->ui->groupBoxDeBrujinRandomization->setEnabled(false);
    QObject::connect(this->ui->buttonGroupRandomizationMethod,SIGNAL(buttonClicked(int)),this,SLOT(onRandomizationMethodChanged(int)));
}

/**
 * @brief VolvuxMainWindow::onRandomizationMethodChanged
 * @param randomVal
 */
void VolvuxMainWindow::onRandomizationMethodChanged(int randomVal)
{
    if (randomVal == -6)
    {
        this->ui->groupBoxDeBrujinRandomization->setEnabled(true);
    }
    else
    {
        this->ui->groupBoxDeBrujinRandomization->setEnabled(false);
    }
}

/**
 * @brief VolvuxMainWindow::onPushButtonLoadBinVoxPressed
 */
void VolvuxMainWindow::onPushButtonLoadBinVoxPressed()
{
    QString binvoxfile = QFileDialog::getOpenFileName(this,"Select 2D points file",QDir::currentPath(),"*.binvox");
    if (binvoxfile.isEmpty())
        return;
    try
    {
        this->ui->volumetricGLWidget->loadBinvox(binvoxfile.toStdString());
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in loading binvox file",QString(e.what()));
    }
}

/**
 * @brief VolvuxMainWindow::~MainWindow
 */
VolvuxMainWindow::~VolvuxMainWindow()
{
    cerr << "[MAINWINDOW] Destructor" << endl;
    saveSettings();
    delete this->ui;
}

/**
 * @brief Window::eventFilter
 * @return
 */
bool VolvuxMainWindow::eventFilter(QObject *, QEvent *)
{
    return false;
}

/**
 * @brief VolvuxMainWindow::keyPressEvent
 * @param e
 */
void VolvuxMainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape || e->key() == Qt::Key_Q )
        close();
    else
        QWidget::keyPressEvent(e);
}

/**
 * @brief VolvuxMainWindow::onPushButtonGenerateFramesPressed
*/
void VolvuxMainWindow::onPushButtonGenerateFramesPressed()
{
    if (this->ui->checkBoxUseOffscreenRendering->isChecked())
    {
        QObject::connect(this->ui->volumetricGLWidget,SIGNAL(memoryAllocatedMegaBytes(int)),this->ui->spinBoxMemoryAllocated,SLOT(setValue(int)));
    }
    this->ui->statusbar->showMessage("Generating "+QString::number(ui->volumetricGLWidget->slicesNumber)+ " frames...");

    this->ui->volumetricGLWidget->updateGL();
    this->ui->volumetricGLWidget->generateFrames();
    this->ui->statusbar->showMessage("Frames generation done",2000);
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxOffsetXChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxOffsetXChanged(double value)
{
    this->ui->volumetricGLWidget->setObjectOffset(value,ui->doubleSpinBoxOffsetY->value(),ui->doubleSpinBoxOffsetZ->value());
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxOffsetYChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxOffsetYChanged(double value)
{
    this->ui->volumetricGLWidget->setObjectOffset(ui->doubleSpinBoxOffsetX->value(),value,ui->doubleSpinBoxOffsetZ->value());
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxOffsetZChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxOffsetZChanged(double value)
{
    this->ui->volumetricGLWidget->setObjectOffset(ui->doubleSpinBoxOffsetX->value(),ui->doubleSpinBoxOffsetY->value(),value);
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxHelicoidXChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxHelicoidXChanged(double value)
{
    this->ui->volumetricGLWidget->setHelicoidOffset(value,ui->doubleSpinboxHelicoidCyMm->value(),ui->doubleSpinboxHelicoidCzMm->value());
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxHelicoidYChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxHelicoidYChanged(double value)
{
    this->ui->volumetricGLWidget->setHelicoidOffset(ui->doubleSpinboxHelicoidCxMm->value(),value,ui->doubleSpinboxHelicoidCzMm->value());
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxHelicoidYChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxHelicoidZChanged(double value)
{
    this->ui->volumetricGLWidget->setHelicoidOffset(ui->doubleSpinboxHelicoidCxMm->value(),ui->doubleSpinboxHelicoidCyMm->value(),value);
    this->ui->volumetricGLWidget->update();
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinboxObjectSizeChanged
 * @param value
 */
void VolvuxMainWindow::onDoubleSpinboxObjectSizeChanged(double value)
{
    this->ui->volumetricGLWidget->setObjectScale(value);
}

/**
 * @brief VolvuxMainWindow::onPushButtonRandomizeSpheresPressed
 */
void VolvuxMainWindow::onPushButtonRandomizeSpheresPressed()
{
    bool useRandomDots = this->ui->randomDotsCheckBox->isChecked();
    this->ui->volumetricGLWidget->randomizeSpheres(useRandomDots, ui->spinBoxStimulusNSpheres->value(),ui->spinBoxStimulusSpheresRadiusMin->value(),ui->spinBoxStimulusSpheresRadiusMax->value());
}

/**
 * @brief VolvuxMainWindow::on_spinBoxSpheresRadiusMin_valueChanged
 * @param arg1
 */
void VolvuxMainWindow::onSpinboxspheresradiusminValuechanged(int arg1)
{
    if (arg1 >= this->ui->spinBoxStimulusSpheresRadiusMax->value() )
    {
        this->ui->spinBoxStimulusSpheresRadiusMax->setValue(arg1+1);
    }

}

/**
 * @brief VolvuxMainWindow::on_spinBoxSpheresRadiusMax_valueChanged
 * @param arg1
 */
void VolvuxMainWindow::onSpinboxspheresradiusmaxValuechanged(int arg1)
{
    if (arg1 < this->ui->spinBoxStimulusSpheresRadiusMin->value() )
    {
        this->ui->spinBoxStimulusSpheresRadiusMin->setValue(arg1-1);
    }
}

void VolvuxMainWindow::onPushButtonUploadSequenceClicked()
{
    this->ui->statusbar->showMessage("Uploading sequence...",500);
    /*
    try
    {
        int nSlices = this->ui->spinBoxProjectorNSlices->value();
        unsigned char *data = this->ui->volumetricGLWidget->allFrames.data();
        long int pictureTimeMs = helper->getALP()->getMinimumPictureTime();
        if (helper->getALP()->m_bAlpInit)
            this->ui->spinBoxProjectorMicrosecondsPerFrame->setMinimum(pictureTimeMs);
        helper->getALP()->setPicturesTimeus(this->ui->spinBoxProjectorMicrosecondsPerFrame->value());
        helper->getALP()->loadSequence(nSlices,data);
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector",QString(e.what()));
    }
    this->ui->statusbar->showMessage("Sequence successfully uploaded, sequence ID="+QString::number(helper->getALP()->m_AlpSeqDisp),5000);
    this->ui->listWidgetSequences->clear();
    for (unsigned int i=0; i<helper->getALP()->m_AlpSeqId.size(); ++i)
        this->ui->listWidgetSequences->addItem(QString::number(helper->getALP()->m_AlpSeqId.at(i)));
    */
    this->ui->statusbar->showMessage("Sequence uploaded",5000);
}

/**
* @brief onPushButtonProjectorSequenceChanged
**/
void VolvuxMainWindow::onPushButtonProjectorSequenceChanged()
{
    if( ui->listWidgetSequences->selectedItems().isEmpty() )
        return;
    int sequenceToDisplay = ui->listWidgetSequences->currentItem()->text().toLong();

    if (helper->getALP()->m_bAlpInit)
    {
        try
        {
            helper->getALP()->changeSequence(sequenceToDisplay);
            if (helper->getALP()->m_bDisp)
            {
                helper->getALP()->stop();
                helper->getALP()->start();
            }
        }
        catch (const std::exception &e)
        {
            QMessageBox::warning(this,"Error in ALP projector, changing sequence",QString(e.what()));
        }
    }

}

/**
* @brief onPushButtonProjectorRemoveSequencePressed
**/
void VolvuxMainWindow::onPushButtonProjectorRemoveSequencePressed()
{
    if( ui->listWidgetSequences->selectedItems().isEmpty() )
        return;
    int sequenceToRemove = ui->listWidgetSequences->currentItem()->text().toLong();

    if (helper->getALP()->m_bAlpInit)
    {
        try
        {
            if (helper->getALP()->m_bDisp)
                helper->getALP()->stop();
            helper->getALP()->removeSequence(sequenceToRemove);
            this->ui->listWidgetSequences->clear();
            for (unsigned int i=0; i<helper->getALP()->m_AlpSeqId.size(); ++i)
                this->ui->listWidgetSequences->addItem(QString::number(helper->getALP()->m_AlpSeqId.at(i)));
        }
        catch (const std::exception &e)
        {
            QMessageBox::warning(this,"Error in ALP projector, removing sequence",QString(e.what()));
        }
    }

}

/**
 * @brief VolvuxMainWindow::onPushButtonProjectorStartProjectionClicked
 */
void VolvuxMainWindow::onPushButtonProjectorStartProjectionClicked()
{

    try
    {
        if ( this->ui->volumetricGLWidget->width() != PROJECTOR_RESOLUTION_WIDTH &&
             this->ui->volumetricGLWidget->height() != PROJECTOR_RESOLUTION_HEIGHT )
            throw std::runtime_error(std::string("OpenGL widget must have the same resolution of the projector, 1024x768"));
        helper->getALP()->start();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector, starting sequence",QString(e.what()));
    }

}

/**
 * @brief VolvuxMainWindow::onPushButtonProjectorStopProjectionClicked
 */
void VolvuxMainWindow::onPushButtonProjectorStopProjectionClicked()
{
    try
    {
        helper->getALP()->stop();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error in ALP projector",QString(e.what()));
    }
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinBoxSurfaceFirstOrderCoefficientChanged
 * @param val
 */
void VolvuxMainWindow::onDoubleSpinBoxSurfaceFirstOrderCoefficientChanged(double val)
{
    //this->ui->volumetricGLWidget->curvature = val;
}

/**
 * @brief VolvuxMainWindow::onDoubleSpinBoxSurfaceZerothOrderCoefficientChanged
 * @param val
 */
void VolvuxMainWindow::onDoubleSpinBoxSurfaceZerothOrderCoefficientChanged(double val)
{

}

/**
 * @brief VolvuxMainWindow::onDoubleSpinBoxSurfaceSecondOrderCoefficientChanged
 * @param val
 */
void VolvuxMainWindow::onDoubleSpinBoxSurfaceSecondOrderCoefficientChanged(double val)
{

}

/**
 * @brief VolvuxMainWindow::triggerFramesGeneration
 * @param curvature
 */
void VolvuxMainWindow::triggerFramesGeneration(double curvature)
{
    this->onPushButtonProjectorStopProjectionClicked();
    this->onDoubleSpinBoxSurfaceFirstOrderCoefficientChanged(curvature);
    this->onPushButtonGenerateFramesPressed();
    this->onPushButtonUploadSequenceClicked();
    this->onPushButtonProjectorSequenceChanged();
    this->onPushButtonProjectorStartProjectionClicked();
}

/**
 * @brief VolvuxMainWindow::onPushButtonExperimentStartClicked
 * @param clicked
 */
void VolvuxMainWindow::onPushButtonExperimentStartClicked()
{
    this->ui->plainTextExperimentInfo->clear();
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString timeString = time.toString();

    QString subjectName = QInputDialog::getText(this, "Enter Subject name","Subject name:", QLineEdit::Normal);
    if ( subjectName.isEmpty() )
    {
        QMessageBox::warning(this,"Warning","Please set a valid (non-empty) subject name");
        return;
    }

    // Then must initialize the ALP
    /*
    try
    {
        this->ui->checkBoxUseOffscreenRendering->setChecked(true);
        this->ui->volumetricGLWidget->setOffscreenRendering(true);
        this->onPushButtonProjectorInitializeClicked();
        this->ui->spinBoxProjectorLEDcurrent->setValue(this->ui->spinBoxProjectorLEDcurrent->maximum());
        this->ui->doubleSpinBoxProjectorLEDpercentage->setValue(100);
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Warning",QString(e.what()));
        this->onPushButtonProjectorReleaseClicked();
        return;
    }
    */

    exp = new VolvuxExpWidget(NULL);
    exp->setCameraParameters(this->ui->volumetricGLWidget->eyeZ,this->ui->volumetricGLWidget->FOV,this->ui->volumetricGLWidget->zNear,this->ui->volumetricGLWidget->zFar);

    exp->initMonitor(this->ui->monitorResolutionXSpinBox->value(),this->ui->monitorResolutionYSpinBox->value(),
                     this->ui->monitorWidthMMDoubleSpinBox->value(),this->ui->monitorHeightMMDoubleSpinBox->value());

    //QString windowTitle = QString("Volumetric Experiment - ") + date.toString("dd.MM.yyyy") + " " + timeString + " - " + subjectName; exp->setWindowTitle(windowTitle);
    // Fetch experiment parameters
    int nRepetitions = this->ui->repetitionsSpinBox->value();
    int randomize = this->ui->buttonGroupRandomizationMethod->checkedId();
    if (randomize == -1)
    {
        QMessageBox::warning(this,"Warning",QString("Please select a randomization method"));
        return;
    }
	//exp->bal.init(nRepetitions,-randomize-2);
    // Get the list of factors
    vector<double> factorsDepth;
    try
    {
        //factorsDepth = util::str2num<double>(this->ui->factorCurvatureLineEdit->text().toStdString()," ");
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error",e.what());
        return;
    }
    //exp->bal.addFactor("Curvature",factorsDepth);

    //Establish connections
    connect(exp,SIGNAL(trialAdvanced(double)),this->ui->volumetricGLWidget,SLOT(onSurfaceCurvatureChanged(double)));
    connect(exp,SIGNAL(trialAdvanced(double)),this,SLOT(triggerFramesGeneration(double)));
    connect(exp,SIGNAL(getExperimentInfo(const QString &)),this->ui->plainTextExperimentInfo,SLOT(insertPlainText(const QString &)));
    connect(exp,SIGNAL(experimentFinished()),this,SLOT(onPushButtonProjectorReleaseClicked()));
    // Run the experiment
    exp->initializeExperiment();
    exp->show();
}

void VolvuxMainWindow::closeEvent(QCloseEvent *event)
{
    // Ensure clean close of Experiment Widget
    if (exp)
        exp->close();
    //this->onPushButtonProjectorReleaseClicked();
}
