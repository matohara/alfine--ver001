//=============================================================================
//
// カメラ処理 [Camera.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_SIZE		(10.0f)	// カメラの当たり判定時に使用(正六面体)

#define	VIEW_ANGLE		(D3DXToRadian(45))								// ビュー平面の視野角(45度)
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(32768.0f)										// ビュー平面のFarZ値

enum CAMERA_STATUS
{
	CAMERA_POSITION,	// カメラの位置
	CAMERA_FOCUS,		// 注視点
	CAMERA_GAZE,		// 視線ベクトル
	CAMERA_ROTATION,	// カメラの回転
	CAMERA_UPSIDE,		// 上方向ベクトル
};

//*****************************************************************************
// 構造体
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

D3DXVECTOR3 GetCamera(int status);
void SetCameraStatus(int status, D3DXVECTOR3 vec);
D3DXMATRIX GetMtxView(void);
D3DXVECTOR3 SetMovableCameraUpVector(D3DXVECTOR3 Vector);

#endif
