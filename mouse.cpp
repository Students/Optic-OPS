
#include <QtGui>

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint widgetPosition = mapFromGlobal(event->globalPos());

   widgetPosition.y() // координаты мышы по У
   widgetPosition.x() // координаты мышы по Х
  // MainWindow::size() // размер окна
}

// По теме размера окна. Походу, создавая окно для карты, ты сам обязан указать функцией window.resize(200, 120); соответственно 200 - ширина, 
// 120 пикселей - высота. И собсно потом от них и считать положение мыши надо. =\ 