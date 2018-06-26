#include "scene.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "Train.h"
#include "shadow.h"
#include "Billboard.h"
#include "wall.h"
#include "meshfield.h"
#include "polygon.h"
#include "stage.h"
#include "Resalte.h"
#include "sound.h"

//void(*pFunc)() = InitTittle;
//void(*pFunc)(int) = 
//void(*pFunc)(int,int) = 
//int(*pFunc)(int,int) = 


typedef void(*SceneFunc)(void);
static const SceneFunc g_pInit[SERNR_MAX]=
{
	InitTitle,
	InitTrain,
	InitGame,
	InitStage,
	InitResalte,
};
static const SceneFunc g_pUninit[SERNR_MAX] =
{
	UninitTitle,
	UninitTrain,
	UninitGame,
	UninitStage,
	UninitResalte,
};
static const SceneFunc g_pUpdate[SERNR_MAX] =
{
	UpdateTitle,
	UpdateTrain,
	UpdateGame,
	UpdateStage,
	UpdateResalte,
};
static const SceneFunc g_pDraw[SERNR_MAX] =
{
	DrawTitle,
	DrawTrain,
	DrawGame,
	DrawStage,
	DrawResalte,
};


#define START_SCENE (SCENE_TITLE)

static SCENE_ID g_nID= START_SCENE;
static SCENE_ID g_nNextID= START_SCENE;

void InitAllScene(void)
{
	InitPolygon();
	InitScore();
	//影設定
	if (!InitShadow())
	{
		MessageBox(NULL, "initshadow読み込めなかった", "エラー", MB_OK);
	}
	if (!ReadShadow())
	{
		MessageBox(NULL, "readshadow読み込めなかった", "エラー", MB_OK);
	}
	SetShadowColor(SHADOW_CHARACTER, 255, 255, 255, 90);
	SetShadowTex(SHADOW_TEXTURE_1);
	InitShadowData();
	if (!InitBillboard())
	{
		MessageBox(NULL, "Billboard読み込めなかった", "エラー", MB_OK);
	}
	if (!InitMeshField())
	{
		MessageBox(NULL, "MeshField読み込めなかった", "エラー", MB_OK);
	}
	if (!InitWall())
	{
		MessageBox(NULL, "Wall読み込めなかった", "エラー", MB_OK);
	}
	InitFade();
}

void UninitAllScene(void)
{
	UninitPolygon();
	UninitBillboard();
	UninitMeshField();
	UninitWall();
	UninitShadow();
}

void InitScene(void)
{
	g_pInit[g_nID]();
}
void UninitScene(void)
{
	g_pUninit[g_nID]();
}
void UpdateScene(void)
{
	g_pUpdate[g_nID]();
	UpdateFade();
}
void DrawScene(void)
{
	g_pDraw[g_nID]();
	if (g_nNextID != g_nID)
	{
		UninitScene();
		g_nID = g_nNextID;
		InitScene();
	}
	DrawFade();
}

SCENE_ID ChangeScene(SCENE_ID id)
{
	g_nNextID = id;
	return g_nID;
}