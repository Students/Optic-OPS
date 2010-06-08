
#ifndef GameUnitAI_H
  #define GameUnitAI_H

  #include <QObject>

  class GameInfo;

class GameUnitAI : public QObject
{
  Q_OBJECT

 protected:
  GameInfo *Info;

 public:
  GameUnitAI(GameInfo *info);
  ~GameUnitAI();
};

#endif // GameUnitAI_H

