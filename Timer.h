#define _TIMER_H_
#ifdef _TIMER_H_

//���P�ʂŊǗ�
#define LIMEI_TIMER	(5)



void InitTimer(void);

// -- TimeOver��false��Ԃ� --
bool UpdateTimer(void);

void DrawTimer(void);

// -- �^�C�}�[�̍쓮�J�� --
void ChangeStateTimer(bool b_live);

float GetTime(void);

#endif