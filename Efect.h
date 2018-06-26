//================================================
//	エフェクト.h
//
//================================================

#include <d3dx9.h>

#ifndef _EFECT_H_
#define _EFECT_H_

#define MAX_EFECT	(1024)
#define TEXTURE_H	(80)
#define TEXTURE_W	(80)

typedef struct
{
	D3DXVECTOR2 vPos;
	bool b_Efect;
	D3DCOLOR color;
	int nLimit;//寿命
	int nBirth;//誕生タイミング

}EFECT;

enum EFECT_TEX
{
	PLAYER_EFE=0
};

static EFECT g_Efects[MAX_EFECT];
static int g_nEfectFrameCounter = 0 ;

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************

void InitEfect(void);
void UninitEfect(void);
void UpdateEfect(void);
void DrawEfect(void);

//=======================================================
//	エフェクトの生成
//	x,y... 生成位置	color... 開始位置	
//	nLimit...何フレーム分生きるか
//=======================================================
void CreateEfect(float x, float y, D3DCOLOR color, int nLimit);

//=========================================================
//	エフェクトテクスチャの指定
//	tex... エフェクトの列挙がたを入れる
//=========================================================
void EfectTexture(EFECT_TEX tex);

#endif

