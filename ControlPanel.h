
#ifndef ControlPanel_H
  #define ControlPanel_H

  #include <QWidget>

  #include "GameInfo.h"

class ControlPanel : public QWidget
{
  Q_OBJECT

 public:
  ControlPanel(GameInfo *info, QWidget *parent = 0);
  ~ControlPanel();

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

 protected:
  GameInfo *Info;
  void paintEvent(QPaintEvent *event);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
};

#endif // ControlPanel_H

