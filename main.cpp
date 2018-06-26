#include "main.h"
#include "input.h"
#include "debug.h"
#include "Game.h"
#include "scene.h"
#include "sound.h"



#define CLASS_NAME      "Sample"
#define WINDOW_NAME     "Sample App"


// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

// �O���[�o���ϐ�
static HWND hWnd=NULL;


DWORD TimeNow;
DWORD TimeOld;
static int nCount;
static int CountFrame;

static float r = 255;
static float g = 255.0;
static float b = 255.0;
static float a2 = 0;
static float a3 = 0;
static float alice_x = 300;
static float alice_y = 300;
static float doichux = 600;
static float doichuy = 10;
static float g_ftestangle = 0.0f;
static float g_fScale = 1.0f;

static D3DLIGHT9 light;
static D3DLIGHT9 light1;
static D3DLIGHT9 light2;


static LPDIRECT3D9        g_pD3D = NULL;
static LPDIRECT3DDEVICE9  g_pD3DDevice = NULL;

float x, y;
#ifdef _DEBUG
//LPD3DXFONT	  
#endif

// �E�B���h�E�v���V�[�W���A�E�B���h�E�ɑ΂��郁�b�Z�[�W�������s��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// �E�B���h�E���j�����ꂽ�Ƃ�
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT���b�Z�[�W�����b�Z�[�W�L���[�ɑ���
		return 0;
	}
	// �f�t�H���g�̃��b�Z�[�W�������s��
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	RegisterClassEx(&wcex);

	hWnd = CreateWindowEx
	(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_MAXIMIZEBOX ^ WS_SIZEBOX ^ (WS_OVERLAPPEDWINDOW),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);


	if (!Init(hInstance, hWnd, TRUE))
	{
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;


	TimeNow = TimeOld = timeGetTime();

	// ����\�̐ݒ�
	timeBeginPeriod(1);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W����
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// �Q�[������
			TimeNow = timeGetTime();

			if ((TimeNow - TimeOld) * 60 >= (1000))
			{
				// �X�V
				Update();
				// �`��
				Draw();

				TimeOld = TimeNow;
			}
		}
	}

	Uninit();

	timeEndPeriod(1);

	return (int)msg.wParam;
}

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// Direct3D�I�u�W�F�N�g�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE d3ddm;

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// DirectX�f�o�C�X�̍쐬
	if (FAILED(g_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{
		// ��L�̐ݒ肪���s������
		MessageBox(hWnd, "DirectX�̏����������s���܂���", "�G���[", MB_OK);
		return false;
	}
	x = 0;
	y = 0;

	// �����_�[�X�e�[�g�̐ݒ�					 SRC_RGB * SRC_a + DEST_RGB * (1 - SRC_a)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	  // ������`�����́A�|���S���e�N�X�`��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // ���łɕ`�悵��

																		  // �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �t�B���^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	InitKeyboard(hInstance, hWnd);


	nCount = 0;
	CountFrame = 0;

	InitDebugText();
	InitAllScene();
	InitSound(hWnd);
	InitScene();
	return true;

}

void Uninit(void)
{

	UninitDebugText();
	UninitKeyboard();
	UninitAllScene();
	UninitScene();
	if (g_pD3DDevice != NULL)
	{
		// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

void Update(void)
{	
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		return;
	}
	//�}�e���A���ݒ�
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	//�}�e���A���ǉ�(�w���F�ݒ�)
	mat.Ambient.r = 0.9f;
	mat.Ambient.g = 0.9f;
	mat.Ambient.b = 0.9f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);

	//���C�g�ݒ�
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDor(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDor);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	//�}�e���A���ǉ�
	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);


	//ZeroMemory(&light1, sizeof(light1));
	//light1.Type = D3DLIGHT_DIRECTIONAL;
	//D3DXVECTOR3 vecDor1(1.0f, 0.0f, 1.0f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&light1.Direction, &vecDor1);
	//light1.Diffuse.r = 0.0f;
	//light1.Diffuse.g = 1.0f;
	//light1.Diffuse.b = 0.0f;
	//light1.Diffuse.a = 1.0f;
	////�}�e���A���ǉ�
	//light1.Ambient.r = 1.0f;
	//light1.Ambient.g = 1.0f;
	//light1.Ambient.b = 1.0f;
	//light1.Ambient.a = 1.0f;
	//pDevice->SetLight(1, &light1);
	////pDevice->LightEnable(1, TRUE);

	//ZeroMemory(&light2, sizeof(light2));
	//light2.Type = D3DLIGHT_DIRECTIONAL;
	//D3DXVECTOR3 vecDor2(1.0f, 0.0f, 1.0f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&light2.Direction, &vecDor2);
	//light2.Diffuse.r = 0.0f;
	//light2.Diffuse.g = 0.0f;
	//light2.Diffuse.b = 1.0f;
	//light2.Diffuse.a = 1.0f;
	////�}�e���A���ǉ�
	//light2.Ambient.r = 1.0f;
	//light2.Ambient.g = 1.0f;
	//light2.Ambient.b = 1.0f;
	//light2.Ambient.a = 1.0f;
	//pDevice->SetLight(2, &light2);
	////pDevice->LightEnable(2, TRUE);

	//�O���[�h���A���r�G���g�̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	UpdateKeyboard();
	UpdateScene();
}

void Draw(void)
{
	g_pD3DDevice->Clear
	(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(96,96, 96, 255),
		1.0f,										   // Z�o�b�t�@�̃N���A�l
		0
	);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawScene();
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present
	(
		NULL, NULL, NULL, NULL
	);
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	// Direct3D�f�o�C�X�̎擾
	return g_pD3DDevice;
}