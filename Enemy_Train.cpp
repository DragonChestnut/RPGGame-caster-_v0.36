#include "Enemy_Train.h"
#include "Train.h"

#define WALK_ANIME_CHANGE (7)
#define TRAIN_STAGE (2)
#define ENEMY_Z_MAX (5)
#define ENEMY_Z_MIN (-10)
#define TRAIN_MAX_ENEMY (2)
#define TRAIN_MAX_EFFECT (10)

#define ENEMY_MAX_HP_01 (5000)

static TRAIN_ENEMY g_Enemy[TRAIN_MAX_ENEMY];
static float Enemy_Xmin[TRAIN_STAGE];
static float Enemy_Xmax[TRAIN_STAGE];
static int EnemyCount = 0;//動き出すまでの時間
static int EnemyTime = 0;//敵の思考する時間
static float Value = 0;//絶対値用の変数

void InitEnemyTrain(void)
{
	for (int i = 0; i < TRAIN_MAX_ENEMY; i++)
	{
		g_Enemy[i].EnemyPos.x = -40.f;
		g_Enemy[i].EnemyPos.y = 0.f;
		g_Enemy[i].EnemyPos.z = 0.f;
		g_Enemy[i].speed_x = 0.4f;
		g_Enemy[i].speed_z = 0.3f;
		g_Enemy[i].EnemyHP = ENEMY_MAX_HP_01;
		g_Enemy[i].ISEnemy = false;
	}
	Enemy_Xmin[0] = -48.5f;
	Enemy_Xmin[1] = -32.f;
	Enemy_Xmax[0] = -31.5f;
	Enemy_Xmax[1] = -15;
}

void UninitEnemyTrain(void)
{
	for (int i = 0; i < TRAIN_MAX_ENEMY; i++)
	{
		if (g_Enemy[i].ISEnemy)
		{
			if (i==0)
			{
				DestroyBillboard(BILL_ENEMY_TRAIN_00);
			}
			else if (i==1)
			{
				DestroyBillboard(BILL_ENEMY_TRAIN_01);
			}
			g_Enemy[i].ISEnemy = false;
		}
		
	}
}

void UpdateEnemyTrain(void)
{
	int trainlevel = GetTrainLevel();
	if (trainlevel==4)
	{
		if (g_Enemy[0].EnemyHP <= 0)
		{
			SetTrainLevel(5);
		}
		if (g_Enemy[0].ISEnemy)
		{
			DestroyBillboard(BILL_ENEMY_TRAIN_HP_CAGE);
			CreateBillboardWHN(BILL_ENEMY_TRAIN_HP_CAGE, (2.f*g_Enemy[0].EnemyHP)/ (float)ENEMY_MAX_HP_01, 0.2f, 1);
			SetBillboardPos(BILL_ENEMY_TRAIN_HP_CAGE, g_Enemy[0].EnemyPos.x+(((2.f*(ENEMY_MAX_HP_01-g_Enemy[0].EnemyHP)) / (float)ENEMY_MAX_HP_01)/ (float)2), g_Enemy[0].EnemyPos.y + 2.5f, g_Enemy[0].EnemyPos.z);
			SetBillboardISTexNum(BILL_ENEMY_TRAIN_HP_CAGE, TEX_ENEMY_TRAIN_HP_CAGE);
		}
	}
}

void DrawEnemyTrain(void)
{

}

void CreateEnemyTrain(int Enemynum,float EnemyPosx, float EnemyPosy, float EnemyPosz)
{
	g_Enemy[Enemynum].EnemyPos.x = EnemyPosx;
	g_Enemy[Enemynum].EnemyPos.y = EnemyPosy;
	g_Enemy[Enemynum].EnemyPos.z = EnemyPosz;
	g_Enemy[Enemynum].ISEnemy = true;
	if (Enemynum==0)
	{
		CreateBillboardWHN(BILL_ENEMY_TRAIN_00, 2.08f, 2.14f, 1);
		SetBillboardPos(BILL_ENEMY_TRAIN_00, g_Enemy[Enemynum].EnemyPos.x, g_Enemy[Enemynum].EnemyPos.y, g_Enemy[Enemynum].EnemyPos.z);
		SetBillboardISTexNum(BILL_ENEMY_TRAIN_00, TEX_ENEMY_BOX);
		CreateBillboardWHN(BILL_ENEMY_TRAIN_HP_K, 2.f, 0.2f, 1);
		SetBillboardPos(BILL_ENEMY_TRAIN_HP_K, g_Enemy[Enemynum].EnemyPos.x, g_Enemy[Enemynum].EnemyPos.y+2.5f, g_Enemy[Enemynum].EnemyPos.z);
		SetBillboardISTexNum(BILL_ENEMY_TRAIN_HP_K, TEX_ENEMY_TRAIN_HP_K);
		CreateBillboardWHN(BILL_ENEMY_TRAIN_HP_CAGE, 2.f, 0.2f, 1);
		SetBillboardPos(BILL_ENEMY_TRAIN_HP_CAGE, g_Enemy[Enemynum].EnemyPos.x, g_Enemy[Enemynum].EnemyPos.y+2.5f, g_Enemy[Enemynum].EnemyPos.z);
		SetBillboardISTexNum(BILL_ENEMY_TRAIN_HP_CAGE, TEX_ENEMY_TRAIN_HP_CAGE);
	}
}

D3DXVECTOR3 GetTrainEnemyPos(int Enemynum)
{
	return g_Enemy[Enemynum].EnemyPos;
}

void DestroyEnemyTrain(int Enemynum)
{
	DestroyBillboard(BILL_ENEMY_TRAIN_00);
	DestroyBillboard(BILL_ENEMY_TRAIN_HP_K);
	DestroyBillboard(BILL_ENEMY_TRAIN_HP_CAGE);
	g_Enemy[Enemynum].ISEnemy = false;
}

void TrainEnemyBeHit(int Enemynum,int damage)
{
	g_Enemy[Enemynum].EnemyHP -= damage;
}

int GetEnemyHPTrain(int Enemynum)
{
	return g_Enemy[Enemynum].EnemyHP;
}

bool GetISEnemyTrain(int Enemynum)
{
	return g_Enemy[Enemynum].ISEnemy;
}