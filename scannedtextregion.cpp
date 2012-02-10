#include "scannedtextregion.h"

ScannedTextRegion::ScannedTextRegion(QWidget *parent) :
	QGraphicsView(parent)
{
}

void ScannedTextRegion::mousePressEvent (QMouseEvent * event)
{
	mousePressed(event);
}

void ScannedTextRegion::mouseReleaseEvent (QMouseEvent * event)
{
	mouseReleased(event);
}
