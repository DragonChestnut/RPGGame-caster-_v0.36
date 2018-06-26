#include "Xmodel.h"
#include "main.h"
#include "camera.h"
#include "input.h"

static LPDIRECT3DTEXTURE9 g_pTexture[MODEL_MAX][MAX_TEX] = { NULL };


bool InitXmodel(void)
{
	LPD3DXMESH pTempMesh;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	LPD3DXBUFFER pAdjacency;
	for (int i = 0; i < MODEL_MAX; i++)
	{
		HRESULT hr;
		hr = D3DXLoadMeshFromX(ModelMessage[i].filename/*ファイル名*/, D3DXMESH_SYSTEMMEM, pDevice, &pAdjacency, &g_pMaterial[i], NULL, &g_nMaterialNum[i], &g_pMesh[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "ダイレクト３Dボックスの生成に失敗しました", "エラー", MB_OK);
			return false;
		}
			for (int num = 0; num < ModelMessage[i].meshnum; num++)
			{
				hr = D3DXCreateTextureFromFile
				(
					pDevice,
					TextureModelMessage[i][num].filename,
					&g_pTexture[i][num]
				);

				if (FAILED(hr))
				{
					MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
					return false;
				}
			}

		//メッシュの最適化
		hr = g_pMesh[i]->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);
		pAdjacency->Release();

		D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH];
		g_pMesh[i]->GetDeclaration(elements);
		hr = g_pMesh[i]->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pTempMesh);//Clone->pTempMesh
		g_pMesh[i]->Release();
		g_pMesh[i] = pTempMesh;
	}
	return true;
}
void UninitXmodel(void)
{

}
void UpdateXmodel(void)
{
	SetModelXYZ(MODEL_1, 4.0f, 0.0f, 0.0f);
	SetModelXYZ(MODEL_2, 0.0f, 0.0f, 0.0f);
	SetModelXYZ(MODEL_3, -4.0f, 0.0f, 0.0f);
	for (int count = 0; count < MODEL_MAX; count++)
	{
		D3DXMatrixTranslation(&g_mtxModel[count], g_x[count], g_y[count], g_z[count]);
	}

	//拡大
	D3DXMatrixScaling(&g_mtxtran1, 3.0f, 3.0f, 3.0f);

	//D3DXMatrixMultiply(&g_mtxModel2, &g_mtxModel2, &g_mtxtran1);
}
void DrawXmodel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int count = 0; count < MODEL_MAX; count++)
	{
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxModel[count]);
		for (int i = 0; i < g_nMaterialNum[count]; i++)
		{
			LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)g_pMaterial[i]->GetBufferPointer();
			pDevice->SetTexture
			(
				0,
				g_pTexture[count][i]
			);
			pMaterial[i].MatD3D.Ambient.a = 1.0f;
			pMaterial[i].MatD3D.Ambient.g = 1.0f;
			pMaterial[i].MatD3D.Ambient.b= 1.0f;
			pMaterial[i].MatD3D.Ambient.r = 1.0f;
			//pMaterial[i].pTextureFilename= "Xmodel/00tex_master.png";	
			g_pMesh[count]->DrawSubset(i);
		}
	}
}

void SetModelXYZ(MODEL_NUM modelnum, float x, float y, float z)
{
	g_x[modelnum] = x;
	g_y[modelnum] = y;
	g_z[modelnum] = z;
}
