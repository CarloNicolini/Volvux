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

#include <QtGui>
#include <QtOpenGL>
#include "VolvuxCalibrationWidget.h"
#ifdef __APPLE__
QString CNCSVISION_BASE_DIRECTORY("/Users/rs/workspace/");
#endif

#ifdef __linux__
//QString CNCSVISION_BASE_DIRECTORY("/home/carlo/workspace/");
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

/**
 * @brief ShaderWidget::ShaderWidget
 * @param parent
 * @param shareWidget
 */
VolvuxCalibrationWidget::VolvuxCalibrationWidget(QWidget *parent)
{
    // Get the 2D points and 3D points
    //this->setAutoBufferSwap(true);
    this->setMouseTracking(true);
    this->setAutoFillBackground(false);
    this->setCursor(Qt::BlankCursor);
    this->resize(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT);
    glPointSize(0.1);
    QTimer *timer = new QTimer(this);
    timer->start(10);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    this->setFocus();
    drawingText=true;

	this->alp = new ALPProjector();

}

void VolvuxCalibrationWidget::moveCursor(int x, int y)
{
    this->lastPoint.setX(this->lastPoint.x()+x);
    this->lastPoint.setY(this->lastPoint.y()+y);
}

/**
 * @brief ShaderWidget::~ShaderWidget
 */
VolvuxCalibrationWidget::~VolvuxCalibrationWidget()
{
	delete alp;
}

/**
 * @brief ShaderWidget::minimumSizeHint
 * @return
 */
QSize VolvuxCalibrationWidget::minimumSizeHint() const
{
    return QSize(PROJECTOR_RESOLUTION_WIDTH, PROJECTOR_RESOLUTION_HEIGHT);
}

/**
 * @brief ShaderWidget::sizeHint
 * @return
 */
QSize VolvuxCalibrationWidget::sizeHint() const
{
    return QSize(PROJECTOR_RESOLUTION_WIDTH, PROJECTOR_RESOLUTION_HEIGHT);
}

/**
 * @brief ShaderWidget::saveData
 */
void VolvuxCalibrationWidget::saveData()
{
    QString filename = QFileDialog::getSaveFileName(this,"Select points output file name", QDir::currentPath());
    QFileInfo outputfile(filename);

    filename.replace("."+outputfile.suffix(),"");
    QString pointsOutputFileName = filename + ".txt";
    QString imageOutputFileName  = filename + ".bmp";


    //    QImage frame = this->grabFrameBuffer();
    //    if ( !frame.save(imageOutputFileName,NULL,-1) )
    //    {
    //        QMessageBox::warning(this,"Error saving image","Can't save image");
    //    }

    //    QFile outputFile(pointsOutputFileName);
    //    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    //    QTextStream out(&outputFile);

    //    //outputPoints.open(pointsOutputFileName.toStdString().c_str());
    //    out << "# Calibration points" << endl;
    //    for (int i=0; i<points2D.size();i++)
    //    {
    //        out << points2D.at(i).x() << "\t" << points2D.at(i).y() << endl;
    //    }
}

/**
 * @brief CalibrationWidget::mouseMoveEvent
 * @param event
 */
void VolvuxCalibrationWidget::mouseMoveEvent(QMouseEvent *event)
{
    lastPoint = QPoint(event->x() ,event->y());
}

/**
 * @brief CalibrationWidget::mouseMoveEvent
 * @param event
 */
void VolvuxCalibrationWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton )
    {
        // Search if the point already exists remove it
        lastPoint = QPoint(event->x() ,event->y());
        addPoint();
    }
}

/**
 * @brief ShaderWidget::paintGL
 */
void VolvuxCalibrationWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(QRect(QPoint(0,0),QPoint(PROJECTOR_RESOLUTION_WIDTH,PROJECTOR_RESOLUTION_HEIGHT)),Qt::black);
    painter.setPen(Qt::white);

    painter.drawPoint(lastPoint);
    painter.drawLine(lastPoint-QPoint(3,0),lastPoint+QPoint(3,0));
    painter.drawLine(lastPoint-QPoint(0,3),lastPoint+QPoint(0,3));

    for (int i=0; i< this->points2D.size();i++)
    {
        painter.drawPoint(points2D.at(i));
        painter.drawEllipse(points2D.at(i),6,6);
        painter.drawLine(points2D.at(i)-QPoint(3,0),points2D.at(i)+QPoint(3,0));
        painter.drawLine(points2D.at(i)-QPoint(0,3),points2D.at(i)+QPoint(0,3));
    }

    painter.drawPoint(PROJECTOR_RESOLUTION_WIDTH/2,PROJECTOR_RESOLUTION_HEIGHT/2);

    if ( drawingText )
    {
        painter.drawText(40,PROJECTOR_RESOLUTION_HEIGHT-20,QString("(x,y)=(")+ QString::number(lastPoint.x())+","+QString::number(lastPoint.y())+")");
                painter.drawText(800,PROJECTOR_RESOLUTION_HEIGHT-20,QString("(x,y)=(")+ QString::number(lastPoint.x()-PROJECTOR_RESOLUTION_WIDTH/2)+","+QString::number(lastPoint.y()-PROJECTOR_RESOLUTION_HEIGHT/2)+")");
        //painter.drawText(80,PROJECTOR_RESOLUTION_HEIGHT-20,QString::number(lastPoint.y()));
        painter.drawText(120,PROJECTOR_RESOLUTION_HEIGHT-60,"Press S to select the output file name");
        painter.drawText(120,PROJECTOR_RESOLUTION_HEIGHT-80,"Press Q to quit and save");
        painter.drawText(120,PROJECTOR_RESOLUTION_HEIGHT-100,"RightMouse to save/erase points");
        painter.drawText(120,PROJECTOR_RESOLUTION_HEIGHT-120,"Press T to toggle this text");
        painter.drawText(120,PROJECTOR_RESOLUTION_HEIGHT-140,"Press R to save this point");

        QRect rect;
        QPen pen; pen.setWidth(1);pen.setColor(Qt::white);
        painter.setPen(pen);
        rect.setTopLeft(QPoint(0,0));
        rect.setBottomRight(QPoint(PROJECTOR_RESOLUTION_WIDTH-1,PROJECTOR_RESOLUTION_HEIGHT-1));
        painter.drawRect(rect);
    }
    painter.end();

    // Copy the current frame to the projector so that it can display it

	QImage frame;// = this->grabFrameBuffer();
    try
    {
        alp->stop();
        alp->cleanAllSequences();
        alp->loadSequence(1, frame.convertToFormat(QImage::Format_Mono).bits());
        alp->start();
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this,"Error streaming data to projector", e.what());
    }

}

/**
 * @brief VolvuxCalibrationWidget::toggleText
 */
void VolvuxCalibrationWidget::toggleText()
{
    this->drawingText = !this->drawingText;
}

/**
 * @brief VolvuxCalibrationWidget::addPoint
 */
void VolvuxCalibrationWidget::addPoint()
{
    for (int i=0; i<points2D.size();i++)
    {
        if (lastPoint == points2D.at(i))
        {
            points2D.remove(i);
            emit pointRemoved(lastPoint);
            //qDebug() << "Removed  " << lastPoint ;
            return;
        }
    }
    //qDebug() << "Added " << lastPoint;
    ;
    emit lastPointPressed(lastPoint);
    this->points2D.push_back(lastPoint);
}
