//==========================================================================================
//
//	Clock.cpp
//
//==========================================================================================
#include "Timer.h"
#include "Polygon.h"

#define MAX_TIME (LIMEI_TIMER * 60)

float g_rad;

void NewGame(void)
{
	InitTimer();
	g_rad = 0;
}

bool UpdateClock(void)
{
	if (UpdateTimer() == false)
	{
		return false;
	}
	float time = GetTime();
	time /= MAX_TIME;

	g_rad = -3.14 *time + 3.14;
}
void DrawClock(void)
{
	SetTexture(TEX_CLOCK);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(760, 0, 400, 200, 0, 0, 400, 200);

	SetTexture(TEX_PIN);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	SetPolygonRotation(7.5,7.5, g_rad);
	SetPolygonScale(0, 0, 0.4, 0.4);
	DrawPolygon(950, -7, 455, 60, 0, 0, 455, 60,true);

	DrawTimer();
}

void StopClock(bool b)
{
	ChangeStateTimer(b);
}
