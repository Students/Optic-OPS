
#ifndef GameInfo_H
  #define GameInfo_H

  #include <QObject>
  #include <QList>
  #include <QPolygonF>

class GameMap; // Map.h

class GameInfo : QObject
{
  Q_OBJECT

 public:
  GameInfo();
  ~GameInfo();

  GameMap *Map;

  bool antialiased;

  QRectF GameUserView_Size; // Размер просматриваемой области
  QPointF GameUserView_Position; // Положение отображаемой пользователю области
  int ScrollHorizontal; // Направление прокрутки карты по горизонтали (-1 - влево, +1 - вправо, 0 - без прокрутки)
  int ScrollVertical; // Направление прокрутки карты по вертикали (-1 - вверх, +1 - вниз, 0 - без прокрутки)
  qreal ScrollSpeed; // Скорость прокрутки
  qreal ZoomFactor; // Коэффициент масштабирования изображения области
  long Global_Time; // "Источник времени для всех"
  qreal FramesPerSecond; // FPS для определения времени до следующего кадра
  int FrameTime; // Разность во времени между кадрами

// Флаги рисования дополнительных построений:
  int DrawUnitsPath; // Отображение линий, соединяющих юнитов с целями их действий
};


#endif // GameInfo_H

