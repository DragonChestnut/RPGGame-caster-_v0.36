#include <stdlib.h>
#include <time.h>
#include "character.h"
#include "Game.h"
#include "camera.h"
#include "input.h"
#include "effect.h"
#include "Train.h"
#include "GameUI.h"
#include "Enemy_Train.h"
#include "Hit2dTrain.h"
#include "Clock.h"
#include "sound.h"


#define WALK_ANIME_CHANGE (7)

#define MAX_ATTACK_MODE (3)

#define MAX_STAGE (4)

#define CHARACTER_Z_MAX (5)
#define CHARACTER_Z_CHANGE_MAX (-7.3f)
#define CHARACTER_Z_MIN (-10)

#define MAX_STARCAGE (7)

#define CAMERA_CHANGE (66)

#define CHARACTER_BEHIT_DAMAGE (1)

static bool StageChangeCounter= false;
static int StageChangeCounterNum = 0;
static int IsStage = 0;
static float Character_Xchange[MAX_STAGE];
static float Character_Xmin[MAX_STAGE];
static float Character_Xmax[MAX_STAGE];

static int AttackIsNum;

static CHARACTER g_character;
//
static float camera_WS_speed = 0.1f;//カメラ縦スピード
static float camera_AD_speed = 0.25f;//カメラ横スピード

static bool Character_opswitch;

static bool CharacterStageChangeSwitch=false;

