#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_


#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"

static D3DXMATRIX g_mtxfield;

typedef enum MESH_FIELD_NUM
{
	MESH_FIELD_1,
	MESH_FIELD_2,
	MESH_FIELD_3,
	MESH_FIELD_MAX
};

const TEXTURE TextureMeshMessage[MESH_FIELD_MAX] =
{
	{ "Texture/field001.png", 160, 160 },
	{ "Texture/field002.png", 160, 160 },
	{ "Texture/field003.png", 160, 160 },
};

bool InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

bool SetMeshSize(float w, float h, int wnum, int hnum);/*メッシュフィールドの幅さ、長さ、幅の数、長の数設定*/

void SetMeshFildTexNum(int Texnum);

#endif