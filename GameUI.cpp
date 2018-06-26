#include "GameUI.h"
#include "camera.h"
#include "polygon.h"
#include "character.h"
#include "Clock.h"
#include "sound.h"
#include "Enemy_Train.h"


#define SUPER_SKILL_MAX_ANIME (16)
#define SUPER_SKILL_CARD_MAX_ANIME (16)
#define SUPER_SKILL_MAGIC_MAX_ANIME (10)
#define SUPER_SKILL_CARD_MAX_SPEED (5)
#define SUPER_SKILL_MAGIC_MAX_SPEED (8)
#define UI_CHARACTER_MAX_ANIME (4)
#define CARD_MAX_COOL_TIME (360)

static bool SuperSkillSwitchFade;
static int FadeAlpha;
static bool SuperSkillSwitch;
static float SuperSkillX0;
static int SuperSkillAnimeCouter;
static int SuperSkillISAnime;
static float SuperSkillCutInX;

static float SuperSkillCardX0;
static int SuperSkillCardAnimeCouter;
static int SuperSkillCardISAnime;

static float SuperSkillMagicX0;
static int SuperSkillMagicAnimeCouter;
static int SuperSkillMagicISAnime;

static int SuperSkillCardAlpha;
static int SuperSkillLightAlpha;

static float UICharacterX0;
static int  UICharacterAnimeCouter;
static int UICharacterDoCounter;
static int UICharacterISAnime;
static bool UICharacterDoSwitch;

static int CardCoolTimeCounter;
static bool CardCoolTimeSwitch;

static int CardLightAlpha;
static int CardLightAlphaSwitch;

