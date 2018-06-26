#include "main.h"
#include "camera.h"
#include "input.h"
#include "Billboard.h"


static LPDIRECT3DTEXTURE9 g_pTexture[TEX_BILLBOARD_MAX] = { NULL };
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;


static D3DCOLOR color = 0xffffffff;
static int TexNum = 1;
static float TexX0[MAX_BILLBOARD] = { 0.f, };
static float TexY0[MAX_BILLBOARD] = { 0.f, };
static float TexX1[MAX_BILLBOARD] = { 0.f, };
static float TexY1[MAX_BILLBOARD] = { 0.f, };
//
BILLBOARD billboard[MAX_BILLBOARD];


bool InitBillboard(void)
{
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		TexX0[i] = 0.0f;
		TexY0[i] = 0.0f;
		TexX1[i] = 1.0f;
		TexY1[i] = 1.0f;
	}
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	HRESULT hr;
	for (int count = 0; count < TEX_BILLBOARD_MAX; count++)
	{
		hr = D3DXCreateTextureFromFile
		(
			pDevice,
			BillboardTextureMessage[count].filename,
			&g_pTexture[count]
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}
	}
	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX3D,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファが作れなかった", "エラー", MB_OK);
		return false;
	}

	hr = pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * 6 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファが作れなかった", "エラー", MB_OK);
		return false;
	}
	//
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		billboard[i].BillboardXYZ.x = 0.f;
		billboard[i].BillboardXYZ.y = 0.f;
		billboard[i].BillboardXYZ.z = 0.f;
		billboard[i].ISbnum = TEX_BILLBOARD_NULL;
		//
		billboard[i].BillboardHeight = 0.f;
		billboard[i].BillboardWidth = 0.f;
		billboard[i].BillboardTexNum = 0;
		billboard[i].ISBillboard = false;
		//
	}
	return true;
}

void UninitBillboard(void)
{
	for (int count = 0; count < TEX_BILLBOARD_MAX; count++)
	{
		if (g_pTexture[count] != NULL)
		{
			g_pTexture[count]->Release();
			g_pTexture[count] = NULL;
		}
	}
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}


