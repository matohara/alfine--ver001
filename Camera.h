//=============================================================================
//
// �J�������� [Camera.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SIZE		(10.0f)	// �J�����̓����蔻�莞�Ɏg�p(���Z�ʑ�)

#define	VIEW_ANGLE		(D3DXToRadian(45))								// �r���[���ʂ̎���p(45�x)
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(32768.0f)										// �r���[���ʂ�FarZ�l

enum CAMERA_STATUS
{
	CAMERA_POSITION,	// �J�����̈ʒu
	CAMERA_FOCUS,		// �����_
	CAMERA_GAZE,		// �����x�N�g��
	CAMERA_ROTATION,	// �J�����̉�]
	CAMERA_UPSIDE,		// ������x�N�g��
};

//*****************************************************************************
// �\����
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
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
