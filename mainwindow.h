#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	QGraphicsView* getView();
	//bool eventFilter(QObject *obj, QEvent *event);
	void mousePressEvent (QMouseEvent * event);
	void mouseReleaseEvent (QMouseEvent * event);
	bool haveNewImageData;
	bool *haveNewImage;
	bool isMouseGrabbed;
	QPoint pressPoint;
	QWidget selectionRegion;
	//QGraphicsOpacityEffect opacityEffect;

public slots:
	void saveScreenshot(QString outputPath);
	void setOCRText(QString ocrText);
	void shortcutPressed();
	void mousePressSlot(QMouseEvent *event);
	void mouseReleaseSlot(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	Ui::MainWindow *ui;
	QImage prevImg;
	QShortcut *shortcut;
};

#endif // MAINWINDOW_H
