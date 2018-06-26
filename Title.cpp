#include "Title.h"
#include "Polygon.h"
#include "input.h"
#include "scene.h"
#include "Fade.h"
#include "input.h"
#include "Efect.h"
#include <d3d9.h>
#include "sound.h"

#define BG_W	(2160)
#define BG_H	(1215)
#define SCROOL_SPEED	(5)

#define CARD_SPEED	(20)
#define ROGO_INTERVAL	(150)

#define FLICK_MAX	(50)
#define STAR_MAX	(5)
#define STAR_SPEED	(0.8)

static bool FadeSwitch;

namespace
{
	float g_card_01 = 0;
	float g_card_02 = 0;
	float g_card_03 = 0;
	float g_card_04 = 0;
	float g_card_05 = 0;

	int g_flick = 0;
	bool g_bflick = true;

}

STAR g_star[STAR_MAX];


static TITLE_NUM g_cahnge;
float g_count;

void InitTitle(void)
{

	InitEfect();
	g_cahnge = SCROOL;
	g_count = 0;
	g_card_01 = -1;
	g_card_02 = -ROGO_INTERVAL * 1;
	g_card_03 = -ROGO_INTERVAL * 2;
	g_card_04 = -ROGO_INTERVAL * 3;
	g_card_05 = -ROGO_INTERVAL * 5;

	g_flick = 0;
	g_bflick = true;

	FadeSwitch = false;

	for (int i = 0; i < STAR_MAX; i++)
	{
		g_star[i].pos = { 0,9 };
		g_star[i].speed = STAR_SPEED;
		g_star[i].b_live = false;
		g_star[i].live_time = 0;
	}
	CreateSound(SOUND_BGM_TITLE);
}
void UninitTitle(void)
{
	UninitEfect();
}
void UpdateTitle(void)
{
	// --- Efect¶¬ ---
	GenerationStar();
	switch (g_cahnge)
	{
	case SCROOL:
		g_count += SCROOL_SPEED;
		if (g_count >= BG_H || GetKeyboardPress(DIK_RETURN))
		{
			g_count = BG_H;
			g_cahnge = CARD;
		}
		break;

	case CARD:
		g_card_01 += CARD_SPEED;
		g_card_02 += CARD_SPEED;
		g_card_03 += CARD_SPEED;
		g_card_04 += CARD_SPEED;
		g_card_05 += CARD_SPEED;
		
		if (g_card_05 >= 255)
		{
			g_cahnge = MAX;
		}
		break;
	case MAX:
		g_card_05 = 255;
		if (g_bflick)
		{
			g_flick += 1;
			if (g_flick >= FLICK_MAX)
			{
				g_bflick = false;
			}
		}
		else if (!g_bflick)
		{
			g_flick -= 1;
			if (g_flick <= 30)
			{
				g_bflick = true;
			}
		}
		break;

	default:
		break;
	}


	if (GetKeyboardPress(DIK_RETURN) && g_cahnge == MAX)
	{
		DestroySound(SOUND_BGM_TITLE);
		CreateSound(SOUND_SE_GAMESTART);
		StartFade(Out, White);
		FadeSwitch = true;
	}
	if (FadeSwitch)
	{
		if (GetState() == After)
		{
			StartFade(In, White);
			ChangeScene(SCENE_TRAIN);
		}
	}
	UpdatePolygon();
	UpdateStar();
	UpdateEfect();
}
void DrawTitle(void)
{
	SetDUIChange(2);
	SetTexture(TEX_TITLE_BG);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0+g_count, BG_W, BG_H );

	DrawEfect();

	SetTexture(TEX_TITLE_01);
	SetPolygonColor(D3DCOLOR_ARGB(JudgAlpha(g_card_01), 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);

	SetTexture(TEX_TITLE_02);
	SetPolygonColor(D3DCOLOR_ARGB(JudgAlpha(g_card_02), 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);
	
	SetTexture(TEX_TITLE_03);
	SetPolygonColor(D3DCOLOR_ARGB(JudgAlpha(g_card_03), 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);

	SetTexture(TEX_TITLE_04);
	SetPolygonColor(D3DCOLOR_ARGB(JudgAlpha(g_card_04), 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);

	SetTexture(TEX_TITLE_MAX);
	SetPolygonColor(D3DCOLOR_ARGB(JudgAlpha(g_card_05), 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);

	SetTexture(TEX_TITLE_FLICK);
	SetPolygonColor(D3DCOLOR_ARGB(g_flick, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 2046, 1447);

}

int JudgAlpha(float a)
{
	if (a < 0)return 0;
	else if (a>256)	return 255;
	else return (int)a;
}

void UpdateStar(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (g_star[i].b_live)
		{
			g_star[i].pos.x+= g_star[i].speed;
			g_star[i].pos.y += g_star[i].speed;
			g_star[i].live_time -= 1;
			CreateEfect(g_star[i].pos.x, g_star[i].pos.y, g_star[i].color, 80);
			if (g_star[i].pos.y > WINDOW_HEIGHT || g_star[i].pos.x > WINDOW_WIDTH || g_star[i].live_time <=0)
			{
				g_star[i].b_live = false;
			}
		}
	}
}

void CreateStar(int x, int y , D3DCOLOR color, int limit, int speed)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (g_star[i].b_live)
		{
			continue;
		}
		else
		{
			g_star[i].pos.x = x;
			g_star[i].pos.y = y;
			g_star[i].color = color;
			g_star[i].speed = speed;
			g_star[i].live_time = limit;
			g_star[i].b_live = true;
			break;
		}
	}
}

void GenerationStar(void)
{
	if (rand() % 50 == 0)
	{
		CreateStar(rand() % WINDOW_WIDTH, rand()%(WINDOW_HEIGHT - 400), D3DXCOLOR(0,0,0,1),200,3);
	}
}