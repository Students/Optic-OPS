
#include <QList>
#include <QPolygonF>

#include "GameInfo.h"
#include "Map.h"

GameInfo::GameInfo()
{
 antialiased = false;

 ScrollHorizontal = 0;
 ScrollVertical = 0;
 GameUserView_Position.rx() = 0.0;
 GameUserView_Position.ry() = 0.0;
 ScrollSpeed = 20.0;
 ZoomFactor = 1.0;
 FramesPerSecond = 100.0;

 DrawUnitsPath = 0;

 Global_Time = 0;
 FrameTime = (int)(1000.0/FramesPerSecond);
 if (FrameTime <= 0) FrameTime = 2;

 Map = new GameMap(this);
}

GameInfo::~GameInfo()
{

}

