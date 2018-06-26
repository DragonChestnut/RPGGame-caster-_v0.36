//================================================================================
//	
//	Number.h
//	
//
//================================================================================

#ifndef	_NUMBER_H_
#define _NUMBER_H_
#include <stdio.h>
#include "Polygon.h"


#define NUMBER_WIDTH	( 100 )
#define NUMBER_HEIGHT	( 100 )

#define TIMER_INTERVAL	( 50 )



//********************************************************************************
//
// プロトタイプ宣言
//
//********************************************************************************

void DrawAllNum(int nowTime, int dig, bool bZero, float x, float y);

// nには０～９までの数字
// この関数は数字1文字を表示
void DrawNumber( int n, float x, float y );


void FontResize(int size);

void FontInterval(int interval);


void NumberTexChange(TEXTURE_NUM num);

#endif