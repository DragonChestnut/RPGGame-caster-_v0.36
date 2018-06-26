#include "camera.h"
#include "input.h"
#include "main.h"

static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxProj;

static D3DXVECTOR3 g_up(0.0f, 1.0f, 0.0f);//上ベクトル
static D3DXVECTOR3 g_front(0.0f, 0.0f, 1.0f);//前ベクトル
static D3DXVECTOR3 g_right(1.0f, 0.0f, 1.0f);//右ベクトル

static D3DXVECTOR3 g_eye(-40.0f, 6.0f, -10.0f); //カメラ座標
static D3DXVECTOR3 g_at(-40.0f, 0.0f, 0.0f);//視点座標

static float g_MoveSpeed = 0.1f;//移動速度
static float g_RotateSpeed= D3DXToRadian(1);//回転速度


void UpdateCamera(void)
{
	D3DXMatrixPerspectiveFovLH(&g_mtxProj, D3DX_PI / 3, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	g_front = g_at - g_eye;//前ベクトル=視点座標-カメラ座標
	//D3DXVec3Normalize(&g_front, &g_front);
	D3DXMatrixLookAtLH(&g_mtxView, &g_eye, &g_at, &g_up);

	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProj);
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	//if (GetKeyboardPress(DIK_W))
	//{
	//	D3DXVECTOR3 vec=g_front;
	//	vec.y = 0;
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye+= vec*g_MoveSpeed;
	//	g_at += vec*g_MoveSpeed;
	//}

	//if (GetKeyboardPress(DIK_S))
	//{
	//	D3DXVECTOR3 vec = g_front;
	//	vec.y = 0;
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye -= vec*g_MoveSpeed;
	//	g_at -= vec*g_MoveSpeed;
	//}
	////横移動
	////外積（２本のベクトルに対して直角のベクトルを求める）
	////外積の求め方法（右）
	////D3DXVec3Cross(&右ベクトル,&前ベクトル,&上ベクトル)
	////ノーマライズ
	//if (GetKeyboardPress(DIK_D))
	//{
	//	D3DXVECTOR3 vec = g_right;
	//	D3DXVec3Cross(&vec, &g_up, &g_front);
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye += vec*g_MoveSpeed;
	//	g_at += vec*g_MoveSpeed;
	//}
	//if (GetKeyboardPress(DIK_A))
	//{
	//	D3DXVECTOR3 vec = g_right;
	//	D3DXVec3Cross(&vec, &g_front, &g_up);
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye += vec*g_MoveSpeed;
	//	g_at += vec*g_MoveSpeed;
	//}
	////Y回転
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	D3DXMATRIX rotY;
	//	D3DXMatrixRotationY(&rotY, g_RotateSpeed);
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotY);
	//	g_at = g_eye + g_front;
	//}
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	D3DXMATRIX rotY;
	//	D3DXMatrixRotationY(&rotY, (-g_RotateSpeed));
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotY);
	//	g_at = g_eye + g_front;
	//}
	////x回転
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	D3DXMATRIX rotX;
	//	D3DXMatrixRotationAxis(&rotX,&g_right, (-g_RotateSpeed));
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotX);
	//	D3DXVec3TransformNormal(&g_right, &g_right, &rotX);
	//	D3DXVec3Cross(&g_right, &g_up, &g_front);
	//	D3DXVec3Normalize(&g_right, &g_right);
	//	g_at = g_eye + g_front;
	//}
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	D3DXMATRIX rotX;
	//	D3DXMatrixRotationAxis(&rotX, &g_right, g_RotateSpeed);
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotX);
	//	D3DXVec3TransformNormal(&g_right, &g_right, &rotX);
	//	D3DXVec3Cross(&g_right, &g_up, &g_front);
	//	D3DXVec3Normalize(&g_right, &g_right);
	//	g_at = g_eye + g_front;
	//}
	////視点を中心に回転
	//if (GetKeyboardPress(DIK_Q))
	//{
	//	D3DXMATRIX rotAt;
	//	D3DXMatrixRotationAxis(&rotAt, &g_up, (-g_RotateSpeed));
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotAt);
	//	g_eye =g_at- g_front;
	//}
	//if (GetKeyboardPress(DIK_E))
	//{
	//	D3DXMATRIX rotAt;
	//	D3DXMatrixRotationAxis(&rotAt, &g_up, g_RotateSpeed);
	//	D3DXVec3TransformNormal(&g_front, &g_front, &rotAt);
	//	g_eye = g_at - g_front;
	//}
	////前後に移動
	//if (GetKeyboardPress(DIK_O))
	//{
	//	D3DXVECTOR3 vec = g_front;
	//	vec.z = 0;
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye += vec*g_MoveSpeed;
	//	g_at += vec*g_MoveSpeed;
	//}
	//if (GetKeyboardPress(DIK_P))
	//{
	//	D3DXVECTOR3 vec = g_front;
	//	vec.z= 0;
	//	D3DXVec3Normalize(&vec, &vec);
	//	g_eye -= vec*g_MoveSpeed;
	//	g_at -= vec*g_MoveSpeed;
	//}

	//前後に移動
	//内積
	//	D3DXVec3Dot(&前ベクトル, &dir);
	//ベクトル座標変換
	//D3DXVec3TransformNormal(&向き（前（右）（上））ベクトル, &向き（前（右）（上））ベクトル, &rotY);
	//向きベクトル＝視点ーカメラ座標＝前ベクトル＊視点までの長さ
	//視点＝カメラ座標＋向きベクトル
	////視点までの長さ
	////D3DXVec3Length(&向きベクトル); D3DXVec3Length(&(視点ーカメラ座標));
	if (GetKeyboardPress(DIK_R))
	{
		g_up.x = 0.0f;
		g_up.y = 1.0f;
		g_up.z = 0.0f;
		g_front.x = 0.0f;
		g_front.y = 0.0f;
		g_front.z = 1.0f;
		g_right.x = 1.0f;
		g_right.y = 0.0f;
		g_right.z = 1.0f;
		g_eye.x = 0.0f;
		g_eye.y = 10.0f;
		g_eye.z = -10.0f;
		g_at.x = 0.0f;
		g_at.y = 0.0f;
		g_at.z = 0.0f;
	}
}

void SetCameraPos(D3DXVECTOR3 CameraPos)
{
	g_eye = CameraPos;
}

void SetCameraAt(D3DXVECTOR3 CameraAt)
{
	g_at = CameraAt;
}

D3DXMATRIX GetView(void)
{
	return g_mtxView;
}


D3DXMATRIX GetUp(void)
{
	return g_up;
}

D3DXMATRIX GetFront(void)
{
	return g_front;
}

D3DXMATRIX GetEye(void)
{
	return g_eye;
}

D3DXMATRIX GetAt(void)
{
	return g_at;
}

D3DXMATRIX GetRight(void)
{
	return g_right;
}

void ResetCamera(void)
{
	g_eye.x = -40.f;
	g_eye.y = 6.f;
	g_eye.z = -10.f;
	g_at.x = -40.f;
	g_at.y = 0.f;
	g_at.z = 0.f;
}