#pragma once

#include "DirectX.h"

//extern DirectX gc;
///////////////////////////////
/*            地图           */
/*            0 为空         */
/*            遵循上右下左   */
/*       砖块 1,2,3,4,5      */
/*       铁块 6,7,8,9,10     */
/*       草地为14，水为15    */
////////////////////////////////

#define MainTankMove 95
#define STARTX 371
#define STARTY 144

bool GameInit();
bool SurfaceInit();
void GameDraw();
void GameInput();
bool TSpriteInit();
//void 
