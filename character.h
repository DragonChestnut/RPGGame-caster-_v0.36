#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <d3dx9.h>
#include "Game.h"
#include "Billboard.h"

#define CHARACTER_MAX_HP (100)
#define CHARACTER_MAX_MP (10000)

typedef enum CARD_TYPE
{
	CARD_TYPE_NULL = 0,
	CARD_TYPE_FIRE,
	CARD_TYPE_AQUA,
	CARD_TYPE_THUNDER,
	CARD_TYPE_MAX
};


typedef struct
{
	D3DXVECTOR3 CharacterPos;/*座標*/
	float speed_x;//横スピード
	float speed_z;//縦スピード
	int CharacterWalkAnimeCounter;
	float CharacterWalkx0;
	float CharacterWalkx1;
	int CharacterWalkISAnime;
	int CharacterWalkMaxAnime;
	int CharacterAttackAnimeCounter;
	float CharacterAttackx0;
	float CharacterAttackx1;
	int CharacterAttackISAnime;
	int CharacterAttackMaxAnime;
	bool CharacterAttackCounter;
	int CharacterISAttackMode;
	int CharacterAttackMode;
	int CharacterDirection;
	CARD_TYPE ISCharacterCard;
	bool ISSuperSkill;
	bool ISCharacter;
	bool ISCharacterTrain;
	bool NoActionSwitch;
	bool CardCoolTimeSwitch;

	int CharacterHP;
	int CharacterMP;
	int CharacterStarCage;

	bool ISCharacterBeHit;
	float CharacterBeHitx0;
	float CharacterBeHitx1;
	int CharacterBeHitAnimeCounter;
	int CharacterBeHitISAnime;
	int CharacterBeHitMaxAnime;

	bool ISCharacterDrowCard;
	float CharacterDrowCardx0;
	float CharacterDrowCardx1;
	int CharacterDrowCardAnimeCounter;
	int CharacterDrowCardISAnime;
	int CharacterDrowCardMaxAnime;

}CHARACTER;



void InitCharacter(void);
void UninitCharacter(void);
void UpdateCharacter(void);
void DrawCharacter(void);

void CharacterWalk(void);
int GetCharacterDirection(void);
D3DXVECTOR3 GetCharacterPos(void);
void SetISCharacterTrain(bool CharacterTrain);

void SetNoActionSwitch(bool ActionSwitch);
void CharacterNormalAttack(void);

void CharacterSetCard(CARD_TYPE Type);
void CharacterCardSetNum(void);
void CharacterSuperSkill(void);

CARD_TYPE GetCharacterISCard(void);

void DestroyCharacterSuperSkill(void);

void SetCardCoolSwitch(bool CardCool);

int GetCharacterHP(void);

int GetCharacterMP(void);

void CharacterBeHit(void);

bool GetCharacterISBeHit(void);

void CharacterPerformance(void);

void CharacterDrowCard(void);

int GetCharacterStarCage(void);

bool GetCharacterISAttack(void);

int GetCharacterISAttackMode(void);

bool GetCharacterTrain(void);
#endif