
#include <QtGui>

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint widgetPosition = mapFromGlobal(event->globalPos());

   widgetPosition.y() // ���������� ���� �� �
   widgetPosition.x() // ���������� ���� �� �
   MainWindow::size() // ������ ����
}

// �� ���� �������� ���, ����� ������� �����������������, � ������ ���� ���� �������� ��� ��� �������� �������. =( ����� �� // ����������?