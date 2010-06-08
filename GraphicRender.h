
#ifndef GraphicRender_H
  #define GraphicRender_H

  #include <QWidget>

  class GameInfo;

class GraphicRender : public QWidget
{
  Q_OBJECT

 protected:
  GameInfo *Info;
  int TimerID;
  bool antialiased;

 public:
  GraphicRender(GameInfo *info, QWidget *parent = 0);
  ~GraphicRender();
  void Draw();

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

 protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
};

#endif // GraphicRender_H

