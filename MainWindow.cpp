
#include <QWidget>
#include <QtGui>
#include <QGridLayout>

#include "MainWindow.h"
#include "GameInfo.h"
#include "GraphicRender.h"
#include "ControlPanel.h"

MainWindow::MainWindow()
 : QWidget(0)
{
 setWindowTitle(tr("Optic-OPS"));
 setWindowState(Qt::WindowFullScreen);

 Info = new GameInfo;
 Render = new GraphicRender(Info);
 Panel = new ControlPanel(Info);

 QGridLayout *MainLayout = new QGridLayout;
 MainLayout->addWidget(Render, 0, 0);
 MainLayout->addWidget(Panel, 1, 0);
 setLayout(MainLayout);

 TimerID = startTimer(Info->FrameTime);
}

MainWindow::~MainWindow()
{
 killTimer(TimerID);
 delete Panel;
 delete Render;
 delete Info;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
 Info->Global_Time += Info->FrameTime;
 Render->Draw();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
 switch (event->key())
  {
   case Qt::Key_Left:
     Info->ScrollHorizontal = -1;
     break;

   case Qt::Key_Right:
     Info->ScrollHorizontal = 1;
     break;

   case Qt::Key_Up:
     Info->ScrollVertical = -1;
     break;

   case Qt::Key_Down:
     Info->ScrollVertical = 1;
     break;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
 switch (event->key())
  {
   case Qt::Key_Left:
   case Qt::Key_Right:
     Info->ScrollHorizontal = 0;
     break;

   case Qt::Key_Up:
   case Qt::Key_Down:
     Info->ScrollVertical = 0;
     break;
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
 int mouse_x = event->x();
 int mouse_y = event->y();
 int screen_size_x = width();
 int screen_size_y = height();
 if (mouse_x <= 3)
  {
   Info->ScrollHorizontal = -1;
   if (mouse_y <= 10) Info->ScrollVertical = -1;
   else if (mouse_y >= screen_size_y-10) Info->ScrollVertical = 1;
  }
 else if (mouse_x >= screen_size_x-3)
  {
   Info->ScrollHorizontal = 1;
   if (mouse_y <= 10) Info->ScrollVertical = -1;
   else if (mouse_y >= screen_size_y-10) Info->ScrollVertical = 1;
  }
 else if (mouse_y <= 3)
  {
   Info->ScrollVertical = -1;
   if (mouse_x <= 10) Info->ScrollHorizontal = -1;
   else if (mouse_x >= screen_size_x-10) Info->ScrollHorizontal = 1;
  }
 else if (mouse_y >= screen_size_y-3)
  {
   Info->ScrollVertical = 1;
   if (mouse_x <= 10) Info->ScrollHorizontal = -1;
   else if (mouse_x >= screen_size_x-10) Info->ScrollHorizontal = 1;
  }
 else
  {
   Info->ScrollHorizontal = 0;
   Info->ScrollVertical = 0;
  }
}


