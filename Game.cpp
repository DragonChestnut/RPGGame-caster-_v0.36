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
#include "GameUI.h"
#include "effect.h"
#include "Fade.h"
#include "Clock.h" 
#include "Resalte.h"
#include "Timer.h"
#include "sound.h"


static bool FadeSwitch;

void InitGame(void)
{
	NewGame();
	ResetCamera();
	//
	D3DXVECTOR3 characterpos=GetBillboardPos(BILL_CHARACTER);
	SetShadowPos(SHADOW_CHARACTER, characterpos.x, characterpos.y, characterpos.z);
	SetShadowScaling(SHADOW_CHARACTER, 0.12f, 0.05f, 0.05f);

	InitCharacter();
	SetISCharacterTrain(false);
	InitGameUI();
	InitEffect();
	SetMeshFildTexNum(0);

	CreateBillboardWHN(BILL_BACKGROUND_01, 128.f, 10.f, 1);
	SetBillboardISTexNum(BILL_BACKGROUND_01, TEX_BACKGROUND_TREE_01);
	SetBillboardPos(BILL_BACKGROUND_01, -30.f, 0.f, 12.f);

	FadeSwitch = false;
	NewGame();
	CreateSound(SOUND_BGM_BATTLE);
}


void UninitGame(void)
{
	UninitCharacter();
	UninitGameUI();
	UninitEffect();
	DestroyBillboard(SOUND_BGM_BATTLE);
}

void UpdateGame(void)
{
	//
	D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
	SetShadowPos(SHADOW_CHARACTER, characterpos.x, characterpos.y, characterpos.z);
	//
	UpdateWall();
	UpdateCamera();
	
	UpdateMeshField();
	UpdateCharacter();
	UpdateShadow();
	UpdateGameUI();
	UpdateClock();
	UpdateEffect();
	UpdateBillboard();
	//test
	if (GetKeyboardPress(DIK_8))
	{
		//NewScore(GetTime(), 10, GetCharacterISCard());
		StartFade(Out, White);
		FadeSwitch = true;
	}
	if (FadeSwitch)
	{
		if (GetState() == After)
		{
			StartFade(In, White);
			ChangeScene(SCENE_STAGE);
		}
	}
	//
}

void DrawGame(void)
{
	DrawWall();
	DrawMeshField();
	DrawCharacter();
	DrawBillboard();
	DrawShadow();
	DrawGameUI();
	DrawClock();
}