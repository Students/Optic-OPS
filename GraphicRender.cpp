
#include <QtGui>
#include <math.h>
#include "GameInfo.h"
#include "Map.h"
#include "GameUnit.h"
#include "GraphicRender.h"

GraphicRender::GraphicRender(GameInfo *info, QWidget *parent)
 : QWidget(parent)
{
 Info = info;
 Info->GameUserView_Size.setRect(0.0, 0.0, (qreal)width(), (qreal)height());
 TimerID = startTimer(Info->FrameTime);
}

GraphicRender::~GraphicRender()
{
 killTimer(TimerID);
}

QSize GraphicRender::minimumSizeHint() const
{
 return QSize(100, 100);
}

QSize GraphicRender::sizeHint() const
{
 return QSize(1400, 600);
}

void GraphicRender::paintEvent(QPaintEvent * /* event */)
{
 long CurrentFrameTime = Info->Global_Time; // Значение времени для рендеринга текущего кадра
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

 painter.save();
 painter.translate(-Info->GameUserView_Position.rx(), -Info->GameUserView_Position.ry());

// Отрисовка водоемов
 painter.setPen(QColor(0xBE,0xCD,0xCA));
 painter.setBrush(QBrush(QColor(0xB4,0xD0,0xD1), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Waters->length(); i++)
  {
   painter.drawPolygon((*((*(Info->Map->Waters))[i])));
  }

// Отрисовка дорог
 painter.setPen(QColor(0xBE,0xBD,0xBB));
 painter.setBrush(QBrush(QColor(0xFF,0xFF,0xFF), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Roads->length(); i++)
  {
   painter.drawPolygon((*((*(Info->Map->Roads))[i])));
  }

// Отрисовка зданий
 painter.setPen(QColor(0xBE,0xBD,0xBB));
 painter.setBrush(QBrush(QColor(0xBC,0xAA,0xAA), Qt::SolidPattern));
 for (int i=0; i<Info->Map->Buildings->length(); i++)
  {
   painter.drawPolygon((*((*(Info->Map->Buildings))[i])));
  }

// Отрисовка юнитов
 for (int i=0; i<Info->GameUnits->length(); i++)
  {
   painter.save();
   ((*(Info->GameUnits))[i])->Draw(&painter);
   painter.restore();
  }

 painter.restore();

// Отрисовка рамки выделения
 painter.setRenderHint(QPainter::Antialiasing, false);
 if (Info->DrawSelection == 1)
  {
   painter.setPen(QColor(0xF0,0x80,0x80));
   painter.setPen(Qt::DashDotLine);
   painter.setBrush(Qt::NoBrush);
   painter.drawRect(Info->SelectionArea);
  }

/***/
 painter.setPen(QColor(0x00,0xFF,0x00));
 painter.setBrush(Qt::NoBrush);
 painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
/***/
}

void GraphicRender::timerEvent(QTimerEvent *event)
{
 Draw();
}

void GraphicRender::Draw()
{
 update();
}

void GraphicRender::mousePressEvent(QMouseEvent *event)
{
 if (event->buttons() & Qt::LeftButton)
  { // Начало выделения группы объектов
   Info->UnSelectAllUnits();
   Info->SelectionArea.setRect(event->x(), event->y(), 0.0, 0.0);
   Info->SelectUnitsInArea(&Info->SelectionArea);
   Info->DrawSelection = 1;
  }
 else if (event->buttons() & Qt::RightButton) {} /// Send order
}

void GraphicRender::mouseReleaseEvent(QMouseEvent *event)
{
/// if (event->buttons() & Qt::LeftButton)
  {
   if (Info->DrawSelection)
    { // Конец выделения группы объектов
     Info->DrawSelection = 0;
     Info->SelectionArea.setRect(Info->SelectionArea.x(), Info->SelectionArea.y(), event->x()-Info->SelectionArea.x(), event->y()-Info->SelectionArea.y());
    }
  }
}

void GraphicRender::mouseMoveEvent(QMouseEvent *event)
{
 if (event->buttons() & Qt::LeftButton)
  { // Изменение рамки выделения
   Info->SelectionArea.setRect(Info->SelectionArea.x(), Info->SelectionArea.y(), event->x()-Info->SelectionArea.x(), event->y()-Info->SelectionArea.y());
   Info->SelectUnitsInArea(&Info->SelectionArea);
  }
}


