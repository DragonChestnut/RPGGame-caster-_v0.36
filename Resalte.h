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

// -- Scoreの初期のスコア入れ　--
void InitScore(void);

// -- 新しいスコアの受け渡し --
void NewScore(int time, int enemy, CARD_TYPE type);

// -- new内で行う --
void InitResalte(void);
// -- スコアの再配列 -- .. これはNewScore内でやってる
void AlignmentScore(void);
// -- リザルトの描画 --
void UpdateResalte(void);

void DrawResalte(void);

void UninitResalte(void);

// -- エフェクト用 --

void DrawCardEfect(void);

void CreateCardEfect(void);

void UpdateCardEfect(void);


#endif // !_RESALTE_H_
