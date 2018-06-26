#ifndef _ENEMYTRAIN_H_
#define _ENEMYTRAIN_H_

#include <d3dx9.h>
#include "Game.h"
#include "Billboard.h"


typedef struct
{
	D3DXVECTOR3 EnemyPos;/*���W*/
	float speed_x;//���X�s�[�h
	float speed_z;//�c�X�s�[�h
	int EnemyHP;
	int EnemyAnimeCounter;
	int EnemyISAnime;
	int EnemyMaxAnime;
	bool ISEnemy;
}TRAIN_ENEMY;



void InitEnemyTrain(void);
void UninitEnemyTrain(void);
void UpdateEnemyTrain(void);
void DrawEnemyTrain(void);

void CreateEnemyTrain(int Enemynum, float EnemyPosx, float EnemyPosy, float EnemyPosz);
void DestroyEnemyTrain(int Enemynum);

D3DXVECTOR3 GetTrainEnemyPos(int Enemynum);

void TrainEnemyBeHit(int Enemynum, int damage);

int GetEnemyHPTrain(int Enemynum);

bool GetISEnemyTrain(int Enemynum);
#endif