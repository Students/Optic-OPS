
#ifndef GameMainWindow_H
  #define GameMainWindow_H

  #include <QWidget>

  class GameInfo;
  class GraphicRender;
  class ControlPanel;

class MainWindow : public QWidget
{
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

 protected:
  GameInfo *Info;
  GraphicRender *Render;
  ControlPanel *Panel;
  int TimerID;

  void timerEvent(QTimerEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void mouseMoveEvent(QMouseEvent *event);
};

#endif // GameMainWindow_H

