
#ifndef GameRender_H
  #define GameRender_H

  #include <QObject>

  class GameInfo;

class GameRender : public QObject
{
  Q_OBJECT

 protected:
  GameInfo *Info;
  int TimerID;

 public:
  GameRender(GameInfo *info);
  ~GameRender();
  void Process();

 protected:
  void timerEvent(QTimerEvent *event);
};

#endif // GameRender_H

