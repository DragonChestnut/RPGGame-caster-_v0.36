#include "shadow.h"
#include "Camera.h"
#include "main.h"
#include "input.h"
#include"xmodel.h"
#include "Billboard.h"
#include "character.h"
//***************************************************************************************
//	グローバル変数宣言
//***************************************************************************************
static SHADOWS g_pShadows[SHADOW_MAX];
static LPDIRECT3DVERTEXBUFFER9 g_pShadowVertexBuffer3D = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pShadowIndexBuffer = NULL;
static const SHADOW_TEXTURE g_pShadowTexture[SHADOW_TEXTURE_MAX] = { { SHADOW_TEXTURE_FILENAME1 , 32, 32 } };
static LPDIRECT3DTEXTURE9  g_pShadowTextures[SHADOW_TEXTURE_MAX] = { NULL };
static WORD g_ShadowIndex[SHADOW_INDEX_MAXPOINT];
static SHADOW_VERTEX g_Shadowv[SHADOW_V_MAXPOINT];
static int g_nIndexPoint = 0;
static int g_Color_r[SHADOW_MAX];
static int g_Color_g[SHADOW_MAX];
static int g_Color_b[SHADOW_MAX];
static int g_Color_a[SHADOW_MAX];
static SHADOW_TEXTURE_ENUM g_eTexNum;
static SHADOW_ID g_eTypeNum;

//逆行列　D3DXMatrixInverse(出力アドレス,NULL,入力先アドレス);
//転置行列 D3DXMatrixTranspose(出力アドレス,入力先アドレス);



bool InitShadow(void)
{
	HRESULT hr;
	hr = ReadShadow();
	InitShadowData();

	return hr;
}
void UninitShadow(void)
{
	if (g_pShadowVertexBuffer3D)
	{
		g_pShadowVertexBuffer3D->Release();
		g_pShadowVertexBuffer3D = NULL;
	}
	if (g_pShadowIndexBuffer)
	{
		g_pShadowIndexBuffer->Release();
		g_pShadowIndexBuffer = NULL;
	}
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (g_pShadowTextures[i])
		{
			g_pShadowTextures[i]->Release();
			g_pShadowTextures[i] = NULL;
		}
	}
}
void UpdateShadow(void)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (g_pShadows[i].ISshadow)
		{
			D3DXMatrixTranslation(&g_pShadows[i].MtxShadowT,
				g_pShadows[i].pos.x,
				g_pShadows[i].pos.y,
				g_pShadows[i].pos.z);
			D3DXMatrixScaling(&g_pShadows[i].MtxShadowS, g_pShadows[i].Scaling.x, g_pShadows[i].Scaling.y, g_pShadows[i].Scaling.z);
			D3DXMatrixMultiply(&g_pShadows[i].MtxShadow, &g_pShadows[i].MtxShadowS, &g_pShadows[i].MtxShadowT);
		}
	}
}

