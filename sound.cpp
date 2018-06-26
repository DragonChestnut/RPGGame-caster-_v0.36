//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include <XAudio2.h>
#include "sound.h"


//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

SOUNDALL g_sound[SOUND_LABEL_MAX];
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"sound/bgm/Wolf_Dead.wav", 0},		// BGM0
	{ "sound/bgm/Wolf.wav", 0 },
	{ "sound/bgm/water.wav", 0 },
	{ "sound/bgm/title.wav", -1 },
	{ "sound/bgm/Mori_Bgm.wav", -1 },
	{ "sound/bgm/maxwater2.wav", 0 },
	{ "sound/bgm/MAXwater.wav", 0 },
	{ "sound/bgm/maxkaminari.wav", 0 },
	{ "sound/bgm/maxfire.wav", 0 },
	{ "sound/bgm/Machi_Bgm.wav", -1 },
	{ "sound/bgm/kiru.wav", 0 },
	{ "sound/bgm/kaminari.wav", 0 },
	{ "sound/bgm/hahaha.wav", 0 },
	{ "sound/bgm/gameover.wav", 0 },
	{ "sound/bgm/flydead.wav", 0 },
	{ "sound/bgm/fly.wav", -1 },
	{ "sound/bgm/fire.wav", 0 },
	{ "sound/bgm/dameji.wav", 0 },
	{ "sound/bgm/card2.wav", 0 },
	{ "sound/bgm/Card_Drow.wav", 0 },
	{ "sound/bgm/card.wav", 0 },
	{ "sound/bgm/attack1.wav", 0 },
	{ "sound/bgm/AshiOto.wav", 0 },
	{ "sound/bgm/GameStart.wav", 0 },
	{ "sound/bgm/Page.wav", 0 },
	{ "sound/bgm/battle_bgm.wav", -1 },
	{ "sound/bgm/box_dead.wav", 0 },
	{ "sound/bgm/Drow_Card.wav", 0 },
	{ "sound/bgm/enemy_see.wav", 0 },
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		switch (i)
		{
		case 0:g_sound[i].SoundNum = SOUND_WOLF_DEAD; break;
		case 1:g_sound[i].SoundNum = SOUND_WOLF; break;
		case 2:g_sound[i].SoundNum = SOUND_WATER; break;
		case 3:g_sound[i].SoundNum = SOUND_BGM_TITLE; break;
		case 4:g_sound[i].SoundNum = SOUND_BGM_MORI; break;
		case 5:g_sound[i].SoundNum = SOUND_ATTACK_WATER; break;
		case 6:g_sound[i].SoundNum = SOUND_SP_WATER; break;
		case 7:g_sound[i].SoundNum = SOUND_ATTACK_KAMINARI; break;
		case 8:g_sound[i].SoundNum = SOUND_ATTACK_FIRE; break;
		case 9:g_sound[i].SoundNum = SOUND_BGM_MACHI; break;
		case 10:g_sound[i].SoundNum = SOUND_ATTACK_ALL; break;
		case 11:g_sound[i].SoundNum = SOUND_SP_KAMINARI; break;
		case 12:g_sound[i].SoundNum = SOUND_SE_HAHAHA; break;
		case 13:g_sound[i].SoundNum = SOUND_SE_GAMEOVER; break;
		case 14:g_sound[i].SoundNum = SOUND_FLY_DEAD; break;
		case 15:g_sound[i].SoundNum = SOUND_FLY; break;
		case 16:g_sound[i].SoundNum = SOUND_SP_FIRE; break;
		case 17:g_sound[i].SoundNum = SOUND_SE_BEHIT; break;
		case 18:g_sound[i].SoundNum = SOUND_ATTACK_02; break;
		case 19:g_sound[i].SoundNum = SOUND_DROW_02; break;
		case 20:g_sound[i].SoundNum = SOUND_DROW_01; break;
		case 21:g_sound[i].SoundNum = SOUND_ATTACK_01; break;
		case 22:g_sound[i].SoundNum = SOUND_SE_ASHIOTO; break;
		case 23:g_sound[i].SoundNum = SOUND_SE_GAMESTART; break;
		case 24:g_sound[i].SoundNum = SOUND_SE_PAGE; break;
		case 25:g_sound[i].SoundNum = SOUND_BGM_BATTLE; break;
		case 26:g_sound[i].SoundNum = SOUND_BOX_DEAD; break;
		case 27:g_sound[i].SoundNum = SOUND_DROW_CARD; break;
		case 28:g_sound[i].SoundNum = SOUND_ENEMY_SEE; break;
		default:
			break;
		}
		g_sound[i].SoundSwitch = false;
	}

	//
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void StopSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}


void CreateSound(int SoundNum)
{
	if (!g_sound[SoundNum].SoundSwitch)
	{
		g_sound[SoundNum].SoundSwitch = true;
		PlaySound(g_sound[SoundNum].SoundNum);
	}
}

void DestroySound(int SoundNum)
{
	if (g_sound[SoundNum].SoundSwitch)
	{
		g_sound[SoundNum].SoundSwitch = false;
		StopSound(g_sound[SoundNum].SoundNum);
	}
}

void ResetSound(void)
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		switch (i)
		{
		case 0:g_sound[i].SoundNum = SOUND_WOLF_DEAD; break;
		case 1:g_sound[i].SoundNum = SOUND_WOLF; break;
		case 2:g_sound[i].SoundNum = SOUND_WATER; break;
		case 3:g_sound[i].SoundNum = SOUND_BGM_TITLE; break;
		case 4:g_sound[i].SoundNum = SOUND_BGM_MORI; break;
		case 5:g_sound[i].SoundNum = SOUND_ATTACK_WATER; break;
		case 6:g_sound[i].SoundNum = SOUND_SP_WATER; break;
		case 7:g_sound[i].SoundNum = SOUND_ATTACK_KAMINARI; break;
		case 8:g_sound[i].SoundNum = SOUND_ATTACK_FIRE; break;
		case 9:g_sound[i].SoundNum = SOUND_BGM_MACHI; break;
		case 10:g_sound[i].SoundNum = SOUND_ATTACK_ALL; break;
		case 11:g_sound[i].SoundNum = SOUND_SP_KAMINARI; break;
		case 12:g_sound[i].SoundNum = SOUND_SE_HAHAHA; break;
		case 13:g_sound[i].SoundNum = SOUND_SE_GAMEOVER; break;
		case 14:g_sound[i].SoundNum = SOUND_FLY_DEAD; break;
		case 15:g_sound[i].SoundNum = SOUND_FLY; break;
		case 16:g_sound[i].SoundNum = SOUND_SP_FIRE; break;
		case 17:g_sound[i].SoundNum = SOUND_SE_BEHIT; break;
		case 18:g_sound[i].SoundNum = SOUND_ATTACK_02; break;
		case 19:g_sound[i].SoundNum = SOUND_DROW_02; break;
		case 20:g_sound[i].SoundNum = SOUND_DROW_01; break;
		case 21:g_sound[i].SoundNum = SOUND_ATTACK_01; break;
		default:
			break;
		}
		g_sound[i].SoundSwitch = false;
	}
}