#include "main.h"
#include "debug.h"
#include <stdio.h>

#ifdef _DEBUG
static LPD3DXFONT g_pFont = NULL;
LPDIRECT3DDEVICE9 pDevice;
#endif // defined(_DEBUG)||defined(DEBUG)


void InitDebugText(void)
{
#ifdef _DEBUG
	pDevice = GetD3DDevice();

	D3DXCreateFont(pDevice, 18, 0, 0, 0, false, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Terminal",&g_pFont);
#endif // defined(_DEBUG)||defined(DEBUG)
}
void UninitDebugText(void)
{
#ifdef _DEBUG
	if (g_pFont)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif // defined(_DEBUG)||defined(DEBUG)
}

void DebugText(int x, int y, const char* pFormat, ...)
{
	//#if defined(_DEBUG)||defined(DEBUG)
	#ifdef _DEBUG
	va_list argp;
	char strBuf[512];
	va_start(argp, pFormat);
	vsprintf_s(strBuf, 512, pFormat,argp);
	va_end(argp);

	RECT rect = {
		x,y,WINDOW_WIDTH,WINDOW_HEIGHT
	};

	g_pFont->DrawText(NULL, strBuf, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(32, 255, 64, 255));
	#endif // defined(_DEBUG)||defined(DEBUG)

}

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}DEBUG_VERTEX;

#define FVF_DEBUG (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

void DebugPolygon(int n, float x, float y, float r)
{
#ifdef _DEBUG
	pDevice = GetD3DDevice();
	const float C_R = D3DX_PI * 2 / n;
	DEBUG_VERTEX* pV = (DEBUG_VERTEX*)malloc(sizeof(DEBUG_VERTEX)*(n+1));
		for (int i = 0; i < (n+1); i++)
		{
			pV[i].pos.x = x + cos(C_R*i)*r;
			pV[i].pos.y = y + sin(C_R*i)*r;
			pV[i].pos.z = 1.0f;
			pV[i].pos.w = 1.0f;
			pV[i].color = D3DCOLOR_RGBA(128, 255, 32, 255);
		}
	
		pDevice->SetTexture(0, NULL);
		pDevice->SetFVF(FVF_DEBUG);
		pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, n, pV, sizeof(DEBUG_VERTEX));

		free(pV);
#endif
}
