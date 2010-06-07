
#include <QtGui>
#include <math.h>
#include "GameInfo.h"
#include "Map.h"
#include "GraphicRender.h"

GraphicRender::GraphicRender(GameInfo *info, QWidget *parent)
 : QWidget(parent)
{
 Info = info;
 Info->GameUserView_Size.setRect(0.0, 0.0, (qreal)width(), (qreal)height());
}

GraphicRender::~GraphicRender()
{
}

QSize GraphicRender::minimumSizeHint() const
{
 return QSize(100, 100);
}

QSize GraphicRender::sizeHint() const
{
 return QSize(1400, 600);
}

void GraphicRender::paintEvent(QPaintEvent * event)
{
/* SetUserView */
 Info->GameUserView_Size.setRect(0.0, 0.0, (qreal)width(), (qreal)height());///

 Info->GameUserView_Position.rx() += Info->ScrollHorizontal*Info->ZoomFactor*Info->ScrollSpeed;
 Info->GameUserView_Position.ry() += Info->ScrollVertical*Info->ZoomFactor*Info->ScrollSpeed;

 if (Info->GameUserView_Position.rx() > Info->Map->Size.width()-Info->GameUserView_Size.width())
   Info->GameUserView_Position.rx() = Info->Map->Size.width()-Info->GameUserView_Size.width();
 if (Info->GameUserView_Position.rx() < 0.0)
   Info->GameUserView_Position.rx() = 0.0;
 if (Info->GameUserView_Position.ry() > Info->Map->Size.height()-Info->GameUserView_Size.height())
   Info->GameUserView_Position.ry() = Info->Map->Size.height()-Info->GameUserView_Size.height();
 if (Info->GameUserView_Position.ry() < 0.0)
   Info->GameUserView_Position.ry() = 0.0;
/* */

 QPainter painter(this);

 painter.setRenderHint(QPainter::Antialiasing, false);
 painter.setPen(palette().dark().color());
 painter.setBrush(QBrush(QColor(0xF2,0xEF,0xE8), Qt::SolidPattern));
 painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

 if (Info->antialiased) painter.setRenderHint(QPainter::Antialiasing, true);

// Отрисовка водоемов
 painter.setPen(QColor(0xBE,0xCD,0xCA));
 painter.setBrush(QBrush(QColor(0xB4,0xD0,0xD1), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Waters->length(); i++)
  {
   painter.drawPolygon((*((*(Info->Map->Waters))[i])).translated(-Info->GameUserView_Position.rx(), -Info->GameUserView_Position.ry()));
  }

// Отрисовка дорог
 painter.setPen(QColor(0xBE,0xBD,0xBB));
 painter.setBrush(QBrush(QColor(0xFF,0xFF,0xFF), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Roads->length(); i++)
  {
   painter.drawPolygon((*((*(Info->Map->Roads))[i])).translated(-Info->GameUserView_Position.rx(), -Info->GameUserView_Position.ry()));
  }

// Отрисовка зданий
 painter.setPen(QColor(0xBE,0xBD,0xBB));
 painter.setBrush(QBrush(QColor(0xBC,0xAA,0xAA), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Buildings->length(); i++)
  {
///   painter.translate(Info->GameUserView_Position.rx(), Info->GameUserView_Position.ry());
   painter.drawPolygon((*((*(Info->Map->Buildings))[i])).translated(-Info->GameUserView_Position.rx(), -Info->GameUserView_Position.ry()));
  }
}

void GraphicRender::Draw()
{
 update();
}

void GraphicRender::mousePressEvent(QMouseEvent *event)
{

}

void GraphicRender::mouseReleaseEvent(QMouseEvent *event)
{

}

void GraphicRender::mouseMoveEvent(QMouseEvent *event)
{

}

