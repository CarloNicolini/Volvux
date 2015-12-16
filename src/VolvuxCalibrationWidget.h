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

#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QtGui>
#include <QGLWidget>

#include <fstream>
#include <Eigen/Core>

#include "ALPProjector.h"
#include "CalibrationWidgetPage.h"

#ifdef ALP_SUPPORT
#include "ALPProjector.h"
#endif

//#define ALP_SUPPORT
using Eigen::Vector3d;

class VolvuxCalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    VolvuxCalibrationWidget(QWidget *parent = 0);
    ~VolvuxCalibrationWidget();
    void setALP(ALPProjector *alp);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void saveData();
    void toggleText();
    void moveCursor(int x,int y);
    void addPoint();

signals:
    void lastPointPressed(const QPoint &p);
    void pointRemoved(const QPoint &p);
    void points2Dupdated(const QVector<QPoint> &);

public slots:
    void transferFrame();

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QVector<QPoint> points2D;
    bool drawingText;
    QPoint lastPoint;
    std::ofstream outputPoints;

    ALPProjector *alp;

};

#endif
