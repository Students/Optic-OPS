
#include <QtGui>
#include <math.h>
#include "GameInfo.h"
#include "ControlPanel.h"

ControlPanel::ControlPanel(GameInfo *info, QWidget *parent)
 : QWidget(parent)
{
 Info = info;
}

ControlPanel::~ControlPanel()
{
}

QSize ControlPanel::minimumSizeHint() const
{
 return QSize(100, 100);
}

QSize ControlPanel::sizeHint() const
{
 return QSize(1400, 200);
}

void ControlPanel::paintEvent(QPaintEvent * /* event */)
{

}

void ControlPanel::mousePressEvent(QMouseEvent *event)
{
 if (event->buttons() & Qt::LeftButton) {} // Start select (position_on_screen + view_position)
 else if (event->buttons() & Qt::RightButton) {} // Send order
}

void ControlPanel::mouseReleaseEvent(QMouseEvent *event)
{
 if (event->buttons() & Qt::LeftButton) {} // End select (position_on_screen + view_position)
 else if (event->buttons() & Qt::RightButton) {} /// Order sended
}

void ControlPanel::mouseMoveEvent(QMouseEvent *event)
{

}