void InitGameUI(void)
{
	SuperSkillSwitch = false;
	FadeAlpha = 0;
	SuperSkillSwitchFade = false;
	SuperSkillX0 = 0.f;
	SuperSkillISAnime = 1;
	SuperSkillAnimeCouter = 0;
	SuperSkillCutInX = 10.f;

	SuperSkillCardX0=0.f;
	SuperSkillCardAnimeCouter=0;
	SuperSkillCardISAnime=1;

	SuperSkillMagicX0=0.f;
	SuperSkillMagicAnimeCouter=0;
	SuperSkillMagicISAnime=0;

	SuperSkillCardX0 = 0.f;
	SuperSkillCardAnimeCouter = 0;
	SuperSkillCardISAnime = 0;

	SuperSkillCardAlpha = 0;
	SuperSkillLightAlpha = 0;

	UICharacterX0 = 0.f;
	UICharacterISAnime = 1;

	UICharacterAnimeCouter=0;
	UICharacterDoCounter=0;
	UICharacterDoSwitch = false;

	CardCoolTimeCounter = 0;
	CardCoolTimeSwitch = false;

	CardLightAlpha = 0;
	CardLightAlphaSwitch = false;
}
void UninitGameUI(void)
{
	UninitSuperSkill();
	UICharacterX0 = 0.f;
	UICharacterISAnime = 1;

	UICharacterAnimeCouter = 0;
	UICharacterDoCounter = 0;
	UICharacterDoSwitch = false;

	CardCoolTimeCounter = 0;
	CardCoolTimeSwitch = false;

	CardLightAlpha = 0;
	CardLightAlphaSwitch = false;
	DestroySound(SOUND_DROW_02);
}
void UpdateGameUI(void)
{
	UICharacterDoCounter++;
	if (UICharacterDoCounter>=180||GetCharacterISBeHit())
	{
		UICharacterDoCounter = 0;
		if (!UICharacterDoSwitch)
		{
			UICharacterDoSwitch = true;
		}
	}
	if (UICharacterDoSwitch)
	{
		UICharacterAnimeCouter++;
		if (UICharacterAnimeCouter>=5)
		{
			if (UICharacterISAnime<UI_CHARACTER_MAX_ANIME)
			{
				UICharacterISAnime++;
				UICharacterAnimeCouter = 0;
			}
			else
			{
				UICharacterX0 = 0.f;
				UICharacterISAnime = 1;

				UICharacterAnimeCouter = 0;
				UICharacterDoCounter = 0;
				UICharacterDoSwitch = false;
			}
		}
		UICharacterX0 = (UICharacterISAnime - 1) / (float)UI_CHARACTER_MAX_ANIME;
	}
	if (SuperSkillSwitchFade)
	{
		CreateSound(SOUND_FLY);
		FadeAlpha += 5;
		SuperSkillCutInX *= -1;
		if (FadeAlpha >= 255)
		{
			FadeAlpha = 255;
			SuperSkillMagicAnimeCouter++;
			SuperSkillCardAnimeCouter++;
		}
		if (SuperSkillMagicAnimeCouter >= SUPER_SKILL_MAGIC_MAX_SPEED)
		{
			if (SuperSkillMagicISAnime < SUPER_SKILL_MAGIC_MAX_ANIME)
			{
				SuperSkillMagicISAnime++;
				SuperSkillMagicAnimeCouter = 0;
			}
			else
			{
				SuperSkillMagicISAnime= SUPER_SKILL_MAGIC_MAX_ANIME;
				SuperSkillMagicAnimeCouter = 0;
			}
			SuperSkillMagicX0= (SuperSkillMagicISAnime - 1) / (float)SUPER_SKILL_MAGIC_MAX_ANIME;
		}
		if (SuperSkillCardAnimeCouter >= SUPER_SKILL_CARD_MAX_SPEED)
		{
			if (SuperSkillCardISAnime < SUPER_SKILL_CARD_MAX_ANIME)
			{
				SuperSkillCardISAnime++;
				SuperSkillCardAnimeCouter = 0;
			}
			else
			{
				SuperSkillCardISAnime = SUPER_SKILL_CARD_MAX_ANIME;
				SuperSkillCardAlpha += 5;
				SuperSkillLightAlpha += 5;
			}
			SuperSkillCardX0 = (SuperSkillCardISAnime - 1) / (float)SUPER_SKILL_CARD_MAX_ANIME;
		}
		if (SuperSkillCardAlpha >= 255)
		{
			SuperSkillCardAlpha = 255;
		}
		if (SuperSkillLightAlpha>=255)
		{
			DestroySound(SOUND_FLY);
			SuperSkillSwitchFade = false;
			SuperSkillSwitch = true;
		}
	}
	if (SuperSkillSwitch)
	{
		SuperSkillX0 = (SuperSkillISAnime - 1) / (float)SUPER_SKILL_MAX_ANIME;
		SuperSkillAnimeCouter++;
		if (SuperSkillAnimeCouter >= 5)
		{
			SuperSkillAnimeCouter = 0;
			SuperSkillISAnime++;
		}
		if (SuperSkillISAnime > SUPER_SKILL_MAX_ANIME)
		{
			if (GetCharacterTrain())
			{
				if (GetISEnemyTrain(0))
				{
					TrainEnemyBeHit(0, 2000);
				}
			}
			DestroySound(SOUND_SP_WATER);
			DestroySound(SOUND_SP_KAMINARI);
			DestroySound(SOUND_SP_FIRE);
			UninitSuperSkill();
			DestroyCharacterSuperSkill();
			CardCoolTimeSwitch = true;
			SetCardCoolSwitch(true);
		}
	}
	if (CardCoolTimeSwitch)
	{
		CardCoolTimeCounter++;
		if (CardCoolTimeCounter>= CARD_MAX_COOL_TIME)
		{
			DestroySound(SOUND_DROW_02);
			CreateSound(SOUND_DROW_02);
			CardCoolTimeSwitch = false;
			SetCardCoolSwitch(false);
			CardCoolTimeCounter = 0;
		}
	}
	if (GetCharacterISCard() != CARD_TYPE_NULL)
	{
		if (!CardLightAlphaSwitch)
		{
			CardLightAlpha += 5;
			if (CardLightAlpha >= 250)
			{
				CardLightAlphaSwitch = true;
			}
		}
		else
		{
			CardLightAlpha -= 5;
			if (CardLightAlpha <= 50)
			{
				CardLightAlphaSwitch = false;
			}
		}
	}
	else
	{
		CardLightAlpha = 0;
		CardLightAlphaSwitch = false;
	}
}
void DrawGameUI(void)
{
	SetDUIChange(3);
	if (SuperSkillSwitchFade)
	{
		SetTexture(TEX_FADE);
		SetPolygonColor(D3DCOLOR_ARGB(FadeAlpha, 0, 0, 0));
		DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (SuperSkillCardISAnime>=1&&SuperSkillMagicISAnime>=1)
		{
			SetTexture(TEX_UI_SP_MAGIC);
			SetPolygonColor(D3DCOLOR_ARGB(128, 255, 255, 255));
			DrawPolygon(575.f, 35.f, 700, 700, 2100 * SuperSkillMagicX0, 0, 210, 210);
			SetTexture(TEX_UI_SP_CARD);
			SetPolygonColor(D3DCOLOR_ARGB(255-SuperSkillCardAlpha, 255, 255, 255));
			DrawPolygon(812.5f, 200.f+ SuperSkillCutInX, 225.f, 400, 800* SuperSkillCardX0, 0, 50, 80);
			//
			SetTexture(TEX_UI_SP_SPEEDLINE);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(0, 0, WINDOW_WIDTH, 800, 4219 * SuperSkillCardX0, 0, 263.6875f, 108);
		}
		if (GetCharacterISCard() == CARD_TYPE_FIRE)
		{
			SetTexture(TEX_UI_CARD_FLAME);
			SetPolygonColor(D3DCOLOR_ARGB(SuperSkillCardAlpha, 255, 255, 255));
			DrawPolygon(812.5f, 200.f+ SuperSkillCutInX, 225.f, 400, 0, 0, 300, 533);
		}
		else if (GetCharacterISCard() == CARD_TYPE_AQUA)
		{
			SetTexture(TEX_UI_CARD_AQUA);
			SetPolygonColor(D3DCOLOR_ARGB(SuperSkillCardAlpha, 255, 255, 255));
			DrawPolygon(812.5f, 200.f+ SuperSkillCutInX, 225.f, 400, 0, 0, 300, 533);
		}
		else if (GetCharacterISCard() == CARD_TYPE_THUNDER)
		{
			SetTexture(TEX_UI_CARD_THUNDER);
			SetPolygonColor(D3DCOLOR_ARGB(SuperSkillCardAlpha, 255, 255, 255));
			DrawPolygon(812.5f, 200.f+ SuperSkillCutInX, 225.f, 400, 0, 0, 300, 533);
		}
		SetTexture(TEX_FADE);
		SetPolygonColor(D3DCOLOR_ARGB(SuperSkillLightAlpha, 255, 255, 255));
		DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	if (SuperSkillSwitch)
	{
		SetTexture(TEX_FADE);
		SetPolygonColor(D3DCOLOR_ARGB(FadeAlpha, 255, 255, 255));
		DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		DrawSuperSkill();
	}
	SetTexture(TEX_UI_BASE_BACK);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (GetCharacterISCard() == CARD_TYPE_FIRE)
	{
		SetTexture(TEX_UI_CARD_FLAME);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1660.f, 712.f, 200, 355.33f, 0, 0, 300, 533);
	}
	else if (GetCharacterISCard() == CARD_TYPE_AQUA)
	{
		SetTexture(TEX_UI_CARD_AQUA);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1660.f, 712.f, 200, 355.33f, 0, 0, 300, 533);
	}
	else if (GetCharacterISCard() == CARD_TYPE_THUNDER)
	{
		SetTexture(TEX_UI_CARD_THUNDER);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1660.f, 712.f, 200, 355.33f, 0, 0, 300, 533);
	}
	else
	{
		SetTexture(TEX_UI_CARD_BACK);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1660.f, 712.f, 200, 355.33f, 0, 0, 300, 533);
	}
	if (CardCoolTimeSwitch)
	{
		SetTexture(TEX_UI_SP_COOLTIME);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1660.f, 712.f+(355.33f*CardCoolTimeCounter/(float)CARD_MAX_COOL_TIME), 200, (355.33f*(CARD_MAX_COOL_TIME-CardCoolTimeCounter) / (float)CARD_MAX_COOL_TIME), 0, 0, 100, 100);
	}
	if (GetCharacterISBeHit())
	{
		SetTexture(TEX_UI_CHARACTER_DOWN);
	}
	else
	{
		SetTexture(TEX_UI_CHARACTER_HAPPY);
	}
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(32.f, 721.f, 260, 350, 900 * UICharacterX0, 0, 225, 303);
	SetTexture(TEX_UI_BASE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (GetCharacterISCard() == CARD_TYPE_FIRE)
	{
		SetTexture(TEX_UI_CARD_F_LIGHT);
		SetPolygonColor(D3DCOLOR_ARGB(CardLightAlpha, 255, 255, 255));
		DrawPolygon(1630.f, 682.f, 266.67f, 422.f, 0, 0, 400, 633);
	}
	else if (GetCharacterISCard() == CARD_TYPE_AQUA)
	{
		SetTexture(TEX_UI_CARD_A_LIGHT);
		SetPolygonColor(D3DCOLOR_ARGB(CardLightAlpha, 255, 255, 255));
		DrawPolygon(1630.f, 682.f, 266.67f, 422.f, 0, 0, 400, 633);
	}
	else if (GetCharacterISCard() == CARD_TYPE_THUNDER)
	{
		SetTexture(TEX_UI_CARD_T_LIGHT);
		SetPolygonColor(D3DCOLOR_ARGB(CardLightAlpha, 255, 255, 255));
		DrawPolygon(1630.f, 682.f, 266.67f, 422.f, 0, 0, 400, 633);
	}
	else
	{

	}
	SetTexture(TEX_UI_HP_BACK);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(TEX_UI_HP_GAUGE);
	if (GetCharacterHP() <= (0.3*CHARACTER_MAX_HP))
	{
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else
	{
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	DrawPolygon(567.f, 870.f, ((25*20.2*GetCharacterHP())/ (float)CHARACTER_MAX_HP), 43, 0, 0, 25, 43);
	SetTexture(TEX_UI_HP_BASE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(TEX_UI_MP_BACK);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(TEX_UI_MP_GAUGE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(567.f, 976.f, ((25 * 20.2 * GetCharacterMP()) / (float)CHARACTER_MAX_MP), 44, 0, 0, 26, 44);
	SetTexture(TEX_UI_MP_BASE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(TEX_UI_STAR_BACK);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	int starcage=GetCharacterStarCage();
	if (starcage>=1)
	{
		SetTexture(TEX_UI_STAR_GAUGE_01);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (starcage >= 2)
		{
			SetTexture(TEX_UI_STAR_GAUGE_02);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			if (starcage >= 3)
			{
				SetTexture(TEX_UI_STAR_GAUGE_03);
				SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
				DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
				if (starcage >= 4)
				{
					SetTexture(TEX_UI_STAR_GAUGE_04);
					SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
					DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
					if (starcage >= 5)
					{
						SetTexture(TEX_UI_STAR_GAUGE_05);
						SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
						DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
						if (starcage >= 6)
						{
							SetTexture(TEX_UI_STAR_GAUGE_06);
							SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
							DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
							if (starcage >= 7)
							{
								SetTexture(TEX_UI_STAR_GAUGE_07);
								SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
								DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
							}
						}
					}
				}
			}
		}

	}
	SetTexture(TEX_UI_STAR_BASE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (GetCharacterISBeHit())
	{
		SetTexture(TEX_DEMAGE_INFO);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1280, 720);
	}
}

void CreateSuperSkill(void)
{
	if (GetCharacterISCard() == CARD_TYPE_FIRE|| GetCharacterISCard() == CARD_TYPE_AQUA|| GetCharacterISCard() == CARD_TYPE_THUNDER)
	{
		SuperSkillSwitchFade = true;
	}
}

void DrawSuperSkill(void)
{
	if (GetCharacterISCard() == CARD_TYPE_FIRE)
	{
		CreateSound(SOUND_SP_FIRE);
		SetTexture(TEX_SUPER_FLAME);
	}
	else if (GetCharacterISCard() == CARD_TYPE_AQUA)
	{
		CreateSound(SOUND_SP_WATER);
		SetTexture(TEX_SUPER_AQUA);
	}
	else if (GetCharacterISCard() == CARD_TYPE_THUNDER)
	{
		CreateSound(SOUND_SP_KAMINARI);
		SetTexture(TEX_SUPER_THUNDER);
	}
	else
	{
		SuperSkillSwitch = false;
	}
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0.f, 0.f, WINDOW_WIDTH, 800, (3840 * SuperSkillX0), 0, 240, 100);
}

void UninitSuperSkill(void)
{
	SuperSkillSwitch = false;
	FadeAlpha = 0;
	SuperSkillSwitchFade = false;
	SuperSkillX0 = 0.f;
	SuperSkillISAnime = 1;
	SuperSkillCutInX = 10.f;
	SuperSkillAnimeCouter = 0;

	SuperSkillCardX0 = 0.f;
	SuperSkillCardAnimeCouter = 0;
	SuperSkillCardISAnime = 0;

	SuperSkillMagicX0 = 0.f;
	SuperSkillMagicAnimeCouter = 0;
	SuperSkillMagicISAnime = 0;

	SuperSkillCardAlpha = 0;
	SuperSkillLightAlpha = 0;
}