void UpdateBillboard(void)
{
	//
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (billboard[i].ISBillboard)
		{
			D3DXMatrixTranslation(&billboard[i].MtxBillboard, billboard[i].BillboardXYZ.x, billboard[i].BillboardXYZ.y, billboard[i].BillboardXYZ.z);
			D3DXMATRIX mtxView;
			mtxView = GetView();
			mtxView._14 = 0.0f;
			mtxView._24 = 0.0f;
			mtxView._34 = 0.0f;
			mtxView._41 = 0.0f;
			mtxView._42 = 0.0f;
			mtxView._43 = 0.0f;
			D3DXMatrixTranspose(&mtxView, &mtxView);
			D3DXMatrixMultiply(&billboard[i].MtxBillboard, &mtxView, &billboard[i].MtxBillboard);
		}
	}
	//g_mtxTree._14 = 0.0f;
	//g_mtxTree._24 = 0.0f;
	//g_mtxTree._34 = 0.0f;
	//D3DXMatrixTranspose(&g_mtxTree, &g_mtxTree);
	//////逆行列の作り方
	////D3DXMatrixInverse(出力先アドレス, NULL, 入力先アドレス)

	////11 12 13 14
	////21 22 23 24
	////31 32 33 34
	////41 42 43 44
	////転置行列の作り方
	////D3DXMatrixTranspose(出力先アドレス,入力先アドレス)
	////mtxViewInv._14 = 0.0f;
	////mtxViewInv._24 = 0.0f;
	////mtxViewInv._34 = 0.0f;
	////_12,_32を転置しなければ、垂直方向は無視

}
void DrawBillboard(void)
{
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (billboard[i].ISBillboard)
		{
			VERTEX3D* pV;
			g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
			LPWORD pIndex;
			g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

			LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
			if (pDevice == NULL)
			{
				return;
			}

			VERTEX3D v[4];
			v[0].pos.x = -billboard[i].BillboardWidth / 2;
			v[0].pos.y = billboard[i].BillboardHeight;
			v[0].pos.z = 0.0f;
			v[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			v[0].texcoord.x = TexX0[i];
			v[0].texcoord.y = TexY0[i];
			v[0].way.x = 0.0f;
			v[0].way.y = 0.0f;
			v[0].way.z = -1.0f;
			v[1].pos.x = billboard[i].BillboardWidth / 2;
			v[1].pos.y = billboard[i].BillboardHeight;
			v[1].pos.z = 0.0f;
			v[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			v[1].texcoord.x = TexX1[i];
			v[1].texcoord.y = TexY0[i];
			v[1].way.x = 0.0f;
			v[1].way.y = 0.0f;
			v[1].way.z = -1.0f;
			v[2].pos.x = billboard[i].BillboardWidth / 2;
			v[2].pos.y = 0.0f;
			v[2].pos.z = 0.0f;
			v[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			v[2].texcoord.x = TexX1[i];
			v[2].texcoord.y = TexY1[i];
			v[2].way.x = 0.0f;
			v[2].way.y = 0.0f;
			v[2].way.z = -1.0f;
			v[3].pos.x = -billboard[i].BillboardWidth / 2;
			v[3].pos.y = 0.0f;
			v[3].pos.z = 0.0f;
			v[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			v[3].texcoord.x = TexX0[i];
			v[3].texcoord.y = TexY1[i];
			v[3].way.x = 0.0f;
			v[3].way.y = 0.0f;
			v[3].way.z = -1.0f;

			memcpy(&pV[0], &v[0], sizeof(VERTEX3D) * 4);

			g_pVertexBuffer->Unlock();

			WORD index[] = {
				0,1,2,
				0,2,3,
			};

			memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);

			g_pIndexBuffer->Unlock();

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
			pDevice->SetIndices(g_pIndexBuffer);

			//FVFの設定
			pDevice->SetFVF(FVF_VERTEX3D);
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			//
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			//
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 20);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			//
			//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);//UI:FALSE,other:TURE
			//行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &billboard[i].MtxBillboard);
			pDevice->SetTexture
			(
				0,
				g_pTexture[billboard[i].ISbnum]
			);

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		}
	}
}

//Initの後ろ
void CreateBillboardWHN(int Billboardnum,float width, float height,int TexNumAll)
{
	if (!billboard[Billboardnum].ISBillboard)
	{
		billboard[Billboardnum].BillboardWidth = width;
		billboard[Billboardnum].BillboardHeight = height;
		billboard[Billboardnum].BillboardTexNum = TexNumAll;
		billboard[Billboardnum].ISBillboard = true;
	}
}

//Drawの前
void SetBillboardISTexNum(int Billboardnum, TEXTURE_BILLBOARD_NUM ISTexBillboardNum)
{
	billboard[Billboardnum].ISbnum = ISTexBillboardNum;
}

void SetBillboardPos(int Billboardnum, float x,float y,float z)
{
	billboard[Billboardnum].BillboardXYZ.x = x;
	billboard[Billboardnum].BillboardXYZ.y = y;
	billboard[Billboardnum].BillboardXYZ.z = z;
}

void DestroyBillboard(int Billboardnum)
{
	billboard[Billboardnum].ISBillboard = false;
	billboard[Billboardnum].BillboardXYZ.x = 0.f;
	billboard[Billboardnum].BillboardXYZ.y = 0.f;
	billboard[Billboardnum].BillboardXYZ.z = 0.f;
	billboard[Billboardnum].ISbnum = TEX_BILLBOARD_NULL;
	//
	billboard[Billboardnum].BillboardHeight = 0.f;
	billboard[Billboardnum].BillboardWidth = 0.f;
	billboard[Billboardnum].BillboardTexNum = 0;
}


D3DXVECTOR3 GetBillboardPos(int Billboardnum)
{
	return billboard[Billboardnum].BillboardXYZ;
}

void SetBillboardTexCoord(int Billboardnum,float x0, float y0, float x1, float y1)
{
	TexX0[Billboardnum] = x0;
	TexY0[Billboardnum] = y0;
	TexX1[Billboardnum] = x1;
	TexY1[Billboardnum] = y1;
}





//不透明ポリゴンはカメラから近い順に描く
//半透明ポリゴンはカメラから遠い順に描く
//D3DXVec3Length(物の座標ーカメラ座標);
//D3DXVec3LengthSq
//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE,D3DRS_ALPHAREF, 値, D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//ZバッファONOFF
//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
//Zテスト
//D3DRS_ZFUNC,D3DCMP_~

//影
//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);