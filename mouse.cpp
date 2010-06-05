
#include <QtGui>

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint widgetPosition = mapFromGlobal(event->globalPos());

   widgetPosition.y() // координаты мышы по У
   widgetPosition.x() // координаты мышы по Х
   MainWindow::size() // размер окна
}

// не могу смекнуть щас, какой логикой руководствоваться, в смысле кучу ифов накидать или как красивее сделать. =( Может ты // сообразишь?