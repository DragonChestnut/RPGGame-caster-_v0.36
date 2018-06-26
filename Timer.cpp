//=====================================================================
//
//	GameTimer.cpp
//
//=====================================================================
#include "Number.h"
#include "Timer.h"
#include "Polygon.h"


int g_timeSecond;
int g_timeMinit;

bool g_bLive;
int g_fpControl;

void InitTimer(void)
{
	g_timeSecond = 0;
	g_timeMinit = LIMEI_TIMER;
	g_bLive = true;
	g_fpControl = 0;
}

bool UpdateTimer(void)
{
	if (g_bLive)
	{
		g_fpControl++;
	}
	if (g_fpControl >= 60)
	{
		g_fpControl = 0;
		g_timeSecond--;
		if (g_timeSecond <= 0)
		{
			g_timeSecond = 59;
			g_timeMinit--;

			if (g_timeMinit < 0)
			{//ŽžŠÔØ‚ê
				return false;
			}
		}
	}
	return true;
}

void DrawTimer(void)
{	
	FontResize(100);
	FontInterval(-50);

	NumberTexChange(TEX_NUMBER_01);
	//•ª
	DrawAllNum(g_timeMinit, 1, false, 830, 0);
	//•b
	DrawAllNum(g_timeSecond, 2, true, 950, 0);

	SetTexture(TEX_CORON);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(930,20,30,60,0,0,50,100);

}

//-------------------------------------------
//	ó‘Ô•Ï‰»
//-------------------------------------------
void ChangeStateTimer(bool b_live)
{
	g_bLive = b_live;
}
//ŽžŠÔ‚ÌƒQƒbƒ^[
float GetTime()
{
	float alltime = g_timeMinit * 60 + g_timeSecond;
	return alltime;
}