void InitCharacter(void)
{
	Character_opswitch = true;
	CharacterStageChangeSwitch = false;
	g_character.CharacterPos.x = -53.5f;
	g_character.CharacterPos.y = 0.f;
	g_character.CharacterPos.z = 0.f;
	g_character.speed_x = 0.1f;
	g_character.speed_z = 0.1f;
	g_character.CharacterWalkAnimeCounter = 0;
	g_character.CharacterWalkx0 = 0.000f;
	g_character.CharacterWalkx1 = 0.000f;
	g_character.CharacterWalkISAnime = 1;
	g_character.CharacterWalkMaxAnime = 6;
	g_character.CharacterAttackAnimeCounter = 0;
	g_character.CharacterAttackx0 = 0.000f;
	g_character.CharacterAttackx1 = 0.000f;
	g_character.CharacterAttackISAnime=1;
	g_character.CharacterAttackMaxAnime=5;
	g_character.CharacterAttackCounter = false;
	g_character.CharacterAttackMode = 0;
	g_character.CharacterISAttackMode = 0;
	g_character.CharacterDirection = 0;
	g_character.ISCharacterCard = CARD_TYPE_NULL;
	g_character.ISSuperSkill = false;
	g_character.ISCharacter = true;
	g_character.ISCharacterTrain = false;
	g_character.NoActionSwitch = false;
	g_character.CardCoolTimeSwitch = false;
	g_character.CharacterHP = CHARACTER_MAX_HP;
	g_character.CharacterMP = CHARACTER_MAX_MP;
	g_character.CharacterStarCage = 7;
	g_character.ISCharacterBeHit = false;
	g_character.CharacterBeHitx0 = 0.000f;
	g_character.CharacterBeHitx1 = 0.000f;
	g_character.CharacterBeHitAnimeCounter = 0;
	g_character.CharacterBeHitISAnime = 1;
	g_character.CharacterBeHitMaxAnime = 4;
	g_character.ISCharacterDrowCard = false;
	g_character.CharacterDrowCardx0= 0.000f;
	g_character.CharacterDrowCardx1 = 0.000f;
	g_character.CharacterDrowCardAnimeCounter = 0;
	g_character.CharacterDrowCardISAnime = 1;
	g_character.CharacterDrowCardMaxAnime = 6;
	CreateBillboardWHN(BILL_CHARACTER, 2.2f, 2.68125f, 1);
	SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
	SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_WALK_R);
	g_character.CharacterWalkx0 = (g_character.CharacterWalkISAnime-1) / (float)g_character.CharacterWalkMaxAnime;
	g_character.CharacterWalkx1 = (g_character.CharacterWalkISAnime) / (float)g_character.CharacterWalkMaxAnime;
	SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterWalkx0, 0.0f, g_character.CharacterWalkx1, 1.0f);

	//
	StageChangeCounter = false;
	StageChangeCounterNum = 0;
	IsStage = 0;

	Character_Xchange[0] = -32;
	Character_Xchange[1] = -15.5;
	Character_Xchange[2] = 1;
	Character_Xchange[3] = 100;
	Character_Xmin[0] = -48.5;
	Character_Xmin[1] = -32;
	Character_Xmin[2] = -15.5;
	Character_Xmin[3] = 1;
	Character_Xmax[0] = -31.5;
	Character_Xmax[1] = -15;
	Character_Xmax[2] = 1.5;
	Character_Xmax[3] = 18;
	//

	AttackIsNum = 0;
	srand((unsigned)time(NULL));
}
void UninitCharacter(void)
{
	Character_opswitch = true;
	CharacterStageChangeSwitch = false;
	g_character.CharacterPos.x = -48.5f;
	g_character.CharacterPos.y = 0.f;
	g_character.CharacterPos.z = 0.f;
	g_character.speed_x = 0.1f;
	g_character.speed_z = 0.1f;
	g_character.CharacterWalkAnimeCounter = 0;
	g_character.CharacterWalkx0 = 0.000f;
	g_character.CharacterWalkx1 = 0.000f;
	g_character.CharacterWalkISAnime = 1;
	g_character.CharacterWalkMaxAnime = 6;
	g_character.CharacterAttackAnimeCounter = 0;
	g_character.CharacterAttackx0 = 0.000f;
	g_character.CharacterAttackx1 = 0.000f;
	g_character.CharacterAttackISAnime = 1;
	g_character.CharacterAttackMaxAnime = 5;
	g_character.CharacterAttackCounter = false;
	g_character.CharacterISAttackMode = 0;
	g_character.CharacterAttackMode = 0;
	g_character.CharacterDirection = 0;
	g_character.ISCharacterCard = CARD_TYPE_NULL;
	g_character.ISSuperSkill = false;
	g_character.ISCharacter = true;
	g_character.ISCharacterTrain = false;
	g_character.NoActionSwitch = false;
	g_character.CardCoolTimeSwitch = false;
	g_character.CharacterHP = CHARACTER_MAX_HP;
	g_character.CharacterMP = CHARACTER_MAX_MP;
	g_character.CharacterStarCage = 7;
	g_character.ISCharacterBeHit = false;
	g_character.CharacterBeHitx0 = 0.000f;
	g_character.CharacterBeHitx1 = 0.000f;
	g_character.CharacterBeHitAnimeCounter = 0;
	g_character.CharacterBeHitISAnime = 1;
	g_character.CharacterBeHitMaxAnime = 4;
	g_character.ISCharacterDrowCard = false;
	g_character.CharacterDrowCardx0 = 0.000f;
	g_character.CharacterDrowCardx1 = 0.000f;
	g_character.CharacterDrowCardAnimeCounter = 0;
	g_character.CharacterDrowCardISAnime = 1;
	g_character.CharacterDrowCardMaxAnime = 6;
	DestroyBillboard(BILL_CHARACTER);
}
void UpdateCharacter(void)
{
	//
	if (Character_opswitch)
	{
		StopClock(false);
		if (g_character.CharacterPos.x<-43.5f)
		{
			g_character.NoActionSwitch = true;
			CharacterPerformance();
			StopClock(true);
		}
	}

	//訓練ステージ
	if (g_character.ISCharacterTrain)
	{
		if (!StageChangeCounter)
		{
			int trainlevel = GetTrainLevel();
			if (trainlevel == 4)
			{
				g_character.NoActionSwitch = false;
			}
			else if (trainlevel == 6)
			{
				g_character.NoActionSwitch = false;
				CharacterStageChangeSwitch = true;
			}
			else if (trainlevel == 0)
			{
				g_character.NoActionSwitch = true;
			}
			else
			{
				CharacterStageChangeSwitch = false;
				g_character.NoActionSwitch = true;
				g_character.CharacterWalkAnimeCounter = 0;
				g_character.CharacterWalkx0 = 0.000f;
				g_character.CharacterWalkx1 = 0.000f;
				g_character.CharacterWalkISAnime = 1;
				g_character.CharacterAttackAnimeCounter = 0;
				g_character.CharacterAttackx0 = 0.000f;
				g_character.CharacterAttackx1 = 0.000f;
				g_character.CharacterAttackISAnime = 1;
				g_character.CharacterAttackCounter = false;
				g_character.CharacterISAttackMode = 0;
				g_character.CharacterAttackMode = 0;
				g_character.ISSuperSkill = false;
			}
			if (!g_character.NoActionSwitch)
			{
				if (!g_character.ISCharacterBeHit)
				{
					if (!g_character.ISCharacterDrowCard)
					{
						CharacterWalk();
						CharacterNormalAttack();
						CharacterSuperSkill();
					}
					else
					{
						CharacterDrowCard();
					}
				}
				else
				{
					CharacterBeHit();
				}
			}
			if (g_character.CharacterMP<CHARACTER_MAX_MP)
			{
				g_character.CharacterMP += 1;
			}
		}
	}
	else
	{
		//CHARACTER操作
		if (!StageChangeCounter)
		{
			if (!g_character.NoActionSwitch)
			{
				if (!g_character.ISCharacterBeHit)
				{
					if (!g_character.ISCharacterDrowCard)
					{
						CharacterWalk();
						CharacterNormalAttack();
						CharacterSuperSkill();
					}
					else
					{
						CharacterDrowCard();
					}
				}
				else
				{
					CharacterBeHit();
				}
			}
			if (g_character.CharacterMP<CHARACTER_MAX_MP)
			{
				g_character.CharacterMP+=1;
			}
		}
	}
	//ステージチェンジ
	if (StageChangeCounter)
	{
		D3DXVECTOR3 IsCameraRight = GetRight();
		D3DXVECTOR3 IsCameraUp = GetUp();
		D3DXVECTOR3 IsCameraFront = GetFront();
		D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
		D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
		D3DXVECTOR3 IsCameraEye = GetEye();
		IsCameraEye += IsCameraRight*camera_AD_speed;
		D3DXVECTOR3 IsCameraAt = GetAt();
		IsCameraAt += IsCameraRight*camera_AD_speed;
		SetCameraPos(IsCameraEye);
		SetCameraAt(IsCameraAt);
		StageChangeCounterNum++;
		int maxnumstage = CAMERA_CHANGE;
		if (StageChangeCounterNum >= maxnumstage)
		{
			StageChangeCounter = false;
			StageChangeCounterNum = 0;
			IsStage += 1;
			if (GetTrainLevel() == 6)
			{
				SetTrainLevel(7);
			}
		}
	}
	//
}
void DrawCharacter(void)
{

}

