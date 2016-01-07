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
    void onDoubleSpinboxOffsetXChanged(double);
    void onDoubleSpinboxOffsetYChanged(double);
    void onDoubleSpinboxOffsetZChanged(double);

private:
};

#endif // VOLVUXWIDGETPAGE_H
