#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include <d3dx9.h>
#include "Game.h"

#define MAX_BILLBOARD (50)/*最大ビルボード数設定*/

bool InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);


void CreateBillboardWHN(int Billboardnum, float width, float height, int TexNumAll);/*ビルボード生成*/

void DestroyBillboard(int Billboardnum);/*ビルボード消去*/

void SetBillboardISTexNum(int Billboardnum, TEXTURE_BILLBOARD_NUM ISTexBillboardNum);/*ビルボードのテクスチャー設定*/

void SetBillboardPos(int Billboardnum, float x, float y, float z);/*ビルボードの座標設定*/

D3DXVECTOR3 GetBillboardPos(int Billboardnum);

void SetBillboardTexCoord(int Billboardnum,float x0, float y0, float x1, float y1);

#endif