void CharacterWalk(void)
{
	if (!g_character.CharacterAttackCounter)
	{
		if (!g_character.ISSuperSkill)
		{
			//
			CharacterCardSetNum();
			//
			if (GetKeyboardPress(DIK_W))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z < CHARACTER_Z_MAX)
				{
					if (g_character.ISCharacterTrain)
					{
						int trainlevel = GetTrainLevel();
						if (trainlevel == 4)
						{
							if ((g_character.CharacterPos.x-1.1f) <= (GetTrainEnemyPos(0).x + 0.8f))
							{
								if ((g_character.CharacterPos.x+1.1f) >= (GetTrainEnemyPos(0).x - 0.8f))
								{
									if (g_character.CharacterPos.z> GetTrainEnemyPos(0).z-0.5f)
									{
										if (g_character.CharacterPos.z<(GetTrainEnemyPos(0).z+1.05f))
										{
										}
										else
										{
											g_character.CharacterPos.z += g_character.speed_z;
											SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
											//カメラも移動タイプ
											if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
											{
												D3DXVECTOR3 IsCameraFront = GetFront();
												IsCameraFront.y = 0;
												D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
												D3DXVECTOR3 IsCameraEye = GetEye();
												IsCameraEye += IsCameraFront* camera_WS_speed;
												D3DXVECTOR3 IsCameraAt = GetAt();
												IsCameraAt += IsCameraFront*camera_WS_speed;
												SetCameraPos(IsCameraEye);
												SetCameraAt(IsCameraAt);
											}
										}
									}
									else
									{
										if ((g_character.CharacterPos.z+ g_character.speed_z)>(GetTrainEnemyPos(0).z - 0.5f))
										{
										}
										else
										{
											g_character.CharacterPos.z += g_character.speed_z;
											SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
											//カメラも移動タイプ
											if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
											{
												D3DXVECTOR3 IsCameraFront = GetFront();
												IsCameraFront.y = 0;
												D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
												D3DXVECTOR3 IsCameraEye = GetEye();
												IsCameraEye += IsCameraFront* camera_WS_speed;
												D3DXVECTOR3 IsCameraAt = GetAt();
												IsCameraAt += IsCameraFront*camera_WS_speed;
												SetCameraPos(IsCameraEye);
												SetCameraAt(IsCameraAt);
											}
										}
									}
								}
								else
								{
									g_character.CharacterPos.z += g_character.speed_z;
									SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
									//カメラも移動タイプ
									if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
									{
										D3DXVECTOR3 IsCameraFront = GetFront();
										IsCameraFront.y = 0;
										D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
										D3DXVECTOR3 IsCameraEye = GetEye();
										IsCameraEye += IsCameraFront* camera_WS_speed;
										D3DXVECTOR3 IsCameraAt = GetAt();
										IsCameraAt += IsCameraFront*camera_WS_speed;
										SetCameraPos(IsCameraEye);
										SetCameraAt(IsCameraAt);
									}
								}
							}
							else
							{
								g_character.CharacterPos.z += g_character.speed_z;
								SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
								//カメラも移動タイプ
								if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
								{
									D3DXVECTOR3 IsCameraFront = GetFront();
									IsCameraFront.y = 0;
									D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
									D3DXVECTOR3 IsCameraEye = GetEye();
									IsCameraEye += IsCameraFront* camera_WS_speed;
									D3DXVECTOR3 IsCameraAt = GetAt();
									IsCameraAt += IsCameraFront*camera_WS_speed;
									SetCameraPos(IsCameraEye);
									SetCameraAt(IsCameraAt);
								}
							}
						}
						else
						{
							g_character.CharacterPos.z += g_character.speed_z;
							SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
							//カメラも移動タイプ
							if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
							{
								D3DXVECTOR3 IsCameraFront = GetFront();
								IsCameraFront.y = 0;
								D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
								D3DXVECTOR3 IsCameraEye = GetEye();
								IsCameraEye += IsCameraFront* camera_WS_speed;
								D3DXVECTOR3 IsCameraAt = GetAt();
								IsCameraAt += IsCameraFront*camera_WS_speed;
								SetCameraPos(IsCameraEye);
								SetCameraAt(IsCameraAt);
							}
						}
					}
					else
					{
						g_character.CharacterPos.z += g_character.speed_z;
						SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
						//カメラも移動タイプ
						if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
						{
							D3DXVECTOR3 IsCameraFront = GetFront();
							IsCameraFront.y = 0;
							D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
							D3DXVECTOR3 IsCameraEye = GetEye();
							IsCameraEye += IsCameraFront* camera_WS_speed;
							D3DXVECTOR3 IsCameraAt = GetAt();
							IsCameraAt += IsCameraFront*camera_WS_speed;
							SetCameraPos(IsCameraEye);
							SetCameraAt(IsCameraAt);
						}
					}
				}
				g_character.CharacterWalkAnimeCounter++;
			}

			if (GetKeyboardPress(DIK_S))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z > CHARACTER_Z_MIN)
				{
					if (g_character.ISCharacterTrain)
					{
						int trainlevel = GetTrainLevel();
						if (trainlevel == 4)
						{
							if ((g_character.CharacterPos.x - 1.1f) <= (GetTrainEnemyPos(0).x + 0.8f))
							{
								if ((g_character.CharacterPos.x + 1.1f) >= (GetTrainEnemyPos(0).x - 0.8f))
								{
									if (g_character.CharacterPos.z > GetTrainEnemyPos(0).z - 0.5f)
									{
										if (g_character.CharacterPos.z < (GetTrainEnemyPos(0).z+1.05f))
										{
										}
										else
										{
											if ((g_character.CharacterPos.z- g_character.speed_z)<(GetTrainEnemyPos(0).z + 1.05f))
											{
											}
											else
											{
												g_character.CharacterPos.z -= g_character.speed_z;
												SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
												//カメラも移動タイプ
												if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
												{
													D3DXVECTOR3 IsCameraFront = GetFront();
													IsCameraFront.y = 0;
													D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
													D3DXVECTOR3 IsCameraEye = GetEye();
													IsCameraEye -= IsCameraFront*camera_WS_speed;
													D3DXVECTOR3 IsCameraAt = GetAt();
													IsCameraAt -= IsCameraFront*camera_WS_speed;
													SetCameraPos(IsCameraEye);
													SetCameraAt(IsCameraAt);
												}
											}
										}
									}
									else
									{
										g_character.CharacterPos.z -= g_character.speed_z;
										SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
										//カメラも移動タイプ
										if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
										{
											D3DXVECTOR3 IsCameraFront = GetFront();
											IsCameraFront.y = 0;
											D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
											D3DXVECTOR3 IsCameraEye = GetEye();
											IsCameraEye -= IsCameraFront*camera_WS_speed;
											D3DXVECTOR3 IsCameraAt = GetAt();
											IsCameraAt -= IsCameraFront*camera_WS_speed;
											SetCameraPos(IsCameraEye);
											SetCameraAt(IsCameraAt);
										}
									}
								}
								else
								{
									g_character.CharacterPos.z -= g_character.speed_z;
									SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
									//カメラも移動タイプ
									if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
									{
										D3DXVECTOR3 IsCameraFront = GetFront();
										IsCameraFront.y = 0;
										D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
										D3DXVECTOR3 IsCameraEye = GetEye();
										IsCameraEye -= IsCameraFront*camera_WS_speed;
										D3DXVECTOR3 IsCameraAt = GetAt();
										IsCameraAt -= IsCameraFront*camera_WS_speed;
										SetCameraPos(IsCameraEye);
										SetCameraAt(IsCameraAt);
									}
								}
							}
							else
							{
								g_character.CharacterPos.z -= g_character.speed_z;
								SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
								//カメラも移動タイプ
								if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
								{
									D3DXVECTOR3 IsCameraFront = GetFront();
									IsCameraFront.y = 0;
									D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
									D3DXVECTOR3 IsCameraEye = GetEye();
									IsCameraEye -= IsCameraFront*camera_WS_speed;
									D3DXVECTOR3 IsCameraAt = GetAt();
									IsCameraAt -= IsCameraFront*camera_WS_speed;
									SetCameraPos(IsCameraEye);
									SetCameraAt(IsCameraAt);
								}
							}
						}
						else
						{
							g_character.CharacterPos.z -= g_character.speed_z;
							SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
							//カメラも移動タイプ
							if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
							{
								D3DXVECTOR3 IsCameraFront = GetFront();
								IsCameraFront.y = 0;
								D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
								D3DXVECTOR3 IsCameraEye = GetEye();
								IsCameraEye -= IsCameraFront*camera_WS_speed;
								D3DXVECTOR3 IsCameraAt = GetAt();
								IsCameraAt -= IsCameraFront*camera_WS_speed;
								SetCameraPos(IsCameraEye);
								SetCameraAt(IsCameraAt);
							}
						}
					}
					else
					{
						g_character.CharacterPos.z -= g_character.speed_z;
						SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
						//カメラも移動タイプ
						if (g_character.CharacterPos.z > CHARACTER_Z_CHANGE_MAX&&g_character.CharacterPos.z < CHARACTER_Z_MAX)
						{
							D3DXVECTOR3 IsCameraFront = GetFront();
							IsCameraFront.y = 0;
							D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
							D3DXVECTOR3 IsCameraEye = GetEye();
							IsCameraEye -= IsCameraFront*camera_WS_speed;
							D3DXVECTOR3 IsCameraAt = GetAt();
							IsCameraAt -= IsCameraFront*camera_WS_speed;
							SetCameraPos(IsCameraEye);
							SetCameraAt(IsCameraAt);
						}
					}
				}
				g_character.CharacterWalkAnimeCounter++;
			}
			if (GetKeyboardPress(DIK_D))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.x < Character_Xmax[IsStage])
				{
					if (g_character.ISCharacterTrain)
					{
						int trainlevel = GetTrainLevel();
						if (trainlevel == 4)
						{
							if (g_character.CharacterPos.z > GetTrainEnemyPos(0).z - 0.5f)
							{
								if (g_character.CharacterPos.z < (GetTrainEnemyPos(0).z + 1.05f))
								{
									if ((g_character.CharacterPos.x - 1.1f) <= (GetTrainEnemyPos(0).x + 0.8f))
									{
										if ((g_character.CharacterPos.x + 1.1f) >= (GetTrainEnemyPos(0).x - 0.8f))
										{

										}
										else
										{
											if ((g_character.CharacterPos.x+ g_character.speed_x+1.1f)>= (GetTrainEnemyPos(0).x - 0.8f))
											{

											}
											else
											{
												g_character.CharacterPos.x += g_character.speed_x;
												SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
											}
										}
									}
									else
									{
										g_character.CharacterPos.x += g_character.speed_x;
										SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
									}
								}
								else
								{
									g_character.CharacterPos.x += g_character.speed_x;
									SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
								}
							}
							else
							{
								g_character.CharacterPos.x += g_character.speed_x;
								SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
							}
						}
						else
						{
							g_character.CharacterPos.x += g_character.speed_x;
							SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
						}
					}
					else
					{
						g_character.CharacterPos.x += g_character.speed_x;
						SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					}
				}
				g_character.CharacterWalkAnimeCounter++;
				g_character.CharacterDirection = 0;
				if (CharacterStageChangeSwitch)
				{
					if (g_character.CharacterPos.x > Character_Xchange[IsStage])
					{
						StageChangeCounter = true;
					}
				}
			}
			if (GetKeyboardPress(DIK_A))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.x > Character_Xmin[IsStage])
				{
					if (g_character.ISCharacterTrain)
					{
						int trainlevel = GetTrainLevel();
						if (trainlevel == 4)
						{
							if (g_character.CharacterPos.z > GetTrainEnemyPos(0).z - 0.5f)
							{
								if (g_character.CharacterPos.z < (GetTrainEnemyPos(0).z + 1.05f))
								{
									if ((g_character.CharacterPos.x - 1.1f) <= (GetTrainEnemyPos(0).x + 0.8f))
									{
										if ((g_character.CharacterPos.x + 1.1f) >= (GetTrainEnemyPos(0).x - 0.8f))
										{
										}
										else
										{
											g_character.CharacterPos.x -= g_character.speed_x;
											SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
										}
									}
									else
									{
										if ((g_character.CharacterPos.x - g_character.speed_x-1.1f)<= (GetTrainEnemyPos(0).x + 0.8f))
										{

										}
										else
										{
											g_character.CharacterPos.x -= g_character.speed_x;
											SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
										}

									}
								}
								else
								{
									g_character.CharacterPos.x -= g_character.speed_x;
									SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
								}
							}
							else
							{
								g_character.CharacterPos.x -= g_character.speed_x;
								SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
							}
						}
						else
						{
							g_character.CharacterPos.x -= g_character.speed_x;
							SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
						}
					}
					else
					{
						g_character.CharacterPos.x -= g_character.speed_x;
						SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					}
				}
				g_character.CharacterWalkAnimeCounter++;
				g_character.CharacterDirection = 1;
				////カメラも移動タイプ
				//D3DXVECTOR3 IsCameraRight = GetRight();
				//D3DXVECTOR3 IsCameraUp = GetUp();
				//D3DXVECTOR3 IsCameraFront = GetFront();
				//D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
				//D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
				//D3DXVECTOR3 IsCameraEye = GetEye();
				//IsCameraEye -= IsCameraRight*camera_AD_speed;
				//D3DXVECTOR3 IsCameraAt = GetAt();
				//IsCameraAt -= IsCameraRight*camera_AD_speed;
				//SetCameraPos(IsCameraEye);
				//SetCameraAt(IsCameraAt);
			}
			//
			if (g_character.CharacterWalkAnimeCounter >= WALK_ANIME_CHANGE)
			{
				if (g_character.CharacterWalkISAnime == 2 || g_character.CharacterWalkISAnime == 5)
				{
					DestroySound(SOUND_SE_ASHIOTO);
					CreateSound(SOUND_SE_ASHIOTO);
				}
				if (g_character.CharacterWalkISAnime < g_character.CharacterWalkMaxAnime)
				{
					g_character.CharacterWalkISAnime++;
				}
				else
				{
					g_character.CharacterWalkISAnime = 1;
				}
				g_character.CharacterWalkAnimeCounter = 0;
			}
			//
			if (g_character.CharacterDirection == 0)
			{
				SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_WALK_R);
			}
			else
			{
				SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_WALK_L);
			}
			g_character.CharacterWalkx0 = (g_character.CharacterWalkISAnime - 1) / (float)g_character.CharacterWalkMaxAnime;
			g_character.CharacterWalkx1 = (g_character.CharacterWalkISAnime) / (float)g_character.CharacterWalkMaxAnime;
			SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterWalkx0, 0.0f, g_character.CharacterWalkx1, 1.0f);
		}
	}
}

