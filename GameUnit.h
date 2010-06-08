
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
  QImage *Sprite;                       // ������ � ������������ ������� (�������)
  #if 0
  QList<Task> TaskList;			 // ������ ��������, ��������� �������
  #endif
  int UnitType;                         // ��� ����� - ��� ���������� ��������� (��������, ����������� �� ���������, ��������� ������ ������)
  int MasterID;                         // ������������� ��������� �������
  struct
   {
    QRectF *Position;                   // ���������� �������� ��������� ������� + ������� �������
/*
    struct ActionDescriptor
     {
      int Type;                 // 0 - ��������, 1 - ��������, 2 - �����
      long TimeLeft;            // �����, ��������� �� ������ ��������
      QPointF *StartPosition;   // ���������� ������ ��������
      QPointF *TargetPosition;  // ���������� ����� ��������
     } Action;				 // ��������, ������������ � ������� ������. ������������ ��� �������� ��������.
*/
// ������ ���������� �����:
    int HitPoints;                      // ��������
    int HitPointsMax;                   // ������������ ���������� ��������
    int Speed;                          // ��������
// ����� ���������:
    int isDead;                         // �����
    int isSelected;                     // ������
    int isImmortal;                     // ����������
   } State;

 public:
  GameUnit(GameInfo *info);
  ~GameUnit();
  void Draw(QPainter *painter);         // ��������� ������� �������������
  void DoitSomething(int dtime);        // ���������� ����� �������� ��������, ������������� �� ����� dtime � ������� � ���������� ��������
  void SetSelection(int selection);     // ��������� ��������� ����������� �����
/*{
  void DrawIcon(GraphicScene *gs, QPointF LTpozition, QPointF RBpozition); // ��������� ������ � ������� �������� (� ����������� ������)
  QString *TextInformation();		 ///operator <<  /// ���������� � ������� ��������� �����
}*/
};
// ������
class Task
{
 public: /// /private:
  int Type; // ��� �������
  QPointF TargetPosition; // ��������� ���� � ������ �������� �������
  GameUnit *TargetUnit; // ���� �������
};


#endif // GameUnit_H

