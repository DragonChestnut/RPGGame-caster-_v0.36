#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <d3d9.h>
#include <d3dx9.h>


#define NAME_CHARACTER (0)
#define NAME_ENEMY_01 (1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 way;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;

typedef struct {
	char filename[256];
	int width;
	int height;
}TEXTURE;

typedef enum TEXTURE_BILLBOARD_NUM
{
	TEX_BILLBOARD_NULL = -1,
	TEX_CHARACTER_WOMAN_WALK_R,
	TEX_CHARACTER_WOMAN_WALK_L,
	TEX_EFFECT_FLAME_R,
	TEX_EFFECT_FLAME_L,
	TEX_EFFECT_AQUA_R,
	TEX_EFFECT_AQUA_L,
	TEX_EFFECT_THUNDER_R,
	TEX_EFFECT_THUNDER_L,
	TEX_CHARACTER_WOMAN_ATTACK_R,
	TEX_CHARACTER_WOMAN_ATTACK_L,
	TEX_CHARACTER_WOMAN_BEHIT_R,
	TEX_CHARACTER_WOMAN_BEHIT_L,

	TEX_CHARACTER_WOMAN_DROWCARD_R,
	TEX_CHARACTER_WOMAN_DROWCARD_L,

	TEX_EFFECT_MAGIC_SQUARE_00_R,
	TEX_EFFECT_MAGIC_SQUARE_00_L,
	TEX_EFFECT_MAGIC_SQUARE_01_R,
	TEX_EFFECT_MAGIC_SQUARE_01_L,
	TEX_EFFECT_MAGIC_SQUARE_02_R,
	TEX_EFFECT_MAGIC_SQUARE_02_L,
	TEX_EFFECT_RUA00_R,
	TEX_EFFECT_RUA00_L,
	TEX_EFFECT_RUA01_R,
	TEX_EFFECT_RUA01_L,

	TEX_BACKGROUND_HOUSE_01,
	TEX_BACKGROUND_TREE_01,
	TEX_BACKGROUND_SHIRO_01,

	TEX_ENEMY_BOX,
	TEX_ENEMY_REBOSS,

	TEX_ENEMY_TRAIN_HP_CAGE,
	TEX_ENEMY_TRAIN_HP_K,

	TEX_BILLBOARD_MAX
};

const TEXTURE BillboardTextureMessage[TEX_BILLBOARD_MAX] =
{
	{ "Texture/R/walk_R.png", 1500, 325 },
	{ "Texture/L/walk_L.png", 1500, 325 },
	{ "Texture/R/fire02R.png",1600,108 },
	{ "Texture/L/fire02L.png",1600,108 },
	{ "Texture/R/AQUA_R.png",2710,271 },
	{ "Texture/L/AQUA_L.png",2710,271 },
	{ "Texture/R/THUNDER_R.png",1600,100 },
	{ "Texture/L/THUNDER_L.png",1600,100 },
	{ "Texture/R/attack_R.png", 1250, 325 },
	{ "Texture/L/attack_L.png", 1250, 325 },
	{ "Texture/R/damage_R.png", 1000, 325 },
	{ "Texture/L/damage_L.png", 1000, 325 },

	{ "Texture/R/Drowcard_R.png", 1500, 325 },
	{ "Texture/L/Drowcard_L.png", 1500, 325 },

	{ "Texture/R/magic_01_R.png", 1600, 170 },
	{ "Texture/L/magic_01_L.png", 1600, 170 },
	{ "Texture/R/magic_02_R.png", 1600, 170 },
	{ "Texture/L/magic_02_L.png", 1600, 170 },
	{ "Texture/R/magic_03_R.png", 1600, 170 },
	{ "Texture/L/magic_03_L.png", 1600, 170 },
	{ "Texture/R/rua00_R.png", 4320, 960 },
	{ "Texture/L/rua00_L.png", 4320, 960 },
	{ "Texture/R/rua01_R.png", 4320, 960 },
	{ "Texture/L/rua01_L.png", 4320, 960 },

	{ "Texture/BACKGROUND/shiro_01.png", 3840, 350 },
	{ "Texture/BACKGROUND/tree_01.png", 2560, 200 },
	{ "Texture/BACKGROUND/shiro_03.png", 2560, 300 },

	{ "Texture/ENEMY/box.png", 208, 214 },
	{ "Texture/ENEMY/LOADING.png",750,163 },
	{ "Texture/ENEMY/HP/HP_CAGE.png",25,50 },
	{ "Texture/ENEMY/HP/HP_K.png",500,50 },
};

typedef struct
{
	D3DXMATRIX MtxBillboard;/*ビルボードの世界*/
	float BillboardWidth;/*ビルボードの幅さ*/
	float BillboardHeight;/*ビルボードの長さ*/
	D3DXVECTOR3 BillboardXYZ;/*ビルボードの座標*/
	int BillboardTexNum;/*ビルボードを使う全テクスチャー数*/
	TEXTURE_BILLBOARD_NUM ISbnum; /*ビルボード今使うテクスチャーの番号*/
	bool ISBillboard; /*ビルボードの存在判定*/
}BILLBOARD;


typedef enum BILLBOARD_NUM
{
	BILL_NULL = -1,
	BILL_BACKGROUND_01,
	BILL_CHARACTER,
	BILL_FLAME,
	BILL_AQUA,
	BILL_THUNDER,
	BILL_MAGIC_SQUARE_00,
	BILL_MAGIC_SQUARE_01,
	BILL_MAGIC_SQUARE_02,
	BILL_RUA00,
	BILL_RUA01,
	BILL_ENEMY_TRAIN_00,
	BILL_ENEMY_TRAIN_01,
	BILL_ENEMY_TRAIN_HP_K,
	BILL_ENEMY_TRAIN_HP_CAGE,
	BILL_MAX
};


void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif
