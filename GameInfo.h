
#ifndef GameInfo_H
  #define GameInfo_H

  #include <QObject>
  #include <QList>
  #include <QPolygonF>

class GameMap;
class GameUnit;

class GameInfo : QObject
{
  Q_OBJECT

 public:
  GameInfo();
  ~GameInfo();
  void SelectUnitsInArea(QRectF *Area);
  void UnSelectAllUnits();

  GameMap *Map;

  QList<GameUnit *> *GameUnits;         // Игровые объекты (все юниты)
  QList<int> SelectedObjects;           // Индексы выбранных (рамкой) объектов

  bool antialiased;

  QRectF GameUserView_Size;             // Размер просматриваемой области
  QPointF GameUserView_Position;        // Положение отображаемой пользователю области
  QRectF SelectionArea;                 // Охваченная рамкой выделения область
  int ScrollHorizontal;                 // Направление прокрутки карты по горизонтали (-1 - влево, +1 - вправо, 0 - без прокрутки)
  int ScrollVertical;                   // Направление прокрутки карты по вертикали (-1 - вверх, +1 - вниз, 0 - без прокрутки)
  qreal ScrollSpeed;                    // Скорость прокрутки
  qreal ZoomFactor;                     // Коэффициент масштабирования изображения области
  long Global_Time;                     // "Источник времени для всех"
  qreal FramesPerSecond;                // FPS для определения времени до следующего кадра
  int FrameTime;                        // Разность во времени между кадрами

// Флаги рисования дополнительных построений:
  int DrawUnitsPath;                    // Отображение линий, соединяющих юнитов с целями их действий
  int DrawSelection;                    // Флаг процесса выделения объектов рамкой
};

#endif // GameInfo_H

