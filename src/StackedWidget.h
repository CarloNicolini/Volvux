#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>

namespace Ui {
class StackedWidget;
}

class StackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = 0);
    ~StackedWidget();

private slots:
    void onPushButtonNextStackedWidget(bool value);
    void onPushButtonPreviousStackedWidget(bool value);
    void onCancelPressed(bool value);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::StackedWidget *ui;
};

#endif // STACKEDWIDGET_H
