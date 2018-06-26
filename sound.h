//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_WOLF_DEAD = 0,		// BGM0
	SOUND_WOLF,
	SOUND_WATER,
	SOUND_BGM_TITLE,
	SOUND_BGM_MORI,
	SOUND_ATTACK_WATER,
	SOUND_SP_WATER,
	SOUND_ATTACK_KAMINARI,
	SOUND_ATTACK_FIRE,
	SOUND_BGM_MACHI,
	SOUND_ATTACK_ALL,
	SOUND_SP_KAMINARI,
	SOUND_SE_HAHAHA,
	SOUND_SE_GAMEOVER,
	SOUND_FLY_DEAD,
	SOUND_FLY,
	SOUND_SP_FIRE,
	SOUND_SE_BEHIT,
	SOUND_ATTACK_02,
	SOUND_DROW_02,
	SOUND_DROW_01,
	SOUND_ATTACK_01,
	SOUND_SE_ASHIOTO,
	SOUND_SE_GAMESTART,
	SOUND_SE_PAGE,
	SOUND_BGM_BATTLE,
	SOUND_BOX_DEAD,
	SOUND_DROW_CARD,
	SOUND_ENEMY_SEE,
	SOUND_LABEL_MAX,
} SOUND_LABEL;


typedef struct
{
	SOUND_LABEL SoundNum;
	bool SoundSwitch;
}SOUNDALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

void CreateSound(int SoundNum);
void DestroySound(int SoundNum);

void ResetSound(void);
#endif
