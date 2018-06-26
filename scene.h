#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

typedef enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_TRAIN,
	SCENE_GAME,
	SCENE_STAGE,
	SCENE_RESULT,
	SERNR_MAX
}SCENE_ID;


void InitAllScene(void);
void UninitAllScene(void);
//
void InitScene(void);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

SCENE_ID ChangeScene(SCENE_ID id);


#endif