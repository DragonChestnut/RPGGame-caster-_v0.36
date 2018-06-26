//================================================
//	�G�t�F�N�g.h
//
//================================================

#include <d3dx9.h>

#ifndef _EFECT_H_
#define _EFECT_H_

#define MAX_EFECT	(1024)
#define TEXTURE_H	(80)
#define TEXTURE_W	(80)

typedef struct
{
	D3DXVECTOR2 vPos;
	bool b_Efect;
	D3DCOLOR color;
	int nLimit;//����
	int nBirth;//�a���^�C�~���O

}EFECT;

enum EFECT_TEX
{
	PLAYER_EFE=0
};

static EFECT g_Efects[MAX_EFECT];
static int g_nEfectFrameCounter = 0 ;

//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************

void InitEfect(void);
void UninitEfect(void);
void UpdateEfect(void);
void DrawEfect(void);

//=======================================================
//	�G�t�F�N�g�̐���
//	x,y... �����ʒu	color... �J�n�ʒu	
//	nLimit...���t���[���������邩
//=======================================================
void CreateEfect(float x, float y, D3DCOLOR color, int nLimit);

//=========================================================
//	�G�t�F�N�g�e�N�X�`���̎w��
//	tex... �G�t�F�N�g�̗񋓂���������
//=========================================================
void EfectTexture(EFECT_TEX tex);

#endif

