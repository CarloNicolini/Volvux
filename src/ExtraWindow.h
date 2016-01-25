#ifndef EXTRAWINDOW_H
#define EXTRAWINDOW_H

#include <QWidget>
#include "ProjectorWidgetPage.h"
#include "VolvuxWidget.h"

namespace Ui {
  class ExtraWindow;
}

class ExtraWindow : public QWidget
{
  Q_OBJECT

public:
  explicit ExtraWindow(QWidget *parent = 0);
  ~ExtraWindow();

private:
  Ui::ExtraWindow *ui;
  QWidget *grabbedWidget;

public slots:
  void receiveWidget(ProjectorWidgetPage *projectorMotorSettings);
  void receiveWidget(VolvuxWidget *helicoidWidget);
};

#endif // EXTRAWINDOW_H
