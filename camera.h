#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>


void UpdateCamera(void);

void SetCameraPos(D3DXVECTOR3 CameraPos);/*�J�����̍��W�ݒ�*/
void SetCameraAt(D3DXVECTOR3 CameraAt);/*�J�����̎��_�ݒ�*/

D3DXMATRIX GetView(void);

D3DXMATRIX GetUp(void);

D3DXMATRIX GetFront(void);

D3DXMATRIX GetEye(void);

D3DXMATRIX GetAt(void);

D3DXMATRIX GetRight(void);

void ResetCamera(void);
#endif