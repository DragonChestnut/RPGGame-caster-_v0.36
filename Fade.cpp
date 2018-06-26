//============================================================
//	fade.cpp
//
//
//============================================================
#include "Fade.h"
#include <d3d9.h>
#include "main.h"
#include "Polygon.h"

#define FADE_IN_SPEED	()
#define FADE_OUT_SPEED	()


//	グローバル変数
namespace
{
	//Fade処理中か
	bool g_live;
	//行うFadeの種類（In/Out）
	int g_type;
	//Fade処理用のカウンタ
	float g_count;

	bool g_FullSwitch;
	//テクスチャのFade用
	TEXTURE_NUM g_fadetex;
	//Fadeの種類（White / Bluck / Texture）
	FADE_TEX g_tex;
	//Fadeの前後判定用
	SCREEN_STATE g_state = Bfore;
}

void InitFade(void)
{
	g_count = 0;
	g_live = false;

	//
	g_FullSwitch = false;
	//
	g_state = Bfore;
	//g_fadetex = NULL;
	g_fadetex = TEX_FADE;
}

void UpdateFade(void)
{
	if (g_live)
	{
		g_count+=5;
		if (g_count >= 255)
		{
			g_live = false;
			g_count = 0;
			switch (g_type)
			{
			case In:
				g_state = Purpose;
				break;
			case Out:
				g_state = After;
				g_FullSwitch = true;
				break;
			default:
				break;
			}
		}
	}
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 20);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	g_fadetex = TEX_FADE;
	if (g_live)
	{
		if (g_type == In)
		{
			g_FullSwitch = false;
			int Alpha = 255 - (int)g_count;
			if (Alpha>=255)
			{
				Alpha = 255;
			}
			switch (g_tex)
			{
			case White:
				SetPolygonColor(D3DCOLOR_ARGB(Alpha, 255, 255, 255));
				break;
			case Black:
				SetPolygonColor(D3DCOLOR_ARGB(Alpha, 0, 0, 0));
				break;
			default:
				break;
			}

		}
		else if (g_type = Out)
		{
			switch (g_tex)
			{
			case White:
				SetPolygonColor(D3DCOLOR_ARGB((int)g_count, 255, 255, 255));
				break;
			case Black:
				SetPolygonColor(D3DCOLOR_ARGB((int)g_count, 0, 0, 0));
				break;
			default:
				break;
			}
		}
		SetTexture(g_fadetex);
		DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 100, 100);
	}
	if (g_FullSwitch)
	{
		switch (g_tex)
		{
		case White:
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case Black:
			SetPolygonColor(D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		default:
			break;
		}
		SetTexture(g_fadetex);
		DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 100, 100);
		//SetTexture(TEX_CHARACTER_LOADING);
		//DrawPolygon(0, 0, 150*5, 163*5, 750*g_CharacterWalkx0, 0, 750 * g_CharacterWalkx1, 163);
	}
}

bool StartFade(FADE_TYPE type, FADE_TEX tex)
{
	if (g_live)
	{//別Fade処理中
		return false;
	}
	else
	{//Fade可能
		g_type = type;
		g_count = 0;
		g_live = true;

		switch (tex)
		{
		case White:
			g_tex = White;
			g_fadetex = TEX_FADE;
			break;
		case Black:
			g_tex = Black;
			g_fadetex = TEX_FADE;
			break;
		default:
			break;
		}
	}
}

SCREEN_STATE GetState(void)
{
	return (SCREEN_STATE)g_state;
}
