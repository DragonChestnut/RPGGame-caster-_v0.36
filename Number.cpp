//================================================================================
//	num
//	Number.cpp
//	2017/07/09
//
//================================================================================

#include "Number.h"
#include "Timer.h"

#define LINE_NUM (5)
#define COLUMN__NUM (2)

#define NUM_SIZE (150)
#define NUM_INTERVAL (-50)


//********************************************************************************
//
// グローバル変数宣言
//
//********************************************************************************

int g_FontSize = NUM_SIZE;
int g_FontInterval = NUM_INTERVAL;
TEXTURE_NUM g_tex = TEX_NUMBER_01;

//================================================================================
//描画
//================================================================================
void DrawAllNum(int nowTime, int dig, bool bZero, float x, float y)
{
	if (dig <= 0)
	{
		dig = 1;

		for (; ; )
		{
			nowTime /= 10;

			if (nowTime == 0)
			{
				break;
			}

			dig++;
		}
	}
	// カンスト判定
	int timeMax = 10;

	for (int i = 1; i < dig; i++)
	{
		timeMax *= 10;
	}

	timeMax--;

	nowTime = min(timeMax, nowTime);

	//数値の分解表示
	for (int i = dig - 1; i >= 0; i--)
	{
		int n = nowTime % 10;
		nowTime /= 10;

		DrawNumber(n, x + (g_FontSize + g_FontInterval) * i, y);
		bool isZero = !bZero && !nowTime;

		if (isZero)
		{
			i = 0;
		}
	}
}

//================================================================================
//
// 数字一つ分 描画関数
//
//================================================================================
void DrawNumber( int n, float x, float y )
{
	if ( n < 0 || n > 9 )
	{
		return;
	}
	
	SetTexture(g_tex);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	SetPolygonScale( 0.5f, 0.5f, 1.0f, 1.0f );
	DrawPolygon( x, y, g_FontSize, g_FontSize, NUMBER_WIDTH * (n%LINE_NUM), NUMBER_HEIGHT * (n / LINE_NUM),
		NUMBER_WIDTH, NUMBER_HEIGHT);
}

void FontResize(int size)
{
	g_FontSize = size;
}
void FontInterval(int interval)
{
	g_FontInterval = interval;
}

void NumberTexChange(TEXTURE_NUM num)
{
	g_tex = num;
}
