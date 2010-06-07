
#ifndef GraphicRender_H
  #define GraphicRender_H

  #include <QWidget>
  #include <QBrush>
  #include <QPen>
  #include <QPixmap>

  #include "GameInfo.h"

class GraphicRender : public QWidget
{
  Q_OBJECT

 protected:
  GameInfo *Info;
  bool antialiased;

 public:
  GraphicRender(GameInfo *info, QWidget *parent = 0);
  ~GraphicRender();
  void Draw();

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

 protected:
  void paintEvent(QPaintEvent *event);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
};

#endif // GraphicRender_H