int GetCharacterDirection(void)
{
	return g_character.CharacterDirection;
}

D3DXVECTOR3 GetCharacterPos(void)
{
	return g_character.CharacterPos;
}

void SetISCharacterTrain(bool CharacterTrain)
{
	g_character.ISCharacterTrain = CharacterTrain;
}

void SetNoActionSwitch(bool ActionSwitch)
{
	g_character.NoActionSwitch = ActionSwitch;
}

void CharacterNormalAttack(void)
{
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_character.CharacterAttackCounter = true;
	}
	if (g_character.CharacterAttackCounter)
	{
		if (!g_character.ISSuperSkill)
		{
			if (g_character.CharacterAttackMode == 0)
			{
				g_character.CharacterAttackMode = 1;
				g_character.CharacterISAttackMode = 1;
			}
			g_character.CharacterWalkAnimeCounter = 0;
			g_character.CharacterWalkISAnime = 1;
			if (g_character.CharacterISAttackMode == 1)
			{
				CreateSound(SOUND_ATTACK_01);
				CreateEffect(CHARACTER_EFFECT_RUA00, 8, 3, NAME_CHARACTER);
				if (g_character.CharacterAttackISAnime < g_character.CharacterAttackMaxAnime)
				{
					g_character.CharacterAttackAnimeCounter++;
					if (g_character.CharacterAttackAnimeCounter >= 3)
					{
						g_character.CharacterAttackISAnime++;
						g_character.CharacterAttackAnimeCounter = 0;
					}
					if (g_character.CharacterDirection == 0)
					{
						SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_R);
					}
					else
					{
						SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_L);
					}
				}
				else
				{
					g_character.CharacterAttackISAnime = g_character.CharacterAttackMaxAnime;
					g_character.CharacterAttackAnimeCounter = 0;
				}
				if (GetEffectISAnime(CHARACTER_EFFECT_RUA00) > 1)
				{
					if (GetKeyboardPress(DIK_SPACE))
					{
						g_character.CharacterAttackMode = 2;
					}
				}
				if (GetEffectISAnime(CHARACTER_EFFECT_RUA00) == 8)
				{
					//damage
					if (g_character.ISCharacterTrain)
					{
						if (GetISEnemyTrain(0))
						{
							D3DXVECTOR3 TrainEnemyPos= GetTrainEnemyPos(0);
							if (Hit2DTrain(g_character.CharacterPos.x, (g_character.CharacterPos.z+0.4f), 2.2f, 0.8f,TrainEnemyPos.x, TrainEnemyPos.z+0.4f, 2.1f, 0.8f))
							{
								TrainEnemyBeHit(0, 50);
							}
						}
					}
					//
					if (g_character.CharacterAttackMode == 2)
					{
						DestroySound(SOUND_ATTACK_01);
						g_character.CharacterISAttackMode = 2;
					}
					else
					{
						DestroySound(SOUND_ATTACK_01);
						g_character.CharacterAttackISAnime = 1;
						g_character.CharacterAttackMode = 0;
						g_character.CharacterISAttackMode = 0;
						g_character.CharacterAttackCounter = false;
					}
				}
			}
			else if (g_character.CharacterISAttackMode == 2)
			{
				CreateSound(SOUND_ATTACK_ALL);
				CreateEffect(CHARACTER_EFFECT_RUA01, 8, 3,NAME_CHARACTER);
				if (g_character.CharacterAttackISAnime > 1)
				{
					g_character.CharacterAttackAnimeCounter++;
					if (g_character.CharacterAttackAnimeCounter >= 3)
					{
						g_character.CharacterAttackISAnime--;
						g_character.CharacterAttackAnimeCounter = 0;
					}
					if (g_character.CharacterDirection == 0)
					{
						SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_R);
					}
					else
					{
						SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_L);
					}
				}
				else
				{
					g_character.CharacterAttackISAnime = 1;
					g_character.CharacterAttackAnimeCounter = 0;
				}
				if (GetEffectISAnime(CHARACTER_EFFECT_RUA01) > 1)
				{
					if (g_character.ISCharacterCard != CARD_TYPE_NULL)
					{
						if (g_character.CharacterMP >= 1000)
						{
							if (GetKeyboardPress(DIK_SPACE))
							{
								g_character.CharacterAttackMode = 3;
							}
						}
					}
				}
				if (GetEffectISAnime(CHARACTER_EFFECT_RUA01) == 8)
				{
					//damage
					if (g_character.ISCharacterTrain)
					{
						if (GetISEnemyTrain(0))
						{
							D3DXVECTOR3 TrainEnemyPos = GetTrainEnemyPos(0);
							if (Hit2DTrain(g_character.CharacterPos.x, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
							{
								TrainEnemyBeHit(0, 100);
							}
						}
					}
					//
					if (g_character.CharacterAttackMode == 3)
					{
						DestroySound(SOUND_ATTACK_ALL);
						g_character.CharacterISAttackMode = 3;
						g_character.CharacterMP -= 1000;
					}
					else
					{
						DestroySound(SOUND_ATTACK_ALL);
						g_character.CharacterAttackISAnime = 1;
						g_character.CharacterAttackMode = 0;
						g_character.CharacterISAttackMode = 0;
						g_character.CharacterAttackCounter = false;
					}
				}
			}
			else if (g_character.CharacterISAttackMode == 3)
			{
				CreateSound(SOUND_ATTACK_02);
				g_character.CharacterAttackAnimeCounter++;
				if (g_character.CharacterAttackAnimeCounter >= 5)
				{
					g_character.CharacterAttackISAnime++;
					g_character.CharacterAttackAnimeCounter = 0;
				}
				if (g_character.CharacterDirection == 0)
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_R);
				}
				else
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_L);
				}
				if (g_character.CharacterAttackISAnime >= g_character.CharacterAttackMaxAnime - 1)
				{
					g_character.CharacterAttackISAnime = g_character.CharacterAttackMaxAnime - 1;
				}
				if (g_character.ISCharacterCard == CARD_TYPE_FIRE)
				{
					if (g_character.CharacterAttackISAnime == 2)
					{
						DestroySound(SOUND_ATTACK_02);
						CreateSound(SOUND_ATTACK_FIRE);
						CreateEffect(CHARACTER_EFFECT_MAGIC_SQUARE_00, 16, 3, NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_MAGIC_SQUARE_00) == 6)
					{
						//damage
						if (g_character.ISCharacterTrain)
						{
							if (GetISEnemyTrain(0))
							{
								D3DXVECTOR3 TrainEnemyPos = GetTrainEnemyPos(0);
								if (g_character.CharacterDirection == 0)
								{
									if (Hit2DTrain(g_character.CharacterPos.x + 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
								else
								{
									if (Hit2DTrain(g_character.CharacterPos.x - 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
							}
						}
						//
						CreateEffect(CHARACTER_EFFECT_FLAME, 10, 5, NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_FLAME) == 10)
					{
						DestroySound(SOUND_ATTACK_FIRE);
						g_character.CharacterAttackCounter = false;
						g_character.CharacterAttackISAnime = 1;
						g_character.CharacterAttackMode = 0;
						g_character.CharacterISAttackMode = 0;
						g_character.CharacterAttackAnimeCounter = 0;
					}
				}
				else if (g_character.ISCharacterCard == CARD_TYPE_AQUA)
				{
					if (g_character.CharacterAttackISAnime == 2)
					{
						DestroySound(SOUND_ATTACK_02);
						CreateSound(SOUND_ATTACK_WATER);
						CreateEffect(CHARACTER_EFFECT_MAGIC_SQUARE_01, 16, 3,NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_MAGIC_SQUARE_01) == 6)
					{
						//damage
						if (g_character.ISCharacterTrain)
						{
							if (GetISEnemyTrain(0))
							{
								D3DXVECTOR3 TrainEnemyPos = GetTrainEnemyPos(0);
								if (g_character.CharacterDirection == 0)
								{
									if (Hit2DTrain(g_character.CharacterPos.x + 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
								else
								{
									if (Hit2DTrain(g_character.CharacterPos.x - 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
							}
						}
						//
						CreateEffect(CHARACTER_EFFECT_AQUA, 10, 5, NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_AQUA) == 10)
					{
						DestroySound(SOUND_ATTACK_WATER);
						g_character.CharacterAttackCounter = false;
						g_character.CharacterAttackISAnime = 1;
						g_character.CharacterAttackMode = 0;
						g_character.CharacterISAttackMode = 0;
						g_character.CharacterAttackAnimeCounter = 0;
					}
				}
				else if (g_character.ISCharacterCard == CARD_TYPE_THUNDER)
				{
					if (g_character.CharacterAttackISAnime == 2)
					{
						DestroySound(SOUND_ATTACK_02);
						CreateSound(SOUND_ATTACK_KAMINARI);
						CreateEffect(CHARACTER_EFFECT_MAGIC_SQUARE_02, 16, 3, NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_MAGIC_SQUARE_02) == 6)
					{
						//damage
						if (g_character.ISCharacterTrain)
						{
							if (GetISEnemyTrain(0))
							{
								D3DXVECTOR3 TrainEnemyPos = GetTrainEnemyPos(0);
								if (g_character.CharacterDirection==0)
								{
									if (Hit2DTrain(g_character.CharacterPos.x + 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
								else
								{
									if (Hit2DTrain(g_character.CharacterPos.x - 3.f, (g_character.CharacterPos.z + 0.4f), 2.2f, 0.8f, TrainEnemyPos.x, TrainEnemyPos.z + 0.4f, 2.1f, 0.8f))
									{
										TrainEnemyBeHit(0, 300);
									}
								}
							}
						}
						//
						CreateEffect(CHARACTER_EFFECT_THUNDER, 16, 3, NAME_CHARACTER);
					}
					if (GetEffectISAnime(CHARACTER_EFFECT_THUNDER) == 10)
					{
						DestroySound(SOUND_ATTACK_KAMINARI);
						g_character.CharacterAttackCounter = false;
						g_character.CharacterAttackISAnime = 1;
						g_character.CharacterAttackMode = 0;
						g_character.CharacterISAttackMode = 0;
						g_character.CharacterAttackAnimeCounter = 0;
					}
				}
				else
				{
					DestroySound(SOUND_ATTACK_02);
					g_character.CharacterAttackCounter = false;
					g_character.CharacterAttackISAnime = 1;
					g_character.CharacterAttackMode = 0;
					g_character.CharacterISAttackMode = 0;
					g_character.CharacterAttackAnimeCounter = 0;
				}
			}
			g_character.CharacterAttackx0 = (g_character.CharacterAttackISAnime-1) / (float)g_character.CharacterAttackMaxAnime;
			g_character.CharacterAttackx1 = (g_character.CharacterAttackISAnime) / (float)g_character.CharacterAttackMaxAnime;
			SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterAttackx0, 0.0f, g_character.CharacterAttackx1, 1.0f);
		}
	}
}

//
void CharacterSetCard(CARD_TYPE Type)
{
	g_character.ISCharacterCard = Type;
}

void CharacterSuperSkill(void)
{
	if (!g_character.CharacterAttackCounter)
	{
		if (GetKeyboardPress(DIK_M))
		{
			if (!g_character.ISSuperSkill)
			{
				if (g_character.CharacterStarCage>=2)
				{
					if (g_character.ISCharacterCard == CARD_TYPE_FIRE || g_character.ISCharacterCard == CARD_TYPE_AQUA || g_character.ISCharacterCard == CARD_TYPE_THUNDER)
					{
						g_character.ISSuperSkill = true;
						g_character.CharacterWalkAnimeCounter = 0;
						g_character.CharacterWalkISAnime = 1;
						g_character.CharacterStarCage -= 2;
					}
				}
			}
		}
	}
	if (g_character.ISSuperSkill)
	{
		if (g_character.CharacterAttackISAnime < g_character.CharacterAttackMaxAnime)
		{
			g_character.CharacterAttackAnimeCounter++;
			if (g_character.CharacterAttackAnimeCounter >= 3)
			{
				g_character.CharacterAttackISAnime++;
				g_character.CharacterAttackAnimeCounter = 0;
			}
			if (g_character.CharacterDirection == 0)
			{
				SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_R);
			}
			else
			{
				SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_ATTACK_L);
			}
		}
		if (g_character.CharacterAttackISAnime >= g_character.CharacterAttackMaxAnime)
		{
			CreateSuperSkill();
		}
		g_character.CharacterAttackx0 = (g_character.CharacterAttackISAnime - 1) / (float)g_character.CharacterAttackMaxAnime;
		g_character.CharacterAttackx1 = (g_character.CharacterAttackISAnime) / (float)g_character.CharacterAttackMaxAnime;
		SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterAttackx0, 0.0f, g_character.CharacterAttackx1, 1.0f);
	}
}

CARD_TYPE GetCharacterISCard(void)
{
	return g_character.ISCharacterCard;
}


void DestroyCharacterSuperSkill(void)
{
	g_character.ISSuperSkill = false;
	g_character.CharacterAttackAnimeCounter = 0;
	g_character.CharacterAttackISAnime = 1;
	CharacterSetCard(CARD_TYPE_NULL);
}

void SetCardCoolSwitch(bool CardCool)
{
	g_character.CardCoolTimeSwitch = CardCool;
}

int GetCharacterHP(void)
{
	return g_character.CharacterHP;
}

int GetCharacterMP(void)
{
	return g_character.CharacterMP;
}

void CharacterBeHit(void)
{
	CreateSound(SOUND_SE_BEHIT);
	if (g_character.CharacterBeHitISAnime <= g_character.CharacterBeHitMaxAnime)
	{
		g_character.CharacterBeHitAnimeCounter++;
		if (g_character.CharacterBeHitAnimeCounter >= 5)
		{
			g_character.CharacterBeHitISAnime++;
			g_character.CharacterBeHitAnimeCounter = 0;
		}
		if (g_character.CharacterDirection == 0)
		{
			SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_BEHIT_R);
		}
		else
		{
			SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_BEHIT_L);
		}
	}
	else
	{
		DestroySound(SOUND_SE_BEHIT);
		g_character.ISCharacterBeHit = false;
		g_character.CharacterHP -= CHARACTER_BEHIT_DAMAGE;
		g_character.CharacterBeHitISAnime = 1;
	}
	g_character.CharacterBeHitx0 = (g_character.CharacterBeHitISAnime - 1) / (float)g_character.CharacterBeHitMaxAnime;
	g_character.CharacterBeHitx1 = (g_character.CharacterBeHitISAnime) / (float)g_character.CharacterBeHitMaxAnime;
	SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterBeHitx0, 0.0f, g_character.CharacterBeHitx1, 1.0f);
}

bool GetCharacterISBeHit(void)
{
	return g_character.ISCharacterBeHit;
}

void CharacterPerformance(void)
{
	g_character.CharacterPos.x += 0.05f;
	g_character.CharacterWalkAnimeCounter++;
	SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
	//
	if (g_character.CharacterWalkAnimeCounter >= WALK_ANIME_CHANGE)
	{
		if (g_character.CharacterWalkISAnime==2|| g_character.CharacterWalkISAnime == 5)
		{
			DestroySound(SOUND_SE_ASHIOTO);
			CreateSound(SOUND_SE_ASHIOTO);
		}
		if (g_character.CharacterWalkISAnime < g_character.CharacterWalkMaxAnime)
		{
			g_character.CharacterWalkISAnime++;
		}
		else
		{
			g_character.CharacterWalkISAnime = 1;
		}
		g_character.CharacterWalkAnimeCounter = 0;
	}
	//
	if (g_character.CharacterDirection == 0)
	{
		SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_WALK_R);
	}
	else
	{
		SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_WALK_L);
	}
	g_character.CharacterWalkx0 = (g_character.CharacterWalkISAnime - 1) / (float)g_character.CharacterWalkMaxAnime;
	g_character.CharacterWalkx1 = (g_character.CharacterWalkISAnime) / (float)g_character.CharacterWalkMaxAnime;
	SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterWalkx0, 0.0f, g_character.CharacterWalkx1, 1.0f);
	if (g_character.CharacterPos.x >= -43.5f)
	{
		g_character.NoActionSwitch = false;
		Character_opswitch = false;
		if (g_character.ISCharacterTrain)
		{
			//
			SetTrainLevel(1);
		}
	}

}

void CharacterDrowCard(void)
{
	CreateSound(SOUND_DROW_CARD);
	if (g_character.CharacterDrowCardISAnime <= g_character.CharacterDrowCardMaxAnime)
	{
		g_character.CharacterDrowCardAnimeCounter++;
		if (g_character.CharacterDrowCardAnimeCounter >= 5)
		{
			g_character.CharacterDrowCardISAnime++;
			g_character.CharacterDrowCardAnimeCounter = 0;
		}
		if (g_character.CharacterDirection == 0)
		{
			SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_DROWCARD_R);
		}
		else
		{
			SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_WOMAN_DROWCARD_L);
		}
	}
	else
	{
		DestroySound(SOUND_DROW_CARD);
		g_character.ISCharacterDrowCard = false;
		g_character.CharacterDrowCardISAnime = 1;
		int cardrandnum = rand() % 90;
		if (cardrandnum<30)
		{
			CharacterSetCard(CARD_TYPE_FIRE);
		}
		else if (cardrandnum>=60)
		{
			CharacterSetCard(CARD_TYPE_THUNDER);
		}
		else
		{
			CharacterSetCard(CARD_TYPE_AQUA);
		}
	}
	g_character.CharacterDrowCardx0 = (g_character.CharacterDrowCardISAnime - 1) / (float)g_character.CharacterDrowCardMaxAnime;
	g_character.CharacterDrowCardx1 = (g_character.CharacterDrowCardISAnime) / (float)g_character.CharacterDrowCardMaxAnime;
	SetBillboardTexCoord(BILL_CHARACTER, g_character.CharacterDrowCardx0, 0.0f, g_character.CharacterDrowCardx1, 1.0f);
}

