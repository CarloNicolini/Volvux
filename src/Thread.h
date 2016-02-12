#ifndef THREAD_H
#define THREAD_H

#include <QtCore>
#include "Worker.h"

class Thread : public QThread
{
  Q_OBJECT

public:
  void run(){
    qDebug()<<"From work thread: "<<currentThreadId();
    QTimer timer;
    Worker worker;
    connect(&timer, SIGNAL(timeout()), &worker, SLOT(onTimeout()));
    timer.start(1000);

    exec();
  }

};

#endif // THREAD_H
