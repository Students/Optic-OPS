
#include <QPainter>
#include <QList>
#include <QRectF>
#include <QPolygonF>
#include <QImage>
#include <math.h>
#include "Map.h"
#include "GameInfo.h"
#include "GameUnit.h"

GameUnit::GameUnit(GameInfo *info)
{
 Info = info;
 Sprite = 0;
 State.Position = new QRectF(100.0, 100.0, 30.0, 30.0);
 SetSelection(0);
}

GameUnit::~GameUnit()
{
 delete State.Position;
}

void GameUnit::Draw(QPainter *painter)
{
/***/
 // Отрисовка изображения юнита
 painter->setPen(QColor(0xBE,0xBD,0xBB));
 painter->setBrush(QBrush(QColor(0xFF,0xFF,0xFF), Qt::SolidPattern));
 painter->drawPolygon(QPolygonF(*State.Position));
/***/

 if (State.isSelected)
  { // Отрисовка рамки, полоски здоровья и т.п. вокруг юнита

   // Отрисовка рамки
   painter->setPen(QColor(0x00,0xFF,0x00));
   painter->setPen(Qt::DashDotLine);
   painter->setBrush(Qt::NoBrush);
   painter->drawPolygon(QPolygonF(*State.Position));
  }
}

void GameUnit::DoitSomething(int dtime)
{
/***/
 qreal T = (qreal)( dtime%100 )/100.0*6.283;
 if (   State.Position->x()+State.Position->width()<Info->Map->Size.width()
     && State.Position->y()+State.Position->height()<Info->Map->Size.height())
  {
   State.Position->translate(-1.0*cos(T) + T, 1.0*sin(T) + T);
  }
/***/
}

void GameUnit::SetSelection(int selection)
{
 State.isSelected = selection;
}


