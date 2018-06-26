#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <d3dx9.h>

#include "Billboard.h"

#define MAX_EFFECT (10)

typedef enum CHARACTER_EFFECT_NUM
{
	CHARACTER_EFFECT_NULL = -1,
	CHARACTER_EFFECT_FLAME,
	CHARACTER_EFFECT_AQUA,
	CHARACTER_EFFECT_THUNDER,
	CHARACTER_EFFECT_MAGIC_SQUARE_00,
	CHARACTER_EFFECT_MAGIC_SQUARE_01,
	CHARACTER_EFFECT_MAGIC_SQUARE_02,
	CHARACTER_EFFECT_RUA00,
	CHARACTER_EFFECT_RUA01,
	CHARACTER_EFFECT_MAX
};

typedef struct
{
	D3DXVECTOR3 EffectPos;/*座標*/
	int EffectAnimeCounter;
	float Effectx0;
	float Effectx1;
	int EffectISAnime;
	int EffectMaxAnime;
	int EffectDirection;
	CHARACTER_EFFECT_NUM EffectType;
	bool ISEffect;
	int EffectChangeSpeed;
	bool EffectStop;//調整用
	int EffectStopAnimeNum;//調整用
	float EffectXspeed;
	float EffectZspeed;
	//int EffectI;//調整用
}EFFECT;


void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void CreateEffect(CHARACTER_EFFECT_NUM EffectType, int MaxEffectAnimeNum, int EffectChangeSpeed, int name,float EffectXspeed = 0, float EffectZspeed = 0, bool EffectStopSwitch = false, int EffectStopAnimeNum = 0);
void DestroyEffect(CHARACTER_EFFECT_NUM EffectType);
int GetEffectISAnime(CHARACTER_EFFECT_NUM EffectType);
void SetEffectBill(CHARACTER_EFFECT_NUM EffectType, int EffectDirection, D3DXVECTOR3 EffectPos);


#endif