#define _RESALTE_H_
#ifdef _RESALTE_H_

#include "character.h"

enum RANK
{
	S=0,
	A,
	B,
	C,
	D
};

enum TRANS
{
	Open=0,
	DisplayScore,
	DisplayRank,
	DisplayAllScore,
	Stop

};

#define RANK_S (200)
#define RANK_A (100)
#define RANK_B (50)
#define RANK_C (20)
#define RANK_D (10)

// -- Score�̏����̃X�R�A����@--
void InitScore(void);

// -- �V�����X�R�A�̎󂯓n�� --
void NewScore(int time, int enemy, CARD_TYPE type);

// -- new���ōs�� --
void InitResalte(void);
// -- �X�R�A�̍Ĕz�� -- .. �����NewScore���ł���Ă�
void AlignmentScore(void);
// -- ���U���g�̕`�� --
void UpdateResalte(void);

void DrawResalte(void);

void UninitResalte(void);

// -- �G�t�F�N�g�p --

void DrawCardEfect(void);

void CreateCardEfect(void);

void UpdateCardEfect(void);


#endif // !_RESALTE_H_
