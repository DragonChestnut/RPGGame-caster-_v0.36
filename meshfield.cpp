#include "meshfield.h"
#include "main.h"
#include "input.h"

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static LPDIRECT3DTEXTURE9 g_pTexture[MESH_FIELD_MAX] = { NULL };

static int TexNum = 0;

static int FieldNumX = 75;
static int FieldNumZ = 20;

static float FieldSizeX = 150.0f;
static float FieldSizeZ = 40.0f;

static VERTEX3D *g_v;
static WORD *g_index;

bool InitMeshField(void)
{

	if (!SetMeshSize(FieldSizeX, FieldSizeZ, FieldNumX, FieldNumZ))
	{
		return false;
	}
	return true;
}

void UninitMeshField(void)
{

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

	for (int count = 0; count < MESH_FIELD_MAX; count++)
	{
		if (g_pTexture[count] != NULL)
		{
			g_pTexture[count]->Release();
			g_pTexture[count] = NULL;
		}
	}
	delete g_index;
	delete g_v;
}

void UpdateMeshField(void)
{
	D3DXMatrixTranslation(&g_mtxfield, 0.f, 0.f, 0.f);
}

void DrawMeshField(void)
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

	int fieldsizex = FieldSizeX / FieldNumX;
	int fieldsizez= FieldSizeZ/ FieldNumZ;

	for (int z = 0; z <= FieldNumZ; z++)
	{
		for (int x = 0; x <FieldNumX + 1; x++)
		{
			g_v[z*(FieldNumX + 1) + x].pos.x = ((fieldsizex*x) - (FieldSizeX / 2));
			g_v[z*(FieldNumX + 1) + x].pos.y = 0;
			g_v[z*(FieldNumX + 1) + x].pos.z = ((FieldSizeZ / 2)-(fieldsizez*z));
			g_v[z*(FieldNumX + 1) + x].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_v[z*(FieldNumX + 1) + x].texcoord.x = float(x);
			g_v[z*(FieldNumX + 1) + x].texcoord.y= float(z);
			g_v[z*(FieldNumX + 1) + x].way.x = 0.0f;
			g_v[z*(FieldNumX + 1) + x].way.y = 1.0f;
			g_v[z*(FieldNumX + 1) + x].way.z = 0.0f;
		}
	}

	memcpy(&pV[0], &g_v[0], sizeof(VERTEX3D) * ((FieldNumX + 1)*(FieldNumZ + 1)));

	g_pVertexBuffer->Unlock();

	int index_plus = 0;
	for (int z = 0;  z< FieldNumZ; z++)
	{
		for (int x = 0; x <= FieldNumX; x++)
		{
			g_index[index_plus] = (FieldNumX + 1)*(z + 1)+x;
			g_index[index_plus + 1] = (FieldNumX + 1)*z+x;
			index_plus += 2;
		}
		if (z!=FieldNumZ-1)
		{
			g_index[index_plus] = g_index[index_plus - 1];
			g_index[index_plus + 1] = (FieldNumX + 1)*(z + 2);
			index_plus += 2;
		}
	}

	int vindex = 0;
	if (FieldNumZ >= 2)
	{
		vindex = (FieldNumX * 2 + 3)*FieldNumZ + FieldNumZ - 2;
	}
	else
	{
		vindex = (FieldNumX + 1)*(FieldNumZ + 1);
	}

		memcpy(&pIndex[0], &g_index[0], sizeof(WORD) * vindex);

		g_pIndexBuffer->Unlock();

		pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
		pDevice->SetIndices(g_pIndexBuffer);

		//FVFの設定
		pDevice->SetFVF(FVF_VERTEX3D);
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		//行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxfield);

		pDevice->SetTexture
		(
			0,
			g_pTexture[TexNum]
		);
		
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (FieldNumX + 1)*(FieldNumZ + 1), 0, vindex-2);
}

bool SetMeshSize(float w, float h, int wnum, int hnum)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	FieldNumX = wnum;
	FieldNumZ = hnum;
	FieldSizeX = w;
	FieldSizeZ = h;
	int vSize = (FieldNumX + 1)*(FieldNumZ + 1);
	g_v = new VERTEX3D[vSize];
	int vindex = 0;
	if (FieldNumZ >= 2)
	{
		vindex = (FieldNumX * 2 + 3)*FieldNumZ + FieldNumZ - 2;
	}
	else
	{
		vindex = (FieldNumX + 1)*(FieldNumZ + 1);
	}
	g_index = new WORD[vindex];
	for (int count = 0; count < MESH_FIELD_MAX; count++)
	{
		HRESULT hr;

		hr = D3DXCreateTextureFromFile
		(
			pDevice,
			TextureMeshMessage[count].filename,
			&g_pTexture[count]
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr = pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX3D) * vSize,
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
			sizeof(WORD) * vindex,
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
	}
	return true;
}


void SetMeshFildTexNum(int Texnum)
{
	TexNum = Texnum;
}