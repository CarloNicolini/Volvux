#ifndef SETTINGSWINDOWWIDGET_H
#define SETTINGSWINDOWWIDGET_H

#include <QWidget>

namespace Ui {
class SettingsWindowWidget;
}

class SettingsWindowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindowWidget(QWidget *parent = 0);
    ~SettingsWindowWidget();
    void receiveWidget(QWidget *widget);

private:
    Ui::SettingsWindowWidget *ui;
    QWidget *grabbedWidget;

};

#endif // SETTINGSWINDOWWIDGET_H
