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
#include "Stage.h"
#include "Clock.h"
#include "sound.h"

static bool FadeSwitch;

void InitStage(void)
{
	ResetCamera();
	//
	D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
	SetShadowPos(SHADOW_CHARACTER, characterpos.x, characterpos.y, characterpos.z);
	SetShadowScaling(SHADOW_CHARACTER, 0.12f, 0.05f, 0.05f);

	InitCharacter();
	SetISCharacterTrain(false);
	InitGameUI();
	InitEffect();
	SetMeshFildTexNum(2);

	CreateBillboardWHN(BILL_BACKGROUND_01, 128.f, 15.f, 1);
	SetBillboardISTexNum(BILL_BACKGROUND_01, TEX_BACKGROUND_SHIRO_01);
	SetBillboardPos(BILL_BACKGROUND_01, -30.f, -2.f, 12.f);

	FadeSwitch = false;
	CreateSound(SOUND_BGM_BATTLE);
}


void UninitStage(void)
{
	UninitCharacter();
	UninitGameUI();
	UninitEffect();
	DestroyBillboard(BILL_BACKGROUND_01);
	DestroySound(SOUND_BGM_BATTLE);
}

void UpdateStage(void)
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
	UpdateEffect();
	UpdateBillboard();
	UpdateClock();
	//test
	if (GetKeyboardPress(DIK_9))
	{
		StartFade(Out, White);
		FadeSwitch = true;
	}
	if (FadeSwitch)
	{
		if (GetState() == After)
		{
			StartFade(In, White);
			ChangeScene(SCENE_RESULT);
		}
	}
	//
}

void DrawStage(void)
{
	DrawWall();
	DrawMeshField();
	DrawCharacter();
	DrawBillboard();
	DrawShadow();
	DrawGameUI();
	DrawClock();
}