#include <QtGui/QApplication>
#include <QtConcurrentRun>
#include "screenshottaker.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	MainWindow mw;
	mw.setStyleSheet("background-color: transparent");
	mw.setAttribute(Qt::WA_TranslucentBackground);
	mw.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	//mw.setWindowFlags(Qt::FramelessWindowHint);
	mw.show();

	ScreenshotTaker st;
	st.haveNewImage = mw.haveNewImage;
	QObject::connect(&st, SIGNAL(takeScreenshot(QString)), &mw, SLOT(saveScreenshot(QString)), Qt::BlockingQueuedConnection);
	QObject::connect(&st, SIGNAL(sendOCRText(QString)), &mw, SLOT(setOCRText(QString)), Qt::BlockingQueuedConnection);
	//st.view = mw.getView();
	st.start();
	QObject::connect(&app, SIGNAL(aboutToQuit()), &st,  SLOT(stopRunning()));
	/*
    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/liveocr/main.qml"));
    viewer.showExpanded();
	viewer.setStyleSheet("background:transparent");
	viewer.setAttribute(Qt::WA_TranslucentBackground);
	//viewer.setWindowFlags(Qt::FramelessWindowHint);
	*/
	return app.exec();
}
