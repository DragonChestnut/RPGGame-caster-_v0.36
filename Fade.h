//==========================================================
//
//	fade.cpp
//
//==========================================================

#ifndef _FADE_H_
#define _FADE_H_

enum FADE_TYPE
{
	In = 0,
	Out
};

enum FADE_TEX
{
	White = 0,
	Black 
};

enum SCREEN_STATE
{
	Bfore=0,
	Purpose,
	After
};

void InitFade(void);

void UpdateFade(void);

void DrawFade(void);

bool StartFade(FADE_TYPE type , FADE_TEX tex);

SCREEN_STATE GetState(void);

#endif 
