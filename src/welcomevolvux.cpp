#include <QDesktopWidget>
#include <QApplication>
#include "StackedWidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StackedWidget stacked;
    stacked.show();
    return app.exec();
}
