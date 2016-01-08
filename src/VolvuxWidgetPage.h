#ifndef VOLVUXWIDGETPAGE_H
#define VOLVUXWIDGETPAGE_H

#include <QWidget>

namespace Ui {
class VolvuxWidgetPage;
}

class VolvuxWidgetPage : public QWidget
{
    Q_OBJECT

public:
    explicit VolvuxWidgetPage(QWidget *parent = 0);
    ~VolvuxWidgetPage();
    Ui::VolvuxWidgetPage *ui;

public slots:
    void onDoubleSpinboxOffsetChanged(double);
    void onDoubleSpinboxHelicoidChanged(double);
    void onDoubleSpinboxObjectSizeChanged(double);


private:
};

#endif // VOLVUXWIDGETPAGE_H
