#include <math.h>
#include<d3d9.h>
#include "main.h"
#include "Polygon.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DTEXTURE9 g_pTexture[TEX_MAX] = { NULL };
static float g_fScale = 1.0f;
static float g_fScaleAdd = 0.01f;
static D3DCOLOR color = 0xffffffff;
static int TexNum = 0;

static float ScaleX = 1.0f;
static float ScaleY = 1.0f;
static float g_fRotationOffsetX = 0.0f;
static float g_fRotationOffsetY = 0.0f;
static float g_fPolygonAngle = 0.0f;

static float g_fScaleX = 1.0f;
static float g_fScaleY = 1.0f;
static float g_fScaleOffsetX = 0.0f;
static float g_fScaleOffsetY = 0.0f;

static void CreateVertex(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
static void CreateVertexAffine(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

static float g_Dcounterx = 1.0f;
static float g_Dcountery = 1.0f;

// ポリゴンの初期化
bool InitPolygon()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	// テクスチャの読み込み

	for (int count = 0; count < TEX_MAX; count++)
	{
		HRESULT hr;

		hr = D3DXCreateTextureFromFile
		(
			pDevice,
			TextureMessage[count].filename,
			&g_pTexture[count]
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr = pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVertexBuffer,
			NULL
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}
	}
	return true;
}

// ポリゴンの終了
void UninitPolygon(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	for (int count = 0; count < TEX_MAX; count++)
	{
		if (g_pTexture[count] != NULL)
		{
			g_pTexture[count]->Release();
			g_pTexture[count] = NULL;
		}
	}
}

// ポリゴンの更新
void UpdatePolygon(void)
{

}

void SetPolygonColor(D3DCOLOR nColor)
{
	color = nColor;
}

void SetTexture(int nNumTex)
{
	TexNum = nNumTex;
}


// ポリゴンの描画
void DrawPolygon(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, bool bAffine)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		return;
	}

	if (bAffine)
	{
		CreateVertexAffine(dx, dy, dw, dh, tcx, tcy, tcw, tch);
	}
	else
	{
		CreateVertex(dx, dy, dw, dh, tcx, tcy, tcw, tch);
	}


	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));

	// FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	////
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	////
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 20);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetTexture
	(
		0,
		g_pTexture[TexNum]
	);
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLEFAN,
		0,
		2
	);
}

void CreateVertex(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	int tw = TextureMessage[TexNum].width;
	int th = TextureMessage[TexNum].height;
	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;



	pV[0].pos = D3DXVECTOR4(dx, dy, g_Dcounterx, g_Dcountery);
	pV[1].pos = D3DXVECTOR4(dx + dw, dy, g_Dcounterx, g_Dcountery);
	pV[2].pos = D3DXVECTOR4(dx + dw, dy + dh, g_Dcounterx, g_Dcountery);
	pV[3].pos = D3DXVECTOR4(dx, dy + dh, g_Dcounterx, g_Dcountery);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u1, v1);
	pV[3].texcoord = D3DXVECTOR2(u0, v1);

	g_pVertexBuffer->Unlock();
}

void CreateVertexAffine(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);


	float x = (0.0f - g_fRotationOffsetX)*g_fScaleX + g_fScaleOffsetX;
	float x_w = (dw - g_fRotationOffsetX)*g_fScaleX + g_fScaleOffsetX;
	float y = (0.0f - g_fRotationOffsetY)*g_fScaleY + g_fScaleOffsetY;
	float y_h = (dh - g_fRotationOffsetY)*g_fScaleY + g_fScaleOffsetY;

	float fRotationOffsetX = g_fRotationOffsetX;
	float fRotationOffsetY = g_fRotationOffsetY;
	x -= fRotationOffsetX;
	x_w -= fRotationOffsetX;
	y -= fRotationOffsetY;
	y_h -= fRotationOffsetY;
	dx += fRotationOffsetX - 0.5f;
	dy += fRotationOffsetY - 0.5f;

	//float fRotationOffsetX = (g_fRotationOffsetX-g_fScaleOffsetX)*g_fScaleX;
	//float fRotationOffsetY = (g_fRotationOffsetY - g_fScaleOffsetY)*g_fScaleY;
	//x -= fRotationOffsetX;
	//x_w -= fRotationOffsetX;
	//y -= fRotationOffsetY;
	//y_h -= fRotationOffsetY;
	//dx += fRotationOffsetX - 0.5f;
	//dy += fRotationOffsetY - 0.5f;

	int tw = TextureMessage[TexNum].width;
	int th = TextureMessage[TexNum].height;
	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;



	pV[0].pos = D3DXVECTOR4(dx + x  *cosf(g_fPolygonAngle) - y  *sinf(g_fPolygonAngle), dy + x  *sinf(g_fPolygonAngle) + y  *cosf(g_fPolygonAngle), g_Dcounterx, g_Dcountery);//3d->
	pV[1].pos = D3DXVECTOR4(dx + x_w*cosf(g_fPolygonAngle) - y  *sinf(g_fPolygonAngle), dy + x_w*sinf(g_fPolygonAngle) + y  *cosf(g_fPolygonAngle), g_Dcounterx, g_Dcountery);
	pV[2].pos = D3DXVECTOR4(dx + x_w*cosf(g_fPolygonAngle) - y_h*sinf(g_fPolygonAngle), dy + x_w*sinf(g_fPolygonAngle) + y_h*cosf(g_fPolygonAngle), g_Dcounterx, g_Dcountery);
	pV[3].pos = D3DXVECTOR4(dx + x  *cosf(g_fPolygonAngle) - y_h*sinf(g_fPolygonAngle), dy + x  *sinf(g_fPolygonAngle) + y_h*cosf(g_fPolygonAngle), g_Dcounterx, g_Dcountery);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u1, v1);
	pV[3].texcoord = D3DXVECTOR2(u0, v1);

	g_pVertexBuffer->Unlock();
}


void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fPolygonAngle = angle;
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
}

void SetPolygonScale(float cx, float cy, float sx, float sy)
{
	g_fScaleOffsetX = cx;
	g_fScaleOffsetY = cy;
	g_fScaleX = sx;
	g_fScaleY = sy;
}

void SetDUIChange(int num)
{
	if (num==2)
	{
		g_Dcounterx = 1.0f;
		g_Dcountery = 1.0f;
	}
	if (num == 3)
	{
		g_Dcounterx = 0.5f;
		g_Dcountery = 1.0f;
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 20);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}
}