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
// �v���g�^�C�v�錾
//
//********************************************************************************

void DrawAllNum(int nowTime, int dig, bool bZero, float x, float y);

// n�ɂ͂O�`�X�܂ł̐���
// ���̊֐��͐���1������\��
void DrawNumber( int n, float x, float y );


void FontResize(int size);

void FontInterval(int interval);


void NumberTexChange(TEXTURE_NUM num);

#endif