#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "Thread.h"

class Worker : public QObject
{

  Q_OBJECT

public slots:
  void getSMIAbsPosition();


};

#endif // WORKER_H
