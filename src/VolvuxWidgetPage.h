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


signals:
    void writeOnStatusBar(QString message,int time);

public slots:
    void onDoubleSpinboxOffsetChanged(double);
    void onDoubleSpinboxHelicoidChanged(double);
    void onDoubleSpinboxObjectSizeChanged(double);
    void onPushButtonRandomizeSpheresPressed();
    void onPushButtonGenerateFramesPressed();
	void onDoubleSpinboxSurfaceThicknessChanged(double);
	void onDoubleSpinboxSurfaceCurvatureChanged(double);

	// Projector actions
	void onPushButtonStartProjectionPressed();
	void onPushButtonStopProjectionPressed();
};

#endif // VOLVUXWIDGETPAGE_H
