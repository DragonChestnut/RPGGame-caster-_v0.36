//==================================================================
//	Resalte.cpp
//
//
//==================================================================

#include "Polygon.h"
#include "Resalte.h"
#include "Number.h"
#include "character.h"

#include "Fade.h"
#include "input.h"
#include "scene.h"
#include "sound.h"

#define SCORE_MAX (8)
#define SCORE_TIME (60)

#define CARD_EFECT_MAX (3)

TRANS g_trans;

typedef struct
{
	int totalscore;
	int enemynum;
	int time;
	RANK rank;
	bool nowscore;
}SCORE ;

typedef struct
{
	bool live;
	int x, y;
	char count;
}CARD_EFECT;

static bool FadeSwitch = false;
namespace
{
	//手紙開きよう
	int g_op;
	//全体用のカウンタ
	int g_count;
	//ランダム用
	int g_ran;
	//表示切り替え用
	bool g_rank;
	bool g_allscore;
	bool g_card;
	//表示カード
	CARD_TYPE card;
	//スコア透過よう
	int g_scoreAlfh;
	
	CARD_EFECT g_efe[CARD_EFECT_MAX];

};
static	SCORE g_score[SCORE_MAX];


void InitScore(void)
{
	for (int i = SCORE_MAX - 1; i >= 0; i--)
	{
		g_score[i].totalscore += g_score[i+1].totalscore + 100;
		g_score[i].rank = D;
	}
}

void InitResalte(void)
{
	CreateSound(SOUND_BGM_MORI);
	FadeSwitch = false;
	for (int i = 0; i < SCORE_MAX-1; i++)
	{
		g_score[i].nowscore = false;
	}
	//エフェクトのリセット
	for (int i = 0; i < SCORE_MAX ; i++)
	{
		g_efe[i].live = false;
		g_efe[i].count = 0;
	}
	
	// -- Resalte　-- を使う前にやる
	g_trans = Open;
	g_op =0;
	g_count = 0;
	g_rank = false;
	g_allscore = false;
	g_scoreAlfh = 255;
	g_card = false;

	card = CARD_TYPE_AQUA;
	AlignmentScore();
}


void NewScore(int time, int enemy , CARD_TYPE type)
{
	card = type;
	int score =0;
	score = time * 100;
	score += enemy * 30;

	g_score[7].totalscore = score;
	//新しいスコアのランク付け
	g_score[7].nowscore = true;
	g_score[7].rank = D;
	if (score > RANK_C)
	{
		g_score[7].rank = C;
		if (score > RANK_B)
		{
			g_score[7].rank = B;
			if (score > RANK_A) 
			{
				g_score[7].rank = A;
				if (score > RANK_S)
				{
					g_score[7].rank = S;
				}
			}
		}
	}
	InitResalte();
	AlignmentScore();
}

// -- SCOREの再整列 --
void AlignmentScore()
{
	//今回のスコアのナンバー
	char now;
	for (int i = SCORE_MAX - 2; i > 0; i--)
	{
		if (g_score[7].totalscore <= g_score[i].totalscore)
		{
			now = i;
			break;
		}
	}
	//整列
	for (int i = SCORE_MAX -1; i < now; i--)
	{
		SCORE one;
		one = g_score[i];
		g_score[i] = g_score[i - 1];
		g_score[i - 1] = one;
	}
}

void UpdateResalte(void)
{
	//Fade用
	if (GetKeyboardPress(DIK_RETURN) )
	{
		StartFade(Out, White);
		FadeSwitch = true;
	}
	if (FadeSwitch)
	{
		if (GetState() == After)
		{
			StartFade(In, White);
			ChangeScene(SCENE_TITLE);
		}
	}

	g_count++;
	switch (g_trans)
	{
	case Open:
		if (g_count % 5 == 0)
		{
			g_op++;
			if (g_op >= 9)
			{//手紙終了
				g_trans = DisplayScore;
				g_count = 1;
			}
		}
		break;
	case DisplayScore:
		g_ran = rand() % 100000;
		if (g_count % SCORE_TIME == 0)
		{
			g_trans = DisplayRank;
			g_count = 1;
		}
		break;

	case DisplayRank:
		if (g_count % 20 == 0)
		{
			g_rank = true;
			g_trans = DisplayAllScore;
		}
		break;

	case DisplayAllScore:
		g_scoreAlfh --;
		g_allscore = true;
		g_card = true;
		if (g_scoreAlfh <= 0)
		{
			g_trans = Stop;
		}
		break;
	case Stop:
		break;
	}

	UpdateCardEfect();
}

