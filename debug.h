#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_



void InitDebugText(void);
void UninitDebugText(void);
void DebugText(int x, int y, const char* pFormat, ...);

void DebugPolygon(int n, float x, float y, float r);

#endif