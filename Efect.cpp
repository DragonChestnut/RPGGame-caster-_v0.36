//================================================
//	�G�t�F�N�g.cpp
//
//================================================

#include "main.h"
#include "Efect.h"
#include "Polygon.h"

namespace {
	//�G�t�F�N�g�p�̃e�N�X�`���ꎞ�ϐ�
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
	//�����`�F�b�N
	for (int i = 0; i < MAX_EFECT; i++)
	{
		if (!g_Efects[i].b_Efect)
		{
			continue;
		}
		int nAge = g_nEfectFrameCounter - g_Efects[i].nBirth;
		if (nAge >= g_Efects[i].nLimit)
		{//�����̏I���
			g_Efects[i].b_Efect = false;
		}
	}

	g_nEfectFrameCounter++;	
}

//====================================================
//	�G�t�F�N�g�̕`��
//====================================================
void DrawEfect(void)
{
	//���Z�����̐ݒ�֕ύX
	//SRC_RGB*SRC_��+DST_RGB*1�̌v�Z�i�ݒ�j
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
		//�G�t�F�N�g�`��
		//D3DXCOLOR�^�@=�@�N���X{float r,g,b,a}; a = 0.0~1.0
		//���Ӂ@D3DCOLOR �Ɓ@D3DXCOLOR �̃T�C�Y�͈Ⴄ
		
		//�J���[�̌v�Z
		//�N��ɂ���ă���ς���
		//�O�΁c�ŏ��̃��J���[
		//�����̔N��c�����O
		g_Efects[i].color = D3DXCOLOR(0.7, 0.7, 0.7, 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth),0.1)/ (g_Efects[i].nLimit));
		SetPolygonColor(g_Efects[i].color);
		SetPolygonScale(0, 0, 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit), 1 - max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit));
		SetPolygonRotation(0,0,0);
		DrawPolygon(g_Efects[i].vPos.x + (TEXTURE_W * (max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit)))/2,
			g_Efects[i].vPos.y + (TEXTURE_H * (max((g_nEfectFrameCounter - g_Efects[i].nBirth), 0.1) / (g_Efects[i].nLimit)))/2, 10, 10, 40, 0, 40, 40, true);

	}
	//�ʏ�̕`��ݒ�֖߂�
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
//	�G�t�F�N�g�̍쐬
//	float x,y ... ���W
//	color ... �F
//	nLimit ... ����
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
//	�G�t�F�N�g�p�̉摜�����ւ�
//
//void EfectTexture(EFECT_TEX tex)
//{
//	Efect_Tex = TEXTURE_PLAYWE_01 + tex;
//	SetTexture((TEXTURE_ENUM)Efect_Tex);
//}