void DrawShadow(void)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (g_pShadows[i].ISshadow)
		{
			LPDIRECT3DDEVICE9 pDevice3d = GetD3DDevice();
			//
			pDevice3d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			LPWORD pIndex;
			SHADOW_VERTEX* pV;


			//各種類行列の設定
			pDevice3d->SetTransform(D3DTS_WORLD, &g_pShadows[i].MtxShadow);


			g_pShadowVertexBuffer3D->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);



			memcpy(&pV[0], &g_Shadowv[0], sizeof(SHADOW_VERTEX) * SHADOW_V_MAXPOINT);

			g_pShadowVertexBuffer3D->Unlock();


			g_pShadowIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);


			memcpy(&pIndex[0], &g_ShadowIndex[0], sizeof(WORD) * SHADOW_INDEX_MAXPOINT);
			g_pShadowIndexBuffer->Unlock();

			for (int y = 0; y < (SHADOW_Y_NUM + 1); y++)
			{
				for (int x = 0; x < (SHADOW_X_NUM + 1); x++)
				{
					g_Shadowv[y * (SHADOW_X_NUM + 1) + x] = {
						D3DXVECTOR3(-SHADOW_WIDTH + SHADOW_WIDTH / 2 + SHADOW_IDENTITY_WIDTH*x,//x
						0,//y
						SHADOW_HEIGHT - SHADOW_HEIGHT / 2 - SHADOW_IDENTITY_HEIGHT*y),//z
						D3DXVECTOR3(0,1.f,0),
						D3DCOLOR_RGBA(255,255,255,200),
						//D3DCOLOR_RGBA(g_Color_r[i] , g_Color_g[i], g_Color_b[i],g_Color_a[i]),
						D3DXVECTOR2(x,y)
					};
				}
			}

			g_nIndexPoint = 0;
			for (int y = 0; y < SHADOW_Y_NUM; y++)
			{
				for (int x = 0; x <= SHADOW_X_NUM; x++)
				{
					g_ShadowIndex[g_nIndexPoint] = (SHADOW_X_NUM + 1)*(y + 1) + x;
					g_ShadowIndex[g_nIndexPoint + 1] = (SHADOW_X_NUM + 1)*y + x;
					g_nIndexPoint += 2;

				}
				if (y != SHADOW_Y_NUM - 1)
				{
					g_ShadowIndex[g_nIndexPoint] = g_ShadowIndex[g_nIndexPoint - 1];
					g_ShadowIndex[g_nIndexPoint + 1] = (SHADOW_X_NUM + 1)*(y + 2);
					g_nIndexPoint += 2;
				}
			}
			pDevice3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			pDevice3d->SetStreamSource(0, g_pShadowVertexBuffer3D, 0, sizeof(SHADOW_VERTEX));
			pDevice3d->SetIndices(g_pShadowIndexBuffer);

			//テクスチャ設定
			pDevice3d->SetTexture(0, g_pShadowTextures[g_eTexNum]);

			//FVFの設定
			pDevice3d->SetFVF(FVF_VERTEX3D);
			pDevice3d->SetRenderState(D3DRS_LIGHTING, TRUE);


			//DrawPrimitiveUP 遅い、簡単
			pDevice3d->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SHADOW_V_MAXPOINT, 0, SHADOW_INDEX_MAXPOINT - 2);
			//
			pDevice3d->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
	}
}


bool ReadShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice3d = GetD3DDevice();
	for (int i = 0; i < SHADOW_TEXTURE_MAX; i++)
	{
		HRESULT hr3D;

		hr3D = D3DXCreateTextureFromFile(pDevice3d,
			g_pShadowTexture[i].fileName,//ファイル名
			&g_pShadowTextures[i]);

		if (FAILED(hr3D))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr3D = pDevice3d->CreateVertexBuffer(sizeof(SHADOW_VERTEX) * SHADOW_V_MAXPOINT, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pShadowVertexBuffer3D, NULL);
		if (FAILED(hr3D))
		{
			MessageBox(NULL, "頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}
		hr3D = pDevice3d->CreateIndexBuffer(sizeof(WORD) * SHADOW_INDEX_MAXPOINT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pShadowIndexBuffer, NULL);
		if (FAILED(hr3D))
		{
			MessageBox(NULL, "インデックス頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}
	}

	

	return true;

}

void SetShadowColor(int shadownum,int r, int g, int b, int a)
{
	g_Color_r[shadownum]=r;
	g_Color_g[shadownum]=g;
	g_Color_b[shadownum]=b;
	g_Color_a[shadownum]=a;
}
void SetShadowTex(SHADOW_TEXTURE_ENUM TexNum)
{
	g_eTexNum = TexNum;
}
void InitShadowData(void)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		g_pShadows[i].ISshadow = false;
		g_pShadows[i].pos.x = 0;
		g_pShadows[i].pos.y = 0;
		g_pShadows[i].pos.z = 0;
		g_pShadows[i].Scaling.x = 0;
		g_pShadows[i].Scaling.y = 0;
		g_pShadows[i].Scaling.z = 0;
		g_Color_r[i] = 255;
		g_Color_g[i] = 255;
		g_Color_b[i] = 255;
		g_Color_a[i] = 255;
	}

}

void SetShadowPos(int shadownum, float x, float y, float z)
{
	g_pShadows[shadownum].pos.x = x;
	g_pShadows[shadownum].pos.y = y;
	g_pShadows[shadownum].pos.z = z;
	g_pShadows[shadownum].ISshadow = true;
}

void SetShadowScaling(int shadownum, float x, float y, float z)
{
	g_pShadows[shadownum].Scaling.x = x;
	g_pShadows[shadownum].Scaling.y = y;
	g_pShadows[shadownum].Scaling.z = z;
}

void DestroyShadow(int shadownum)
{
	g_pShadows[shadownum].ISshadow = false;
	g_pShadows[shadownum].pos.x = 0;
	g_pShadows[shadownum].pos.y = 0;
	g_pShadows[shadownum].pos.z = 0;
	g_pShadows[shadownum].Scaling.x = 0;
	g_pShadows[shadownum].Scaling.y = 0;
	g_pShadows[shadownum].Scaling.z = 0;
}