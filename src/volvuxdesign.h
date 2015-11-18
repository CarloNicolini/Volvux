#ifndef VOLVUXDESIGN_H
#define VOLVUXDESIGN_H

#include <QMainWindow>

namespace Ui {
class VolvuxDesign;
}

class VolvuxDesign : public QMainWindow
{
    Q_OBJECT

public:
    explicit VolvuxDesign(QWidget *parent = 0);
    ~VolvuxDesign();

private:
    Ui::VolvuxDesign *ui;
};

#endif // VOLVUXDESIGN_H
