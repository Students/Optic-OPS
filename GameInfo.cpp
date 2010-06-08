
#include <QList>
#include <QPolygonF>

#include "Map.h"
#include "GameUnit.h"
#include "GameInfo.h"

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
 DrawSelection = 0;

 Global_Time = 0;
 FrameTime = (int)(1000.0/FramesPerSecond);
 if (FrameTime <= 0) FrameTime = 2;

 Map = new GameMap(this);
 GameUnits = new QList<GameUnit *>;
/***/
 GameUnit *unit = new GameUnit(this);
 GameUnits->append(unit);
/***/
}

GameInfo::~GameInfo()
{

}

void GameInfo::SelectUnitsInArea(QRectF *Area)
{
 for (int i=0; i<GameUnits->length(); i++)
  {
   if (((*GameUnits)[i])->State.Position->intersects(*Area));
    {
     SelectedObjects.append(i);
     ((*GameUnits)[i])->SetSelection(1);
    }
  }
}

void GameInfo::UnSelectAllUnits()
{
 for (int i=0; i<SelectedObjects.length(); i++)
  {
   ((*GameUnits)[SelectedObjects[i]])->SetSelection(0);
  }
 SelectedObjects.clear();
}


