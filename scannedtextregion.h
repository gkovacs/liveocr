#ifndef SCANNEDTEXTREGION_H
#define SCANNEDTEXTREGION_H

#include <QtCore>
#include <QtGui>

class ScannedTextRegion : public QGraphicsView
{
    Q_OBJECT
public:
	ScannedTextRegion(QWidget *parent = 0);
	void mousePressEvent (QMouseEvent * event);
	void mouseReleaseEvent (QMouseEvent * event);

signals:
	void mousePressed(QMouseEvent *event);
	void mouseReleased(QMouseEvent *event);

public slots:

};

#endif // SCANNEDTEXTREGION_H
