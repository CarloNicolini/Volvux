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

#ifndef VOLVUX_MAIN_WINDOW_H_
#define VOLVUX_MAIN_WINDOW_H_

#include <QtGui>
#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <stdexcept>

#include "VolvuxExpWidget.h"
#include "StackedWidgetHelper.h"
#include "CalibrationHelper.h"

#include "ui_VolvuxMainWindow.h"

#ifdef SMI_SUPPORT
#import "IntegMotorInterface.tlb"
#include "SMIDefs.h"
#include <comdef.h>
#endif

namespace Ui
{
class VolvuxMainWindow;
}

class VolvuxMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VolvuxMainWindow(QWidget *parent = 0);
    ~VolvuxMainWindow();
    void setStackedWidgetHelper(StackedWidgetHelper* swhelper);
    void setCalibrationHelper(CalibrationHelper *calib);
protected:
    void keyPressEvent(QKeyEvent *event) ;
    bool eventFilter(QObject *, QEvent *) ;
    void closeEvent(QCloseEvent *event) ;

private slots:
    // Scene slots
    void onDoubleSpinboxObjectSizeChanged(double value);
    void onDoubleSpinboxOffsetXChanged(double value);
    void onDoubleSpinboxOffsetYChanged(double value);
    void onDoubleSpinboxOffsetZChanged(double value);
    void onDoubleSpinboxHelicoidXChanged(double value);
    void onDoubleSpinboxHelicoidYChanged(double value);
    void onDoubleSpinboxHelicoidZChanged(double value);
    void onPushButtonRandomizeSpheresPressed();
    void onSpinboxspheresradiusminValuechanged(int arg1);
    void onSpinboxspheresradiusmaxValuechanged(int arg1);
    void onPushButtonGenerateFramesPressed();
    void onPushButtonProjectorSequenceChanged();
    void onPushButtonProjectorRemoveSequencePressed();
    void onPushButtonLoadBinVoxPressed();

    void onDoubleSpinBoxSurfaceZerothOrderCoefficientChanged(double val);
    void onDoubleSpinBoxSurfaceFirstOrderCoefficientChanged(double val);
    void onDoubleSpinBoxSurfaceSecondOrderCoefficientChanged(double val);

    // Projector initialization/release/start/stop slots
    void onPushButtonProjectorStartProjectionClicked();
    void onPushButtonProjectorStopProjectionClicked();
    void onPushButtonUploadSequenceClicked();

    // Experiment slots
    void onPushButtonExperimentStartClicked();
    void triggerFramesGeneration(double curvature);
    void onRandomizationMethodChanged(int randomVal);

    // Calibration slots
    void onCalibrationEmitted(CameraDirectLinearTransformation &cam);
private:
    void initializeTabSceneQConnections();
    void initializeTabProjectorQConnections();
    void initializeTabExperimentQConnections();
    void loadSettings();
    void saveSettings();

    Ui::VolvuxMainWindow *ui;
    QPointer<VolvuxExpWidget> exp;

    StackedWidgetHelper *helper;
    CalibrationHelper *calib;

#if defined (SMI_SUPPORT) && (WIN32)
    INTEGMOTORINTERFACELib::ISMICommPtr CommInterface;
#endif
#ifdef COMPILE_GLFW
    int monitorResolutionX;
    int monitorResolutionY;
    int monitorWidthMM;
    int monitorHeightMM;
#endif
};

#endif
