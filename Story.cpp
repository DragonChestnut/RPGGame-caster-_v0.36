//===========================================================================================
//
//	story.cpp
//
//===========================================================================================
#include "Polygon.h"
#include "Story.h"
#include "input.h"
#include "Clock.h"
#include "Train.h"

namespace
{
	bool g_story;
	bool g_out;
	int g_count;
	TEXTURE_NUM g_tex;
	int g_scrol;
}

void InitStory(void)
{
	g_story = false;
	g_count = 0;
	g_tex = TEX_STORY_PLOROAG;
	g_scrol = 0;
	//終わるとき用
	g_out = false;
}

void DrawStory(void)
{
	if (g_story || g_out)
	{// BG
		SetTexture(TEX_FADE);
		SetPolygonColor(D3DCOLOR_ARGB(min(255, g_count), 255, 255, 255));
		DrawPolygon(0, 100, 1920, 1080, 0, 0, 100, 100);

		SetTexture(TEX_STORY_BLACK);
		SetPolygonColor(D3DCOLOR_ARGB(min(100,g_count), 255, 255, 255));
		DrawPolygon(0, 00, 1920, 1080, 0, 0, 25, 25);

		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 0, 1920, min(100, g_count), 0, 0, 25, 25);

		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 1080 -min(100,g_count), 1920, 100, 0, 0, 25, 25);

		SetTexture(g_tex);
		SetPolygonColor(D3DCOLOR_ARGB(min(255, g_count), 255, 255, 255));
		DrawPolygon(550, 220, 800, 600, 0, 0,1280, 720);
	}
}

void SetStory();

void UpdateStory(void)
{
	if (g_story)
	{
		g_count++;
		if (g_count > 255)
		{
			g_count = 255;
		}
		if (GetKeyboardPress(DIK_RETURN))
		{
			g_out = true;
			g_story = false;
		}
	}
	else if (g_out)
	{
		g_count--;
		if (g_count <= 0)
		{//ここでストーリ処理終了
			g_out = false;
			//StopClock(true);
			StroyOver();
		}
	}
}

void StartStory(void)
{
	g_story = true;
	//StopClock(false);
}