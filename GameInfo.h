
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

  QRectF GameUserView_Size; // ������ ��������������� �������
  QPointF GameUserView_Position; // ��������� ������������ ������������ �������
  int ScrollHorizontal; // ����������� ��������� ����� �� ����������� (-1 - �����, +1 - ������, 0 - ��� ���������)
  int ScrollVertical; // ����������� ��������� ����� �� ��������� (-1 - �����, +1 - ����, 0 - ��� ���������)
  qreal ScrollSpeed; // �������� ���������
  qreal ZoomFactor; // ����������� ��������������� ����������� �������
  long Global_Time; // "�������� ������� ��� ����"
  qreal FramesPerSecond; // FPS ��� ����������� ������� �� ���������� �����
  int FrameTime; // �������� �� ������� ����� �������

// ����� ��������� �������������� ����������:
  int DrawUnitsPath; // ����������� �����, ����������� ������ � ������ �� ��������
};


#endif // GameInfo_H