int GetCharacterStarCage(void)
{
	return g_character.CharacterStarCage;
}

bool GetCharacterISAttack(void)
{
	return g_character.CharacterAttackCounter;
}

int GetCharacterISAttackMode(void)
{
	return g_character.CharacterISAttackMode;
}

bool GetCharacterTrain(void)
{
	return g_character.ISCharacterTrain;
}

//test
void CharacterCardSetNum(void)
{
	if (!g_character.CardCoolTimeSwitch)
	{
		if (GetKeyboardPress(DIK_1))
		{
			CharacterSetCard(CARD_TYPE_FIRE);
		}
		if (GetKeyboardPress(DIK_2))
		{
			CharacterSetCard(CARD_TYPE_AQUA);
		}
		if (GetKeyboardPress(DIK_3))
		{
			CharacterSetCard(CARD_TYPE_THUNDER);
		}
		if (GetKeyboardPress(DIK_0))
		{
			CharacterSetCard(CARD_TYPE_NULL);
		}
	}
	//
	if (GetKeyboardPress(DIK_L))
	{
		if (g_character.CharacterStarCage< MAX_STARCAGE)
		{
			g_character.CharacterStarCage += 1;
		}
	}
	if (GetKeyboardPress(DIK_H))
	{
		if (g_character.CharacterHP >= 10)
		{
			if (!g_character.ISCharacterBeHit)
			{
				g_character.ISCharacterBeHit = true;
				if (g_character.ISCharacterDrowCard)
				{
					g_character.ISCharacterDrowCard = false;
					g_character.CharacterDrowCardISAnime = 1;
				}
				if (g_character.CharacterAttackCounter)
				{
					g_character.CharacterAttackCounter = false;
					g_character.CharacterAttackISAnime = 1;
					g_character.CharacterAttackMode = 0;
					g_character.CharacterISAttackMode = 0;
					g_character.CharacterAttackAnimeCounter = 0;
				}
			}
		}
	}
	if (GetKeyboardPress(DIK_N))
	{
		if (g_character.ISCharacterCard== CARD_TYPE_NULL&&(!g_character.CardCoolTimeSwitch))
		{
			if (!g_character.ISCharacterDrowCard)
			{
				g_character.ISCharacterDrowCard = true;
			}
		}
	}

}
//