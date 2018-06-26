#include "effect.h"
#include "character.h"
#include "Game.h"

static EFFECT g_effect[MAX_EFFECT];

void InitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].EffectPos.x = 0.f;
		g_effect[i].EffectPos.y = 0.f;
		g_effect[i].EffectPos.z = 0.f;
		g_effect[i].Effectx0 = 0.000f;
		g_effect[i].Effectx1 = 0.000f;
		g_effect[i].EffectAnimeCounter = 0;
		g_effect[i].EffectISAnime = 1;
		g_effect[i].EffectMaxAnime = 2;
		g_effect[i].EffectDirection = 0;
		g_effect[i].EffectType = CHARACTER_EFFECT_NULL;
		g_effect[i].ISEffect = false;
		g_effect[i].EffectChangeSpeed = 0;
		//
		g_effect[i].EffectStop = false;
		g_effect[i].EffectStopAnimeNum = 0;
		//
		g_effect[i].EffectXspeed = 0;
		g_effect[i].EffectZspeed = 0;
	}
}
void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].EffectPos.x = 0.f;
		g_effect[i].EffectPos.y = 0.f;
		g_effect[i].EffectPos.z = 0.f;
		g_effect[i].Effectx0 = 0.000f;
		g_effect[i].Effectx1 = 0.000f;
		g_effect[i].EffectAnimeCounter = 0;
		g_effect[i].EffectISAnime = 1;
		g_effect[i].EffectMaxAnime = 2;
		g_effect[i].EffectDirection = 0;
		g_effect[i].EffectType = CHARACTER_EFFECT_NULL;
		g_effect[i].ISEffect = false;
		g_effect[i].EffectChangeSpeed = 0;
		//
		g_effect[i].EffectStop = false;
		g_effect[i].EffectStopAnimeNum = 0;
		//
		g_effect[i].EffectXspeed = 0;
		g_effect[i].EffectZspeed = 0;
	}
}
void UpdateEffect(void)
{
	//new effect”»’è
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].ISEffect)
		{
			if (g_effect[i].EffectAnimeCounter >= g_effect[i].EffectChangeSpeed)
			{
				g_effect[i].EffectISAnime++;
				g_effect[i].EffectAnimeCounter = 0;
			}
			g_effect[i].EffectAnimeCounter++;
			g_effect[i].Effectx0 = (g_effect[i].EffectISAnime-1) / (float)g_effect[i].EffectMaxAnime;
			g_effect[i].Effectx1 = (g_effect[i].EffectISAnime) / (float)g_effect[i].EffectMaxAnime;
			//
			switch (g_effect[i].EffectType)
			{
			case 0:SetBillboardTexCoord(BILL_FLAME, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 1:SetBillboardTexCoord(BILL_AQUA, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 2:SetBillboardTexCoord(BILL_THUNDER, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 3:SetBillboardTexCoord(BILL_MAGIC_SQUARE_00, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 4:SetBillboardTexCoord(BILL_MAGIC_SQUARE_01, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 5:SetBillboardTexCoord(BILL_MAGIC_SQUARE_02, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 6:SetBillboardTexCoord(BILL_RUA00, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			case 7:SetBillboardTexCoord(BILL_RUA01, g_effect[i].Effectx0, 0.0f, g_effect[i].Effectx1, 1.0f); break;
			default:
				break;
			}
			if (g_effect[i].EffectISAnime > g_effect[i].EffectMaxAnime)
			{
				if (!g_effect[i].EffectStop)
				{
					DestroyEffect(g_effect[i].EffectType);
				}
				else
				{
					g_effect[i].EffectISAnime = g_effect[i].EffectMaxAnime - g_effect[i].EffectStopAnimeNum;
				}
			}
		}
	}
}
void DrawEffect(void)
{

}

void CreateEffect(CHARACTER_EFFECT_NUM EffectType, int MaxEffectAnimeNum,int EffectChangeSpeed, int name, float EffectXspeed, float EffectZspeed, bool EffectStopSwitch, int EffectStopAnimeNum)
{
	if (name== NAME_CHARACTER)
	{
		if (!g_effect[EffectType].ISEffect)
		{
			g_effect[EffectType].ISEffect = true;
			g_effect[EffectType].EffectType = EffectType;
			g_effect[EffectType].EffectMaxAnime = MaxEffectAnimeNum;
			g_effect[EffectType].EffectDirection = GetCharacterDirection();
			g_effect[EffectType].EffectPos = GetCharacterPos();
			g_effect[EffectType].EffectChangeSpeed = EffectChangeSpeed;
			g_effect[EffectType].EffectStop = EffectStopSwitch;
			g_effect[EffectType].EffectStopAnimeNum = EffectStopAnimeNum;
			g_effect[EffectType].EffectXspeed = EffectXspeed;
			g_effect[EffectType].EffectZspeed = EffectZspeed;
			SetEffectBill(EffectType, g_effect[EffectType].EffectDirection, g_effect[EffectType].EffectPos);
		}
	}
	else if(name == NAME_ENEMY_01)
	{

	}
}

void DestroyEffect(CHARACTER_EFFECT_NUM EffectType)
{
	switch (EffectType)
	{
	case 0:
	{
		DestroyBillboard(BILL_FLAME);
	}break;
	case 1:
	{
		DestroyBillboard(BILL_AQUA);
	}break;
	case 2:
	{
		DestroyBillboard(BILL_THUNDER);
	}break;
	case 3:
	{
		DestroyBillboard(BILL_MAGIC_SQUARE_00);
	}break;
	case 4:
	{
		DestroyBillboard(BILL_MAGIC_SQUARE_01);
	}break;
	case 5:
	{
		DestroyBillboard(BILL_MAGIC_SQUARE_02);
	}break;
	case 6:
	{
		DestroyBillboard(BILL_RUA00);
	}break;
	case 7:
	{
		DestroyBillboard(BILL_RUA01);
	}break;
	default:
		break;
	}
	g_effect[EffectType].EffectPos.x = 0.f;
	g_effect[EffectType].EffectPos.y = 0.f;
	g_effect[EffectType].EffectPos.z = 0.f;
	g_effect[EffectType].Effectx0 = 0.000f;
	g_effect[EffectType].Effectx1 = 0.000f;
	g_effect[EffectType].EffectAnimeCounter = 0;
	g_effect[EffectType].EffectISAnime = 1;
	g_effect[EffectType].EffectMaxAnime = 2;
	g_effect[EffectType].EffectDirection = 0;
	g_effect[EffectType].EffectType = CHARACTER_EFFECT_NULL;
	g_effect[EffectType].ISEffect = false;
	g_effect[EffectType].EffectChangeSpeed = 0;
	//
	g_effect[EffectType].EffectStop = false;
	g_effect[EffectType].EffectStopAnimeNum = 0;
	//
	g_effect[EffectType].EffectXspeed = 0;
	g_effect[EffectType].EffectZspeed = 0;
}

int GetEffectISAnime(CHARACTER_EFFECT_NUM EffectType)
{
	return g_effect[EffectType].EffectISAnime;
}

void SetEffectBill(CHARACTER_EFFECT_NUM EffectType, int EffectDirection, D3DXVECTOR3 EffectPos)
{
	if (EffectDirection == 0)
	{
		switch (EffectType)
		{
		case 0:
		{
			CreateBillboardWHN(BILL_FLAME, 3.2f, 2.16f, 10);
			SetBillboardISTexNum(BILL_FLAME, TEX_EFFECT_FLAME_R);
			SetBillboardPos(BILL_FLAME, EffectPos.x + 3.6f, EffectPos.y+0.5f, EffectPos.z);
		}break;
		case 1:
		{
			CreateBillboardWHN(BILL_AQUA, 3.2f, 3.2f, 10);
			SetBillboardISTexNum(BILL_AQUA, TEX_EFFECT_AQUA_R);
			SetBillboardPos(BILL_AQUA, EffectPos.x + 3.6f, EffectPos.y, EffectPos.z);
		}break;
		case 2:
		{
			CreateBillboardWHN(BILL_THUNDER, 3.7f, 3.7f, 16);
			SetBillboardISTexNum(BILL_THUNDER, TEX_EFFECT_THUNDER_R);
			SetBillboardPos(BILL_THUNDER, EffectPos.x + 3.1f, EffectPos.y-0.7f, EffectPos.z);
		}break;
		case 3:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_00, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_00, TEX_EFFECT_MAGIC_SQUARE_00_R);
			SetBillboardPos(BILL_MAGIC_SQUARE_00, EffectPos.x + 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 4:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_01, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_01, TEX_EFFECT_MAGIC_SQUARE_01_R);
			SetBillboardPos(BILL_MAGIC_SQUARE_01, EffectPos.x + 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 5:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_02, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_02, TEX_EFFECT_MAGIC_SQUARE_02_R);
			SetBillboardPos(BILL_MAGIC_SQUARE_02, EffectPos.x + 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 6:
		{
			CreateBillboardWHN(BILL_RUA00, 1.8f, 3.2f, 8);
			SetBillboardISTexNum(BILL_RUA00, TEX_EFFECT_RUA00_R);
			SetBillboardPos(BILL_RUA00, EffectPos.x + 1.0f, EffectPos.y-0.3f, EffectPos.z);
		}break;
		case 7:
		{
			CreateBillboardWHN(BILL_RUA01, 1.8f, 3.2f, 8);
			SetBillboardISTexNum(BILL_RUA01, TEX_EFFECT_RUA01_R);
			SetBillboardPos(BILL_RUA01, EffectPos.x + 1.5f, EffectPos.y - 0.3f, EffectPos.z);
		}break;
		default:
			break;
		}
	}
	else
	{
		switch (EffectType)
		{
		case 0:
		{
			CreateBillboardWHN(BILL_FLAME, 3.2f, 2.16f, 10);
			SetBillboardISTexNum(BILL_FLAME, TEX_EFFECT_FLAME_L);
			SetBillboardPos(BILL_FLAME, EffectPos.x - 3.6f, EffectPos.y + 0.5f, EffectPos.z);
		}break;
		case 1:
		{
			CreateBillboardWHN(BILL_AQUA, 3.2f,3.2f, 10);
			SetBillboardISTexNum(BILL_AQUA, TEX_EFFECT_AQUA_L);
			SetBillboardPos(BILL_AQUA, EffectPos.x - 3.6f, EffectPos.y, EffectPos.z);
		}break;
		case 2:
		{
			CreateBillboardWHN(BILL_THUNDER, 3.7f, 3.7f, 16);
			SetBillboardISTexNum(BILL_THUNDER, TEX_EFFECT_THUNDER_L);
			SetBillboardPos(BILL_THUNDER, EffectPos.x - 3.1f, EffectPos.y -0.7f, EffectPos.z);
		}break;
		case 3:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_00, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_00, TEX_EFFECT_MAGIC_SQUARE_00_L);
			SetBillboardPos(BILL_MAGIC_SQUARE_00, EffectPos.x - 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 4:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_01, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_01, TEX_EFFECT_MAGIC_SQUARE_01_L);
			SetBillboardPos(BILL_MAGIC_SQUARE_01, EffectPos.x - 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 5:
		{
			CreateBillboardWHN(BILL_MAGIC_SQUARE_02, 1.5f, 2.55f, 16);
			SetBillboardISTexNum(BILL_MAGIC_SQUARE_02, TEX_EFFECT_MAGIC_SQUARE_02_L);
			SetBillboardPos(BILL_MAGIC_SQUARE_02, EffectPos.x - 1.2f, EffectPos.y, EffectPos.z);
		}break;
		case 6:
		{
			CreateBillboardWHN(BILL_RUA00, 1.8f, 3.2f, 8);
			SetBillboardISTexNum(BILL_RUA00, TEX_EFFECT_RUA00_L);
			SetBillboardPos(BILL_RUA00, EffectPos.x - 1.f, EffectPos.y - 0.3f, EffectPos.z);
		}break;
		case 7:
		{
			CreateBillboardWHN(BILL_RUA01, 1.8f, 3.2f, 8);
			SetBillboardISTexNum(BILL_RUA01, TEX_EFFECT_RUA01_L);
			SetBillboardPos(BILL_RUA01, EffectPos.x - 1.5f, EffectPos.y - 0.3f, EffectPos.z);
		}break;
		default:
			break;
		}
	}
}
