#pragma once
#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <d3d9.h>
#include <d3dx9.h>



void InitTrain(void);
void UninitTrain(void);
void UpdateTrain(void);
void DrawTrain(void);

int GetTrainLevel(void);
void SetTrainLevel(int num);

void StroyOver(void);
#endif