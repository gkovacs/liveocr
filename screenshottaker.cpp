#include "screenshottaker.h"
#include <stdio.h>
#include <QPixmap>
#include <tesseract/ocrclass.h>

ScreenshotTaker::ScreenshotTaker()
{
	running = true;
	api.Init("/usr/share/tesseract-ocr/", "chi_sim");
	api.SetPageSegMode(tesseract::PSM_AUTO);
	qDebug() << "tesseract initialized";
}

void ScreenshotTaker::run()
{
	while (running)
	{
		takeScreenshot("/home/geza/Desktop/output1.png");

		if (!(*haveNewImage))
		{
			//qDebug() << "no change";
			continue;
		}

		//qDebug() << "new image";

		PIX *pixs = pixRead("/home/geza/Desktop/output1.png");
		api.SetImage(pixs);
		ETEXT_DESC monitor;
		monitor.set_deadline_msecs(1000); // times out in a second
		api.Recognize(&monitor);
		char* output = api.GetUTF8Text();
		QString outputText = QString::fromUtf8(output);
		//qDebug() << outputText;
		sendOCRText(outputText);

		delete[] output;
		pixDestroy(&pixs);

		//QPixmap screenshot = QPixmap::grabWidget(view, 0, 0, view->width(), view->height());
		//screenshot.save("/home/geza/Desktop/output1.png", "png");
	}
}

void ScreenshotTaker::stopRunning()
{
	running = false;
}
