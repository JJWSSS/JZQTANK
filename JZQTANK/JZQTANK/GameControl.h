#pragma once

#include "DirectX.h"

//extern DirectX gc;
///////////////////////////////
/*            ��ͼ           */
/*            0 Ϊ��         */
/*            ��ѭ��������   */
/*       ש�� 1,2,3,4,5    */
/*       ���� 6,7,8,9,10     */
/*       ���1Ϊ11�����2Ϊ12    */
/*       �ϼ�Ϊ13          */
/*       �ݵ�Ϊ14��ˮΪ15          */
////////////////////////////////

#define MainTankMove 95
#define STARTX 0
#define STARTY 0

bool GameInit();
bool SurfaceInit();
void GameDraw();
void GameInput();
//void 
