#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include "game.h"
#include "main.h"

// ç\ë¢ëÃíËã`
typedef struct {
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;



typedef enum TEXTURE_NUM
{
	TEX_FADE,
	TEX_DEMAGE_INFO,

	//	--	SUPER SKILL	--
	TEX_SUPER_AQUA,
	TEX_SUPER_FLAME,
	TEX_SUPER_THUNDER,

	//	--	TRAIN	--
	TEX_TRAIN_UI_01,
	TEX_TRAIN_UI_01V2,
	TEX_TRAIN_UI_02,
	TEX_TRAIN_UI_03,

	//	--	UI	--
	TEX_UI_BASE,
	TEX_UI_BASE_BACK,
	TEX_UI_HP_BACK,
	TEX_UI_HP_BASE,
	TEX_UI_HP_GAUGE,
	TEX_UI_MP_BACK,
	TEX_UI_MP_BASE,
	TEX_UI_MP_GAUGE,
	TEX_UI_STAR_BACK,
	TEX_UI_STAR_BASE,
	TEX_UI_STAR_GAUGE_01,
	TEX_UI_STAR_GAUGE_02,
	TEX_UI_STAR_GAUGE_03,
	TEX_UI_STAR_GAUGE_04,
	TEX_UI_STAR_GAUGE_05,
	TEX_UI_STAR_GAUGE_06,
	TEX_UI_STAR_GAUGE_07,
	TEX_UI_CARD_BACK,
	TEX_UI_CARD_FLAME,
	TEX_UI_CARD_AQUA,
	TEX_UI_CARD_THUNDER,
	TEX_UI_SP_CARD,
	TEX_UI_SP_MAGIC,
	TEX_UI_SP_SPEEDLINE,
	TEX_UI_SP_COOLTIME,
	TEX_UI_CARD_F_LIGHT,
	TEX_UI_CARD_A_LIGHT,
	TEX_UI_CARD_T_LIGHT,
	TEX_UI_CHARACTER_DOWN,
	TEX_UI_CHARACTER_HAPPY,

	TEX_UI_INFO_K,
	TEX_UI_INFO_MOJI_01,
	TEX_UI_INFO_MOJI_02,
	TEX_UI_INFO_MOJI_03,

	TEX_UI_STORY_K,
	TEX_UI_STORY_01,
	TEX_UI_STORY_02,
	TEX_UI_STORY_03,
	TEX_UI_STORY_04,
	TEX_UI_STORY_05,

	//	--	TITLE	--
	TEX_TITLE_BG,
	TEX_TITLE_01,
	TEX_TITLE_02,
	TEX_TITLE_03,
	TEX_TITLE_04,
	TEX_TITLE_MAX,
	TEX_TITLE_FLICK,
	TEX_TITLE_EFE,


	// -- resalte --
	TEX_RESALTE_BG,

	// -- CLOCK --
	TEX_CLOCK,
	TEX_PIN,

	// -- number --
	TEX_NUMBER_01,
	TEX_CORON,
	TEX_RANK_NUM,
	TEX_UNDERBER,
	TEX_NUMBER_02,

	// -- Rank --
	TEX_RANK_S,
	TEX_RANK_A,
	TEX_RANK_B,
	TEX_RANK_C,
	TEX_RANK_D,


	// -- efect --
	TEX_EFECT_FIRE,
	TEX_EFECT_AQUA,
	TEX_EFECT_THANDER,

	// -- story --
	TEX_STORY_BLACK,
	TEX_STORY_PLOROAG,


	TEX_MAX
};

const TEXTURE TextureMessage[TEX_MAX] =
{
	{ "Texture/fade.png",100,100 },
	{ "Texture/damge_info.png",1280,720 },

	//	--	SUPER SKILL	--
	{ "Texture/SUPER_AQUA.png",3840,100 },
	{ "Texture/SUPER_FLAME.png",3840,100 },
	{ "Texture/SUPER_THUNDER.png",3840,100 },



	//	--	TRAIN	--
	{ "Texture/message.png",10800,200 },
	{ "Texture/message_02.png",4916,384 },
	{ "Texture/Train_00.png",1000,480 },
	{ "Texture/Train_01.png",1000,480 },

	//	--	UI	--
	{ "Texture/UI/BASE/UI_base.png",1920,1080 },
	{ "Texture/UI/BASE/UI_base_back.png",1920,1080 },
	{ "Texture/UI/HP/UI_HP_back.png",1920,1080 },
	{ "Texture/UI/HP/UI_HP_base.png",1920,1080 },
	{ "Texture/UI/HP/UI_HP_gauge.png",25,43 },
	{ "Texture/UI/MP/UI_MP_back.png",1920,1080 },
	{ "Texture/UI/MP/UI_MP_base.png",1920,1080 },
	{ "Texture/UI/MP/UI_MP_gauge.png",26,44 },
	{ "Texture/UI/STAR/UI_star_back.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_base.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge01.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge02.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge03.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge04.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge05.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge06.png",1920,1080 },
	{ "Texture/UI/STAR/UI_star_gauge07.png",1920,1080 },
	{ "Texture/UI/CARD/Card_Back.png",300,533 },
	{ "Texture/UI/CARD/Card_Flame.png",300,533 },
	{ "Texture/UI/CARD/Card_Aqua.png",300,533 },
	{ "Texture/UI/CARD/Card_Thunder.png",300,533 },
	{ "Texture/UI/CARD/Sp_card.png",800,80 },
	{ "Texture/UI/CARD/Sp_magic.png",2100,210 },
	{ "Texture/UI/CARD/Sp_speedline.png",4219,108 },
	{ "Texture/UI/CARD/cooltime.png",100,100 },

	{ "Texture/UI/CARD/card_F.png",400,633 },
	{ "Texture/UI/CARD/card_A.png",400,633 },
	{ "Texture/UI/CARD/card_T.png",400,633 },

	{ "Texture/UI/CHARACTER/character_down.png",900,303 },
	{ "Texture/UI/CHARACTER/character_happy.png",900,303 },

	{ "Texture/info/info_k.png",1280,250 },
	{ "Texture/info/info_moji_01.png",1280,250 },
	{ "Texture/info/info_moji_02.png",1280,250 },
	{ "Texture/info/info_moji_03.png ",1280,250 },

	{ "Texture/info/story_k.png",1280,250 },
	{ "Texture/info/story_01.png",1280,250 },
	{ "Texture/info/story_02.png",1280,250 },
	{ "Texture/info/story_03.png",1280,250 },
	{ "Texture/info/story_04.png",1280,250 },
	{ "Texture/info/story_05.png",1280,250 },

	//	--	TITLE	--
	{ "Texture/TITLE/op02.png",2160,3840 },
	{ "Texture/TITLE/1.png",2046,1447 },
	{ "Texture/TITLE/card2.png",2046,1447 },
	{ "Texture/TITLE/card3.png",2046,1447 },
	{ "Texture/TITLE/card4.png",2046,1447 },
	{ "Texture/TITLE/Title_rogo.png",2046,1447 },
	{ "Texture/TITLE/Title_rogo_1.png",2046,1447 },
	{ "Texture/TITLE/effect000.jpg",80,80 },

		// -- Resalte --
	{ "Texture/resalte/score_BG.png",1920,1080},

	// -- CLOCK --
	{ "Texture/CLOCK/clock.png",400,200 },
	{ "Texture/CLOCK/pin.png",455,60 },


	// -- NUMBER --
	{ "Texture/score/score_01.png",500,200 },
	{ "Texture/score/coron.png",50,100 },
	{ "Texture/score/score_1.png",500,200 },
	{ "Texture/score/Underber.png",100,100 },
	{ "Texture/score/score_02.png",500,200 },


	// -- RANK --
	{ "Texture/score/S.png",113,100 },
	{ "Texture/score/A.png",113,100 },
	{ "Texture/score/B.png",113,100 },
	{ "Texture/score/C.png",113,100 },
	{ "Texture/score/D.png",113,100 },

	// -- efect --
	{ "Texture/resalte/tekiF.png",1920,108 },
	{ "Texture/resalte/tekiw.png",1920,134 },
	{ "Texture/resalte/tekiK.png",960,68 },


	// -- story --
	{ "Texture/story/black.png",25,25 },
	{ "Texture/story/story_01.png",1280,720 },
};


bool InitPolygon();
void UninitPolygon();
void UpdatePolygon();


void SetPolygonColor(D3DCOLOR nColor);
void SetTexture(int nNumTex);
void SetPolygonRotation(float cx, float cy, float angle);
void SetPolygonScale(float cx, float cy, float sx, float sy);
void DrawPolygon(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,bool bAffine = false);

void SetDUIChange(int num);
#endif
