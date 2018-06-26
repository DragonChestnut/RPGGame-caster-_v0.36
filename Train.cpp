#include "Train.h"
#include "Game.h"
#include "Xmodel.h"
#include "meshfield.h"
#include "camera.h"
#include "character.h"
#include "Billboard.h"
#include "scene.h"
#include "wall.h"
#include "input.h"
#include "shadow.h"
#include "TrainUI.h"
#include "effect.h"
#include "Enemy_Train.h"
#include "Fade.h"
#include "GameUI.h"
#include "Polygon.h"
#include "Story.h"
#include "sound.h"


static int TrainLevel = 0;
static bool FadeSwitch;
static int TrainTime = 0;
static bool EnterSwitch;
static D3DXVECTOR3 BossPos;
static float BossWalkx0;
static float BossWalkx1;
static int BossWalkISAnime;
static int BossWalkMaxAnime;
static int BossWalkCounter;
static bool StorySwitch;

void InitTrain(void)
{
	TrainTime = 0;
	BossPos.x = -22.0f;
	BossPos.y = 0.0f;
	BossPos.z = 0.0f;
	BossWalkx0 = 0.0f;
	BossWalkx1 = 0.0f;
	BossWalkISAnime=1;
	BossWalkMaxAnime=6;
	BossWalkCounter = 0;
	EnterSwitch = false;
	StorySwitch = true;
	ResetCamera();
	D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
	SetShadowPos(SHADOW_CHARACTER, characterpos.x, characterpos.y, characterpos.z);
	SetShadowScaling(SHADOW_CHARACTER, 0.12f, 0.05f, 0.05f);

	//
	InitCharacter();
	SetISCharacterTrain(true);

	InitGameUI();
	InitTrainUI();
	InitEffect();
	InitEnemyTrain();
	SetMeshFildTexNum(1);
	//
	TrainLevel = 0;
	FadeSwitch = false;
	//
	CreateBillboardWHN(BILL_BACKGROUND_01, 192.f, 17.5f, 1);
	SetBillboardISTexNum(BILL_BACKGROUND_01, TEX_BACKGROUND_HOUSE_01);
	SetBillboardPos(BILL_BACKGROUND_01, -30.f, 0.f, 12.f);
	InitStory();
	StartStory();
	DestroySound(SOUND_SE_GAMESTART);
	CreateSound(SOUND_BGM_MACHI);
}
void UninitTrain(void)
{
	TrainTime = 0;
	BossPos.x = -22.0f;
	BossPos.y = 0.0f;
	BossPos.z = 0.0f;
	BossWalkx0 = 0.0f;
	BossWalkx1 = 0.0f;
	BossWalkISAnime = 1;
	BossWalkMaxAnime = 6;
	BossWalkCounter = 0;
	EnterSwitch = false;
	UninitEnemyTrain();
	UninitCharacter();
	SetISCharacterTrain(false);
	UninitTrainUI();
	UninitGameUI();
	TrainLevel = 0;
	FadeSwitch = false;
	StorySwitch = true;
	DestroyBillboard(BILL_BACKGROUND_01);
}
void UpdateTrain(void)
{
	if (StorySwitch)
	{
		UpdateStory();
	}
	else
	{
		//
		D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
		SetShadowPos(SHADOW_CHARACTER, characterpos.x, characterpos.y, characterpos.z);
		if (TrainLevel == 1 || TrainLevel == 2 || TrainLevel == 3 || TrainLevel == 5 || TrainLevel == 7 || TrainLevel == 8 || TrainLevel == 9 || TrainLevel == 11)
		{
			TrainTime++;
			if (TrainTime >= 60)
			{
				EnterSwitch = true;
			}
			if (EnterSwitch)
			{
				if (GetKeyboardPress(DIK_RETURN))
				{
					//“G¶¬
					if (TrainLevel == 2)
					{
						CreateEnemyTrain(0, -38.5f, 0.f, 0.f);
					}
					TrainLevel++;
					TrainTime = 0;
					EnterSwitch = false;
				}
			}
		}
		if (TrainLevel==4)
		{
			DestroySound(SOUND_BGM_MACHI);
			CreateSound(SOUND_BGM_BATTLE);

		}
		if (TrainLevel == 5)
		{
			DestroySound(SOUND_BGM_BATTLE);
			CreateSound(SOUND_BGM_MACHI);
			CreateSound(SOUND_BOX_DEAD);
			DestroyEnemyTrain(0);
		}
		if (TrainLevel == 6)
		{
			DestroySound(SOUND_BOX_DEAD);
		}
		if (TrainLevel == 7)
		{
			CreateSound(SOUND_ENEMY_SEE);
			CreateBillboardWHN(BILL_ENEMY_TRAIN_01, 2.2f, 2.68125f, 1);
			SetBillboardPos(BILL_ENEMY_TRAIN_01, BossPos.x, BossPos.y, BossPos.z);
			SetBillboardISTexNum(BILL_ENEMY_TRAIN_01, TEX_ENEMY_REBOSS);
			BossWalkx0 = (BossWalkISAnime - 1) / (float)BossWalkMaxAnime;
			BossWalkx1 = (BossWalkISAnime) / (float)BossWalkMaxAnime;
			SetBillboardTexCoord(BILL_ENEMY_TRAIN_01, BossWalkx0, 0.0f, BossWalkx1, 1.0f);
		}
		if (TrainLevel == 8)
		{
			DestroySound(SOUND_ENEMY_SEE);
		}
		if (TrainLevel == 10)
		{
			CreateSound(SOUND_SE_HAHAHA);
			BossWalkCounter++;
			BossPos.x += 0.2;
			if (BossWalkCounter >= 5)
			{
				BossWalkCounter = 0;
				BossWalkISAnime++;
				if (BossWalkISAnime > BossWalkMaxAnime)
				{
					BossWalkISAnime = 1;
				}
			}
			SetBillboardPos(BILL_ENEMY_TRAIN_01, BossPos.x, BossPos.y, BossPos.z);
			BossWalkx0 = (BossWalkISAnime - 1) / (float)BossWalkMaxAnime;
			BossWalkx1 = (BossWalkISAnime) / (float)BossWalkMaxAnime;
			SetBillboardTexCoord(BILL_ENEMY_TRAIN_01, BossWalkx0, 0.0f, BossWalkx1, 1.0f);
			if (BossPos.x >= -10)
			{
				DestroySound(SOUND_SE_HAHAHA);
				TrainLevel = 11;
			}
		}
		if (TrainLevel == 12)
		{
			StartFade(Out, White);
			FadeSwitch = true;
			TrainLevel++;
		}
		if (FadeSwitch)
		{
			if (GetState() == After)
			{
				StartFade(In, White);
				DestroySound(SOUND_BGM_MACHI);
				ChangeScene(SCENE_GAME);
			}
		}
		//test
		if (GetKeyboardPress(DIK_5))
		{
			TrainLevel = 5;
		}
		//
		if (GetKeyboardPress(DIK_7))
		{
			StartFade(Out, White);
			FadeSwitch = true;
		}
		UpdateCharacter();
		UpdateEnemyTrain();
		UpdateTrainUI();
		UpdateEffect();
	}
	UpdateShadow();
	UpdateWall();
	UpdateCamera();
	UpdateMeshField();
	UpdateGameUI();
	UpdateBillboard();
}
void DrawTrain(void)
{
	DrawWall();
	DrawMeshField();
	DrawCharacter();
	DrawBillboard();
	DrawGameUI();
	DrawTrainUI();
	if (StorySwitch)
	{
		DrawStory();
	}
	else
	{
		DrawShadow();
	}
}

int GetTrainLevel(void)
{
	return TrainLevel;
}

void SetTrainLevel(int num)
{
	TrainLevel = num;
}

void StroyOver(void)
{
	StorySwitch = false;
}