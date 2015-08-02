#pragma once

#include "DirectX.h"

//extern DirectX gc;
///////////////////////////////
/*            地图           */
/*            0 为空         */
/*            遵循上右下左   */
/*       砖块 1,2,3,4,5    */
/*       铁块 6,7,8,9,10     */
/*       玩家1为11，玩家2为12    */
/*       老家为13          */
/*       草地为14，水为15          */
////////////////////////////////

#define MainTankMove 95
#define STARTX 0
#define STARTY 0

bool GameInit();
bool SurfaceInit();
void GameDraw();
void GameInput();
//void 
