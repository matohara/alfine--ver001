//=============================================================================
//
// カメラ処理 [model.cpp]
// Author : 初 景新
//
//=============================================================================
#include "Camera.h"
#include "input.h"
#include "DebugProcess.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CAMERA_GAZE_X		(0.0f)		// カメラ1(Main)視点の初期位置(X座標)
#define	CAMERA_GAZE_Y		( 250.0f)	// カメラ1(Main)視点の初期位置(Y座標)
#define	CAMERA_GAZE_Z		(-380.0f)		// カメラ1(Main)視点の初期位置(Z座標)

#define	CAMERA_MOVE_VALUE	(20.0f)		// 移動量

#define CtoA_INTERVAL_MAX	(320.0f)	// カメラと注視点間の最大距離
#define CtoA_INTERVAL_MIN	(160.0f)	// カメラと注視点間の最小距離
//#define CAMERA_SPEED_VALUE		(0.001f)		// カメラ感度調整時変動量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		s_pCameraPosition;		// カメラの視点
D3DXVECTOR3		s_pCameraGaze;			// カメラの視線先
D3DXVECTOR3		s_vCameraUpVector;		// カメラの上方向ベクトル
D3DXVECTOR3		s_rCameraRotation;		// カメラの回転

float			s_ctaInterval;			// カメラの視点と視線先の距離

D3DXMATRIX		s_mtxView;				// ビューマトリックス
D3DXMATRIX		s_mtxProjection;		// プロジェクションマトリックス

int Angle = 37;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	// カメラの初期化
	s_pCameraGaze = D3DXVECTOR3(CAMERA_GAZE_X, CAMERA_GAZE_Y, CAMERA_GAZE_Z);

	s_pCameraPosition.y = 0.0f;
	s_pCameraPosition.y = 100.0f * sinf(D3DXToRadian(Angle));
	s_pCameraPosition.z = 100.0f * -cosf(D3DXToRadian(Angle));
	s_pCameraPosition += s_pCameraGaze;

	s_vCameraUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	s_rCameraRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視線先までの距離を記録
	float fVecX, fVecZ;
	fVecX = s_pCameraPosition.x - s_pCameraGaze.x;
	fVecZ = s_pCameraPosition.z - s_pCameraGaze.z;
	s_ctaInterval = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(void)
{
	float move = 1.0f;

	// ホールド・オン
	if (GetKeyboardPress(DIK_W))
	{
		s_pCameraPosition.z += move;
		s_pCameraGaze.z += move;
	}
	if (GetKeyboardPress(DIK_S))
	{
		s_pCameraPosition.z -= move;
		s_pCameraGaze.z -= move;
	}
	if (GetKeyboardPress(DIK_E))
	{
		s_pCameraPosition.y += move;
		s_pCameraGaze.y += move;
	}
	if (GetKeyboardPress(DIK_D))
	{
		s_pCameraPosition.y -= move;
		s_pCameraGaze.y -= move;
	}
	if (GetKeyboardTrigger(DIK_Q))
	{
		Angle++;
		s_pCameraPosition.y = 100.0f * sinf(D3DXToRadian(Angle));
		s_pCameraPosition.z = 100.0f * -cosf(D3DXToRadian(Angle));
		s_pCameraPosition += s_pCameraGaze;
	}
	if (GetKeyboardTrigger(DIK_A))
	{
		Angle--;
		s_pCameraPosition.y = 100.0f * sinf(D3DXToRadian(Angle));
		s_pCameraPosition.z = 100.0f * -cosf(D3DXToRadian(Angle));
		s_pCameraPosition += s_pCameraGaze;
	}

	PrintDebugProcess("カメラ位置 : (%f, %f, %f)\n", s_pCameraPosition.x, s_pCameraPosition.y, s_pCameraPosition.z);
	PrintDebugProcess("カメラ視線 : (%f, %f, %f)\n", s_pCameraGaze.x, s_pCameraGaze.y, s_pCameraGaze.z);
	PrintDebugProcess("カメラ角度 : (%d)\n", Angle);
}

//=============================================================================
// 描画処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ビューマトリックス */
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&s_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&s_mtxView,
		&s_pCameraPosition,		// カメラの視点
		&s_pCameraGaze,			// 視線先
		&s_vCameraUpVector);	// 上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &s_mtxView);


	/* プロジェクションマトリックス */
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&s_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&s_mtxProjection,
		VIEW_ANGLE,		// ビュー平面の視野角
		VIEW_ASPECT,	// ビュー平面のアスペクト比
		VIEW_NEAR_Z,	// ビュー平面のNearZ値
		VIEW_FAR_Z);	// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &s_mtxProjection);

}

//=============================================================================
// カメラ情報取得関数
//=============================================================================
D3DXVECTOR3 GetCamera(int status)
{
	switch (status)
	{
	case CAMERA_POSITION:
		return s_pCameraPosition;	// カメラ位置
		break;

	case CAMERA_FOCUS:
		return s_pCameraGaze;		// カメラの視線先
		break;

	case CAMERA_GAZE:
		return (s_pCameraGaze - s_pCameraPosition);	// カメラの視線先
		break;

	case CAMERA_ROTATION:
		return s_rCameraRotation;	// カメラの回転角(ラジアン)
		break;

	case CAMERA_UPSIDE:
		return s_vCameraUpVector;	// カメラの上方向
		break;

	default:
		// 情報なし
		break;
	}

	return s_pCameraPosition;
}

//=============================================================================
// カメラ情報取得関数
//=============================================================================
void SetCameraStatus(int status, D3DXVECTOR3 vec)
{
	switch (status)
	{
	case CAMERA_POSITION:
		s_pCameraPosition = vec;	// カメラ位置
		break;

	case CAMERA_FOCUS:
		s_pCameraGaze = vec;		// カメラの視線先
		break;

	case CAMERA_ROTATION:
		s_rCameraRotation = vec;	// カメラの回転角(ラジアン)
		break;

	case CAMERA_UPSIDE:
		s_vCameraUpVector = vec;	// カメラの上方向
		break;

	default:
		// 情報なし
		break;
	}
}

//=============================================================================
// カメラ上方ベクトル可動化 (視線向きに対し垂直)
//=============================================================================
D3DXVECTOR3 SetMovableCameraUpVector(D3DXVECTOR3 Vector)
{
	D3DXVECTOR3 subVec;
	D3DXVECTOR3 retVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&subVec, &Vector, &retVec);
	D3DXVec3Cross(&retVec, &Vector, &subVec);

	s_vCameraUpVector = retVec;

	return retVec;
}


//=============================================================================
// ビューマトリックス取得関数
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return s_mtxView;
}

