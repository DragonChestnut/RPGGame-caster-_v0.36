#pragma once
#ifndef _XMODEL_H_
#define _XMODEL_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"

#define MAX_MESH (5)
#define MAX_TEX (10)

//Xƒ‚ƒfƒ‹‚Ì•`‰æ
static LPD3DXMESH g_pMesh[MAX_MESH] = { NULL, };
static DWORD g_nMaterialNum[MAX_MESH] = {0,};
static LPD3DXBUFFER g_pMaterial[MAX_MESH] = { NULL, };

static D3DXMATRIX g_mtxtran1;

typedef struct {
	char filename[256];
	int meshnum;
}MODEL;

typedef enum MODEL_NUM
{
	MODEL_1,
	MODEL_2,
	MODEL_3,
	MODEL_MAX
};

static D3DXMATRIX g_mtxModel[MODEL_MAX];

static float g_x[MODEL_MAX] = {0,};
static float g_y[MODEL_MAX] = { 0, };
static float g_z[MODEL_MAX] = { 0, };
const MODEL ModelMessage[MODEL_MAX] =
{
	{{ "Xmodel/cart.x"},2 },
	{{ "Xmodel/gandamu.x"},1 },
	{{ "Xmodel/gradriel.x"},1 }

};


const TEXTURE TextureModelMessage[MODEL_MAX] [MAX_TEX]=
{
	{{ "Xmodel/tex/horse.png", 256, 256 },{ "Xmodel/tex/cart.png", 256, 256 },},
	{ { "Xmodel/tex/00tex_master.png", 512, 512 },} ,
	{ { "Xmodel/tex/gradriel_tex.dds", 512, 512 }, }
};


bool InitXmodel(void);
void UninitXmodel(void);
void UpdateXmodel(void);
void DrawXmodel(void);

void SetModelXYZ(MODEL_NUM modelnum, float x, float y, float z);

#endif