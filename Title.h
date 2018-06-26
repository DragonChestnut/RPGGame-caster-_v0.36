#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include <d3dx9.h>

enum TITLE_NUM
{
	SCROOL=0,
	CARD,
	ROGO,
	MAX

};

typedef struct
{
	D3DXVECTOR2 pos;
	float speed;
	bool b_live;
	int live_time;
	D3DCOLOR color;
}STAR;

void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

// --Å@ÉøîªíË --
int JudgAlpha(float a);

void UpdateStar(void);
void CreateStar(int x, int y, D3DCOLOR color, int limit, int speed);
void GenerationStar(void);

#endif
