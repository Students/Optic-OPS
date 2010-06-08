
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

  QList<GameUnit *> *GameUnits;         // ������� ������� (��� �����)
  QList<int> SelectedObjects;           // ������� ��������� (������) ��������

  bool antialiased;

  QRectF GameUserView_Size;             // ������ ��������������� �������
  QPointF GameUserView_Position;        // ��������� ������������ ������������ �������
  QRectF SelectionArea;                 // ���������� ������ ��������� �������
  int ScrollHorizontal;                 // ����������� ��������� ����� �� ����������� (-1 - �����, +1 - ������, 0 - ��� ���������)
  int ScrollVertical;                   // ����������� ��������� ����� �� ��������� (-1 - �����, +1 - ����, 0 - ��� ���������)
  qreal ScrollSpeed;                    // �������� ���������
  qreal ZoomFactor;                     // ����������� ��������������� ����������� �������
  long Global_Time;                     // "�������� ������� ��� ����"
  qreal FramesPerSecond;                // FPS ��� ����������� ������� �� ���������� �����
  int FrameTime;                        // �������� �� ������� ����� �������

// ����� ��������� �������������� ����������:
  int DrawUnitsPath;                    // ����������� �����, ����������� ������ � ������ �� ��������
  int DrawSelection;                    // ���� �������� ��������� �������� ������
};

#endif // GameInfo_H

