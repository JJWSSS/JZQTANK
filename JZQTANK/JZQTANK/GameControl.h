#pragma once

#include "DirectX.h"

//extern DirectX gc;
///////////////////////////////
/*            ��ͼ           */
/*            0 Ϊ��         */
/*            ��ѭ��������   */
/*       ש�� 1,2,3,4,5      */
/*       ���� 6,7,8,9,10     */
/*       �ݵ�Ϊ14��ˮΪ15    */
////////////////////////////////

#define MainTankMove 95
#define STARTX 371
#define STARTY 114
#define ENDX 995
#define ENDY 738

void MyTankAnimation();
void ImageDraw(int frame, int columns, int environment, int wid, int hei, float x, float y);
bool GameInit();
bool SurfaceInit();
void GameDraw();
void GameInput();
bool TSpriteInit();
//void 
