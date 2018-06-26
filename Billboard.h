#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include <d3dx9.h>
#include "Game.h"

#define MAX_BILLBOARD (50)/*�ő�r���{�[�h���ݒ�*/

bool InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);


void CreateBillboardWHN(int Billboardnum, float width, float height, int TexNumAll);/*�r���{�[�h����*/

void DestroyBillboard(int Billboardnum);/*�r���{�[�h����*/

void SetBillboardISTexNum(int Billboardnum, TEXTURE_BILLBOARD_NUM ISTexBillboardNum);/*�r���{�[�h�̃e�N�X�`���[�ݒ�*/

void SetBillboardPos(int Billboardnum, float x, float y, float z);/*�r���{�[�h�̍��W�ݒ�*/

D3DXVECTOR3 GetBillboardPos(int Billboardnum);

void SetBillboardTexCoord(int Billboardnum,float x0, float y0, float x1, float y1);

#endif