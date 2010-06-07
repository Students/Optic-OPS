
#ifndef GameMap_H
  #define GameMap_H

  #include <QObject>
  #include <QList>
  #include <QPolygonF>

class GameInfo;

class GameMap : public QObject
{
  Q_OBJECT

 public:
  QRectF Size; // Размер локации
  QList<QPolygonF *> *Buildings;
  QList<QPolygonF *> *Roads;
  QList<QPolygonF *> *Waters;

 protected:
  GameInfo *Info;

 public:
  GameMap(GameInfo *info);
  ~GameMap();

  void LoadLocation(QRectF *Location = 0);
};

#endif // GameMap_H

