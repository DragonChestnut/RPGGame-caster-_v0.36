#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>


void UpdateCamera(void);

void SetCameraPos(D3DXVECTOR3 CameraPos);/*カメラの座標設定*/
void SetCameraAt(D3DXVECTOR3 CameraAt);/*カメラの視点設定*/

D3DXMATRIX GetView(void);

D3DXMATRIX GetUp(void);

D3DXMATRIX GetFront(void);

D3DXMATRIX GetEye(void);

D3DXMATRIX GetAt(void);

D3DXMATRIX GetRight(void);

void ResetCamera(void);
#endif