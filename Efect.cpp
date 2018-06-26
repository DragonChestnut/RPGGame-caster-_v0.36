//================================================
//	エフェクト.cpp
//
//================================================

#include "main.h"
#include "Efect.h"
#include "Polygon.h"

namespace {
	//エフェクト用のテクスチャ一時変数
	int Efect_Tex;
}


void InitEfect(void)
{
	for (int i = 0; i < MAX_EFECT; i++)
	{
		g_Efects[i].b_Efect = false;
	}
	g_nEfectFrameCounter = 0;
}


void UninitEfect(void)
{

}

void UpdateEfect(void)
{
	//寿命チェック
	for (int i = 0; i < MAX_EFECT; i++)
	{
		if (!g_Efects[i].b_Efect)
		{
			continue;
		}
		int nAge = g_nEfectFrameCounter - g_Efects[i].nBirth;
		if (nAge >= g_Efects[i].nLimit)
		{//寿命の終わり
			g_Efects[i].b_Efect = false;
		}
	}

	g_nEfectFrameCounter++;	
}

//====================================================
//	エフェクトの描画
//====================================================
void DrawEfect(void)
{
	//加算合成の設定へ変更
	//SRC_RGB*SRC_α+DST_RGB*1の計算（設定）
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	SetTexture(TEX_TITLE_EFE);
	for (int i = 0; i < MAX_EFECT; i++)
	{
		if (!g_Efects[i].b_Efect)
		{
			continue;
		}
		//エフェクト描画
		//D3DXCOLOR型　=　クラス{float r,g,b,a}; a = 0.0~1.0
		//注意　D3DCOLOR と　D3DXCOLOR のサイズは違う
		
		//カラーの計算
		//年齢によってαを変える
		//０歳…最初のαカラー
		//寿命の年齢…α＝０
		g_Efects[i].color = D3DXCOLOR(0.7, 0.7, 0.7, 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth),0.1)/ (g_Efects[i].nLimit));
		SetPolygonColor(g_Efects[i].color);
		SetPolygonScale(0, 0, 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit), 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit));
		SetPolygonRotation(0,0,0);
		DrawPolygon(g_Efects[i].vPos.x + (TEXTURE_W * (max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit)))/2,
			g_Efects[i].vPos.y + (TEXTURE_H * (max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit)))/2, 10, 10, 40, 0, 40, 40, true);

	}
	//通常の描画設定へ戻す
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 20);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

}

//===========================================================
//	エフェクトの作成
//	float x,y ... 座標
//	color ... 色
//	nLimit ... 寿命
//===========================================================
void CreateEfect(float x, float y , D3DCOLOR color, int nLimit)
{
	for (int i = 0; i < MAX_EFECT; i++)
	{
		if (g_Efects[i].b_Efect)
		{
			continue;
		}
		g_Efects[i].b_Efect = true;
		g_Efects[i].color = color;
		g_Efects[i].vPos = D3DXVECTOR2(x, y);
		g_Efects[i].nLimit = nLimit;
		g_Efects[i].nBirth = g_nEfectFrameCounter;

		i = MAX_EFECT;
	}
}

//
//	エフェクト用の画像差し替え
//
//void EfectTexture(EFECT_TEX tex)
//{
//	Efect_Tex = TEXTURE_PLAYWE_01 + tex;
//	SetTexture((TEXTURE_ENUM)Efect_Tex);
//}