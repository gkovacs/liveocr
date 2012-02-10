#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	haveNewImageData = true;
	haveNewImage = &haveNewImageData;
	isMouseGrabbed = false;

	shortcut = new QShortcut(this);
	shortcut->setKey(QKeySequence(Qt::Key_F7));
	connect(shortcut, SIGNAL(activated()), this, SLOT(shortcutPressed()));
	connect(shortcut, SIGNAL(activatedAmbiguously()), this, SLOT(shortcutPressed()));

	connect(ui->graphicsView, SIGNAL(mousePressed(QMouseEvent*)), this, SLOT(mousePressSlot(QMouseEvent*)));
	connect(ui->graphicsView, SIGNAL(mouseReleased(QMouseEvent*)), this, SLOT(mouseReleaseSlot(QMouseEvent*)));

	selectionRegion.setStyleSheet("background-color: blue");
	selectionRegion.setWindowOpacity(0.3);
	selectionRegion.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);

	this->pressPoint.setX(0);
	this->pressPoint.setY(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shortcutPressed()
{
	qDebug() << "shortcut pressed";
	if (isMouseGrabbed)
	{
		isMouseGrabbed = false;
		this->releaseMouse();
	}
	else
	{
		isMouseGrabbed = true;
		this->grabMouse();
	}
}

QGraphicsView* MainWindow::getView()
{
	return ui->graphicsView;
}

void MainWindow::saveScreenshot(QString outputPath)
{
	QWidget *view = getView();
	//QPixmap screenshot = QPixmap::grabWidget(view, 0, 0, view->width(), view->height());
	QPoint start = view->mapToGlobal(QPoint(0, 0));
	QPixmap screenshot = QPixmap::grabWindow(QApplication::desktop()->winId(), start.x(), start.y(), view->width(), view->height());
	QImage curImg = screenshot.toImage();
	if (curImg == prevImg)
	{
		*haveNewImage = false;
		return;
	}
	*haveNewImage = true;
	prevImg = curImg;
	screenshot.save(outputPath, "png", 100);
}

void MainWindow::setOCRText(QString ocrText)
{
	ui->lineEdit->setText(ocrText);
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "mouse pressed";
	pressPoint.setX(event->globalX());
	pressPoint.setY(event->globalY());
	if (isMouseGrabbed)
	{
		selectionRegion.resize(0, 0);
		selectionRegion.move(pressPoint);
		selectionRegion.show();
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
	selectionRegion.hide();
	qDebug() << "mouse released";
	if (isMouseGrabbed)
	{
		isMouseGrabbed = false;
		this->releaseMouse();
		int newWidth = event->globalX() - pressPoint.x();
		int newHeight = event->globalY() - pressPoint.y();
		if (newWidth <= 5 || newHeight <= 5)
		{
			return;
		}
		QPoint windowZeroCoord = this->mapToGlobal(QPoint(0,0));
		QPoint frameZeroCoord = ui->graphicsView->mapToGlobal(QPoint(0,0));
		QPoint offsetPoint = frameZeroCoord - windowZeroCoord;
		int widthDifference = this->width() - ui->graphicsView->width();
		int heightDifferece = this->height() - ui->graphicsView->height();
		this->move(pressPoint - offsetPoint);
		this->resize(newWidth + widthDifference, newHeight + heightDifferece);
	}
	else
	{
		if (event->button() == Qt::RightButton)
		{
			isMouseGrabbed = true;
			this->grabMouse();
			return;
		}
	}
}

void MainWindow::mousePressSlot(QMouseEvent * event)
{
	mousePressEvent(event);
}

void MainWindow::mouseReleaseSlot(QMouseEvent * event)
{
	mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (!selectionRegion.isVisible())
		return;
	int newWidth = event->globalX() - pressPoint.x();
	int newHeight = event->globalY() - pressPoint.y();
	selectionRegion.resize(newWidth, newHeight);
}