void DrawResalte(void)
{
	// BG
	SetTexture(TEX_RESALTE_BG);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0, 0, 1920, 1080, 0, 0,1920, 1080);

	DrawCardEfect();

	FontResize(150);
	FontInterval(-50);
	if (g_trans != Open)
	{//手紙Open
		SetTexture(TEX_TRAIN_UI_01V2);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(100, 80, 1000, 900, 491.6f * 9,0, 491.6f, 384);
		DestroySound(SOUND_SE_PAGE);
		if (g_trans != DisplayScore)
		{//今のスコア表示
			g_ran = g_score[7].totalscore;
		}
		NumberTexChange(TEX_NUMBER_02);
		DrawAllNum(g_ran, 5, false, 1125, 100);

		if (g_rank)
		{//今のランク表示
			SetTexture(TEX_RANK_S + g_score[7].rank);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			DrawPolygon(1650, 25, 200, 200, 0, 0, 113, 100);
		}
		if (g_allscore)
		{
			for (int i = 0; i < SCORE_MAX - 1; i++)
			{
				NumberTexChange(TEX_RANK_NUM);
				DrawNumber(i, 200, 200 + (i * 100));
				NumberTexChange(TEX_NUMBER_02);
				DrawAllNum(g_score[i].totalscore, 5, true, 320, 200 + (i * 100));
				SetTexture(TEX_RANK_S + g_score[i].rank);
				SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
				DrawPolygon(880, 220 + (i * 100), 100, 100, 0, 0, 113, 100);

				if (g_score[i].nowscore)
				{
					SetTexture(TEX_UNDERBER);
					SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
					DrawPolygon(320, 220 + (i * 100), 600, 100, 0, 0, 100, 100);
				}
			}
		}
	}
	switch (g_trans)
	{
	case Open:
		CreateSound(SOUND_SE_PAGE);
		SetTexture(TEX_TRAIN_UI_01V2);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(100, 80, 1000, 900, 491.6f * g_op, 0, 491.6f, 384);
		break;

	case DisplayAllScore:
		SetTexture(TEX_TRAIN_UI_01V2);
		SetPolygonColor(D3DCOLOR_ARGB(g_scoreAlfh, 255, 255, 255));
		DrawPolygon(100, 80, 1000, 900, 491.6f * g_op, 0, 491.6f, 384);
		break;
	}

	if (g_card)
	{
		switch (card)
		{
		case CARD_TYPE_FIRE:
			SetTexture(TEX_UI_CARD_FLAME);
			break;
		case CARD_TYPE_AQUA:
			SetTexture(TEX_UI_CARD_AQUA);
			break;
		case CARD_TYPE_THUNDER:
			SetTexture(TEX_UI_CARD_THUNDER);
			break;

		}
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(1300, 300, 300 *1.3, 533 * 1.3, 0, 0, 300, 533);
	}
	
}

void UninitResalte(void)
{
	DestroySound(SOUND_BGM_MORI);
	// -- Resalte　-- を使う前にやる
	g_trans = Open;
	g_op = 0;
	g_count = 0;
	g_rank = false;
	g_allscore = false;
	g_scoreAlfh = 255;
	g_card = false;
}

// -- efect用 --
void DrawCardEfect(void)
{
	for (int i = 0; i < CARD_EFECT_MAX; i++)
	{
		if (g_efe[i].live)
		{
			switch (card)
			{
			case CARD_TYPE_NULL:
				break;
			case CARD_TYPE_FIRE:
				SetTexture(TEX_EFECT_FIRE);
				SetPolygonColor(D3DCOLOR_ARGB(150, 255, 255, 255));
				DrawPolygon(g_efe[i].x, g_efe[i].y, 300, 300, 192 * g_efe[i].count, 0, 192, 108);
				break;
			case CARD_TYPE_AQUA:
				SetTexture(TEX_EFECT_AQUA);
				SetPolygonColor(D3DCOLOR_ARGB(150, 255, 255, 255));
				DrawPolygon(g_efe[i].x, g_efe[i].y, 300, 300, 192 * g_efe[i].count, 0, 192, 134);
				break;
			case CARD_TYPE_THUNDER:
				SetTexture(TEX_EFECT_THANDER);
				SetPolygonColor(D3DCOLOR_ARGB(150, 255, 255, 255));
				DrawPolygon(g_efe[i].x, g_efe[i].y, 300, 300, 96 * g_efe[i].count, 0, 96, 68);
				break;
			}
		}
	}
}

void CreateCardEfect()
{
	for (int i = 0; i < CARD_EFECT_MAX; i++)
	{
		if (g_efe[i].live)
		{
			continue;
		}
		else
		{
			g_efe[i].live = true;
			g_efe[i].count = 0;
			g_efe[i].x = rand() % 1600;
			g_efe[i].y = rand() % 700;
			break;
		}
	}
}

void UpdateCardEfect()
{
	if (g_count % 5 == 0)
	{
		for (int i=0; i<CARD_EFECT_MAX ;i++)
		{
			if (g_efe[i].live)
			{
				g_efe[i].count++;
				if (g_efe[i].count > 10)
				{
					g_efe[i].count = 0;
					g_efe[i].live = false;
				}
			}
		}
	}

	if (g_count % 10 == 0)
	{
		CreateCardEfect();
	}
}
