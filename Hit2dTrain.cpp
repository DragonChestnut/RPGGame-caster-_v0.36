//======================================================
//
//	2次元衝突
//
//======================================================
#include "Hit2dTrain.h"

//------------------------------------------------------
//	2次元四角の判定
//	四角の真ん中POS.x,y,	幅,高さ
//
//------------------------------------------------------
bool Hit2DTrain(float a_x, float a_z, float a_w, float a_d,
			float b_x, float b_z, float b_w, float b_d)
{
	float ax =(a_x -(a_w/2)); 
	float bx =(b_x-(b_w/2)); 
	
	float az=(a_z-(a_d/2));
	float bz=(b_z-(b_d/2));
	
	if(ax < (bx + b_w)&&(ax + a_w) > bx &&az < (bz + b_d) &&(az + a_d) > bz)
		{
			return true;
		}	
	else 
	{
		return false;
	}
}
			