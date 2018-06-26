#pragma once
#ifndef _WALL_H_
#define _WALL_H_

#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"

typedef enum WALL_NUM
{
	WALL_1,
	WALL_MAX
};

const TEXTURE TextureWallMessage[WALL_MAX] =
{
	{ "Texture/background_01.jpg", 942.f, 530.f },
};

bool InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

void SetTextureWall(int nNumTex);
#endif
