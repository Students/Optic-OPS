
#ifndef GameUnit_H
  #define GameUnit_H

  #include <QObject>
  #include <QPainter>
  #include <QList>
  #include <QRectF>
  #include <QImage>

  class GameInfo;
/**
  class Task;
*/
class GameUnit : QObject
{
 public:
  GameInfo *Info;///
  QImage *Sprite;                       // Иконка с изображением объекта (аватара)
  #if 0
  QList<Task> TaskList;			 // Список действий, указанных объекту
  #endif
  int UnitType;                         // Тип юнита - для упрощенных рассчетов (например, отображение на миникарте, выделение юнитов рамкой)
  int MasterID;                         // Идентификатор владельца объекта
  struct
   {
    QRectF *Position;                   // Координаты текущего положения объекта + размеры объекта
/*
    struct ActionDescriptor
     {
      int Type;                 // 0 - ожидание, 1 - движение, 2 - атака
      long TimeLeft;            // Время, прошедшее от начала действия
      QPointF *StartPosition;   // Координаты начала действия
      QPointF *TargetPosition;  // Координаты конца действия
     } Action;				 // Действие, производимое в текущий момент. Используется для анимации действий.
*/
// Список параметров юнита:
    int HitPoints;                      // Здоровье
    int HitPointsMax;                   // Максимальное количество здоровья
    int Speed;                          // Скорость
// Флаги состояния:
    int isDead;                         // Мертв
    int isSelected;                     // Выбран
    int isImmortal;                     // Бессмертен
   } State;

 public:
  GameUnit(GameInfo *info);
  ~GameUnit();
  void Draw(QPainter *painter);         // Отрисовка объекта рисовальщиком
  void DoitSomething(int dtime);        // Выполнение части текущего действия, произведенной за время dtime и переход к следующему действию
  void SetSelection(int selection);     // Изменение состояния избранности юнита
/*{
  void DrawIcon(GraphicScene *gs, QPointF LTpozition, QPointF RBpozition); // Отрисовка иконки с полосой здоровья (в контрольной панели)
  QString *TextInformation();		 ///operator <<  /// Информация о текущем состоянии юнита
}*/
};
// Приказ
class Task
{
 public: /// /private:
  int Type; // Тип приказа
  QPointF TargetPosition; // Положение цели в момент принятия приказа
  GameUnit *TargetUnit; // Цель приказа
};


#endif // GameUnit_H

