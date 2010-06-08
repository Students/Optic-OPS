
#include <QList>
#include <QPolygonF>
#include <math.h>
#include "GameInfo.h"
#include "Map.h"

GameMap::GameMap(GameInfo *info)
{
 Info = info;
 Size.setRect(0.0, 0.0, 3000.0,3000.0); /// ”казать размеры области (всей карты)
 Buildings = new QList<QPolygonF *>;
 Roads     = new QList<QPolygonF *>;
 Waters    = new QList<QPolygonF *>;

 /// «десь должна быть инициализаци€ матрицы загруженных секторов карты

 LoadLocation();
}

GameMap::~GameMap()
{

}

void GameMap::LoadLocation(QRectF *Location)
{
 if (!Location)
  { // «агрузка всей карты
/***/
   for (int j=0; j<3; j++)
     for (int i=0; i<4; i++)
      {
       QPolygonF *poly = new QPolygonF;
       (*poly) << QPointF(200.0+200.0*i, 200.0+100.0*j) << QPointF(375.0+200.0*i, 200.0+100.0*j)
               << QPointF(375.0+200.0*i, 275.0+100.0*j) << QPointF(200.0+200.0*i, 275.0+100.0*j);
       Buildings->append(poly);
      }
   {
    QPolygonF *poly = new QPolygonF;
    (*poly) << QPointF(0.0,  0.0) << QPointF(1000.0, 2000.0) << QPointF(3000.0, 3000.0)
            << QPointF(3000.0, 3070.0) << QPointF(1000.0, 2070.0) << QPointF(0.0, 70.0);
    Roads->append(poly);
   }
   {
    QPolygonF *poly = new QPolygonF;
    (*poly) << QPointF(0.0, 2930.0) << QPointF(2000.0, 2300.0) << QPointF(3000.0, 0.0)
            << QPointF(3000.0, 70.0) << QPointF(2000.0, 2370.0) << QPointF(0.0, 3000.0);
    Waters->append(poly);
   }
/***/
  }
 else
  {
   /// «десь должна быть загрузка требуемой части карты
  }
}

