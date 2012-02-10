#ifndef SCREENSHOTTAKER_H
#define SCREENSHOTTAKER_H

#include <QtCore>
#include <QThread>
#include <QGraphicsView>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class ScreenshotTaker : public QThread
{
    Q_OBJECT
public:
	ScreenshotTaker();
	void run();
	bool *haveNewImage;

signals:
	void takeScreenshot(QString);
	void sendOCRText(QString);

public slots:
	void stopRunning();

private:
	bool running;
	tesseract::TessBaseAPI api;

};

#endif // SCREENSHOTTAKER_H
