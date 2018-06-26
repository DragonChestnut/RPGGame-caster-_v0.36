#define _TIMER_H_
#ifdef _TIMER_H_

//分単位で管理
#define LIMEI_TIMER	(5)



void InitTimer(void);

// -- TimeOverでfalseを返す --
bool UpdateTimer(void);

void DrawTimer(void);

// -- タイマーの作動遷移 --
void ChangeStateTimer(bool b_live);

float GetTime(void);

#endif