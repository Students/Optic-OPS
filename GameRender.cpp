
#include <math.h>
#include "GameInfo.h"
#include "Map.h"
#include "GameUnit.h"
#include "GameRender.h"

GameRender::GameRender(GameInfo *info)
{
 Info = info;
 TimerID = startTimer(Info->FrameTime);
}

GameRender::~GameRender()
{
 killTimer(TimerID);
}

void GameRender::timerEvent(QTimerEvent *event)
{
 Info->Global_Time += Info->FrameTime;
 Process();
}

void GameRender::Process()
{
 for (int i=0; i<Info->GameUnits->length(); i++)
  {
   ((*(Info->GameUnits))[i])->DoitSomething(Info->FrameTime);
  }
}

