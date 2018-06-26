#include "TrainUI.h"
#include "camera.h"
#include "polygon.h"
#include "Train.h "
#include "sound.h"

#define MESSAGE_MAX_ANIME (16)

static float MessageX0;
static int MessageAnimeCouter;
static int MessageISAnime;

static int MessageAlpha_01;

static int Info_Height;

static int Story_Height;
static int Story_01_02_Switch;
static int Story_01_02_Counter;

static bool Story_05_Switch;
static int Story_05_Counter;

void InitTrainUI(void)
{
	MessageX0 = 0.f;
	MessageISAnime = 1;
	MessageAnimeCouter=0;
	MessageAlpha_01 = 0;
	Info_Height = 0;
	Story_Height = 0;
	Story_01_02_Switch = 1;
	Story_01_02_Counter = 0;
	Story_05_Switch = false;
	Story_05_Counter = 0;
}
void UninitTrainUI(void)
{
	MessageX0 = 0.f;
	MessageISAnime = 1;
	MessageAnimeCouter = 0;
	MessageAlpha_01 = 0;
	Info_Height = 0;
	Story_Height = 0;
	Story_01_02_Switch = 1;
	Story_01_02_Counter = 0;
	Story_05_Switch = false;
	Story_05_Counter = 0;
}
void UpdateTrainUI(void)
{
	int level = GetTrainLevel();
	if (level == 1)
	{
		Story_Height += 20;
		if (Story_Height>=250)
		{
			Story_Height = 250;
			Story_01_02_Counter += 1;
			if (Story_01_02_Switch ==1)
			{
				if (Story_01_02_Counter >= 30)
				{
					Story_Height = 0;
					Story_01_02_Switch = 2;
				}
			}
		}
	}
	if (level == 5)
	{
		if (!Story_05_Switch)
		{
			Info_Height = 0;
			Story_Height += 20;
			if (Story_Height >= 250)
			{
				Story_Height = 250;
				Story_05_Counter += 1;
				if (Story_05_Counter >= 30)
				{
					Story_05_Switch = true;
					Story_05_Counter = 0;
				}

			}
		}
		else
		{
			Info_Height += 20;
			MessageISAnime = 1;
			if (Info_Height >= 375)
			{
				Info_Height = 375;
			}
		}
	}
	if (level==6)
	{
		Story_Height = 0;
	}
	if (level==7)
	{
		Story_Height += 20;
		if (Story_Height >= 250)
		{
			Story_Height = 250;
		}
	}
	if (level == 11)
	{
		Story_Height += 20;
		if (Story_Height >= 250)
		{
			Story_Height = 250;
		}
	}
	if (level == 2 || level == 8)
	{
		Story_Height = 0;
		MessageAnimeCouter++;
		if (MessageAnimeCouter >= 3)
		{
			MessageAnimeCouter = 0;
			MessageISAnime++;
		}
		if (MessageISAnime >= MESSAGE_MAX_ANIME)
		{
			MessageISAnime = MESSAGE_MAX_ANIME;
			MessageAlpha_01 += 5;
			if (MessageAlpha_01>=255)
			{
				MessageAlpha_01 = 255;
			}
		}
		MessageX0 = (MessageISAnime - 1) / (float)MESSAGE_MAX_ANIME;
	}
	else if (level == 3|| level == 9)
	{
		Info_Height += 20;
		MessageISAnime = 1;
		if (Info_Height>=375)
		{
			Info_Height = 375;
		}
	}
	else
	{
		MessageISAnime = 1;
	}
}
void DrawTrainUI(void)
{
	int level = GetTrainLevel();
	if (level == 1)
	{
		SetTexture(TEX_UI_STORY_K);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(400.f, 100, 1400, Story_Height, 0, 0, 1280, 250);
		if (Story_01_02_Switch == 1)
		{
			SetTexture(TEX_UI_STORY_01);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(450.f, 100, 1280, Story_Height, 0, 0, 1280, 250);
		}
		else
		{
			SetTexture(TEX_UI_STORY_02);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(400.f, 100, 1280, Story_Height, 0, 0, 1280, 250);
		}
	}
	if (level == 5)
	{
		if (!Story_05_Switch)
		{
			SetTexture(TEX_UI_STORY_K);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(400.f, 100, 1400, Story_Height, 0, 0, 1280, 250);
			SetTexture(TEX_UI_STORY_03);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(450.f, 100, 1280, Story_Height, 0, 0, 1280, 250);
		}
		else
		{
			SetTexture(TEX_UI_INFO_K);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
			SetTexture(TEX_UI_INFO_MOJI_03);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
		}
	}
	if (level == 7)
	{
		SetTexture(TEX_UI_STORY_K);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(100.f, 100, 1400, Story_Height, 0, 0, 1280, 250);
		SetTexture(TEX_UI_STORY_04);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(150.f, 100, 1280, Story_Height, 0, 0, 1280, 250);
	}
	if (level == 11)
	{
		SetTexture(TEX_UI_STORY_K);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(400.f, 100, 1400, Story_Height, 0, 0, 1280, 250);
		SetTexture(TEX_UI_STORY_05);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(450.f, 100, 1280, Story_Height, 0, 0, 1280, 250);
	}
	if (level == 9)
	{
		MessageAlpha_01 = 0;
		DestroySound(SOUND_SE_PAGE);
		SetTexture(TEX_UI_INFO_K);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
		SetTexture(TEX_UI_INFO_MOJI_01);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
	}
	if (level == 2 || level == 8)
	{
		CreateSound(SOUND_SE_PAGE);
		SetTexture(TEX_TRAIN_UI_01);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(400.f, 150, 1100, 580, (10800 * MessageX0), 0, 675, 200);
	}
	if (level==2)
	{
		SetTexture(TEX_TRAIN_UI_02);
		SetPolygonColor(D3DCOLOR_ARGB(MessageAlpha_01, 255, 255, 255));
		DrawPolygon(460, 170, 1000, 480, 0, 0, 1000, 480);
	}
	if (level == 8)
	{
		SetTexture(TEX_TRAIN_UI_03);
		SetPolygonColor(D3DCOLOR_ARGB(MessageAlpha_01, 255, 255, 255));
		DrawPolygon(650, 170, 1000, 480, 0, 0, 1000, 480);
	}
	if (level == 3)
	{
		MessageAlpha_01 = 0;
		DestroySound(SOUND_SE_PAGE);
		SetTexture(TEX_UI_INFO_K);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
		SetTexture(TEX_UI_INFO_MOJI_02);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0, 200, WINDOW_WIDTH, Info_Height, 0, 0, 1280, 250);
	}
}
