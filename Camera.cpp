//=============================================================================
//
// �J�������� [model.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Camera.h"
#include "input.h"
#include "DebugProcess.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CAMERA_GAZE_X		(0.0f)		// �J����1(Main)���_�̏����ʒu(X���W)
#define	CAMERA_GAZE_Y		( 250.0f)	// �J����1(Main)���_�̏����ʒu(Y���W)
#define	CAMERA_GAZE_Z		(-380.0f)		// �J����1(Main)���_�̏����ʒu(Z���W)

#define	CAMERA_MOVE_VALUE	(20.0f)		// �ړ���

#define CtoA_INTERVAL_MAX	(320.0f)	// �J�����ƒ����_�Ԃ̍ő勗��
#define CtoA_INTERVAL_MIN	(160.0f)	// �J�����ƒ����_�Ԃ̍ŏ�����
//#define CAMERA_SPEED_VALUE		(0.001f)		// �J�������x�������ϓ���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		s_pCameraPosition;		// �J�����̎��_
D3DXVECTOR3		s_pCameraGaze;			// �J�����̎�����
D3DXVECTOR3		s_vCameraUpVector;		// �J�����̏�����x�N�g��
D3DXVECTOR3		s_rCameraRotation;		// �J�����̉�]

float			s_ctaInterval;			// �J�����̎��_�Ǝ�����̋���

D3DXMATRIX		s_mtxView;				// �r���[�}�g���b�N�X
D3DXMATRIX		s_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X

int Angle = 37;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	// �J�����̏�����
	s_pCameraGaze = D3DXVECTOR3(CAMERA_GAZE_X, CAMERA_GAZE_Y, CAMERA_GAZE_Z);

	s_pCameraPosition.y = 0.0f;
	s_pCameraPosition.y = 100.0f * sinf(D3DXToRadian(Angle));
	s_pCameraPosition.z = 100.0f * -cosf(D3DXToRadian(Angle));
	s_pCameraPosition += s_pCameraGaze;

	s_vCameraUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	s_rCameraRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������܂ł̋������L�^
	float fVecX, fVecZ;
	fVecX = s_pCameraPosition.x - s_pCameraGaze.x;
	fVecZ = s_pCameraPosition.z - s_pCameraGaze.z;
	s_ctaInterval = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(void)
{
	float move = 1.0f;

	// �z�[���h�E�I��
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

	PrintDebugProcess("�J�����ʒu : (%f, %f, %f)\n", s_pCameraPosition.x, s_pCameraPosition.y, s_pCameraPosition.z);
	PrintDebugProcess("�J�������� : (%f, %f, %f)\n", s_pCameraGaze.x, s_pCameraGaze.y, s_pCameraGaze.z);
	PrintDebugProcess("�J�����p�x : (%d)\n", Angle);
}

//=============================================================================
// �`�揈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* �r���[�}�g���b�N�X */
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&s_mtxView,
		&s_pCameraPosition,		// �J�����̎��_
		&s_pCameraGaze,			// ������
		&s_vCameraUpVector);	// �����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_mtxView);


	/* �v���W�F�N�V�����}�g���b�N�X */
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&s_mtxProjection,
		VIEW_ANGLE,		// �r���[���ʂ̎���p
		VIEW_ASPECT,	// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_mtxProjection);

}

//=============================================================================
// �J�������擾�֐�
//=============================================================================
D3DXVECTOR3 GetCamera(int status)
{
	switch (status)
	{
	case CAMERA_POSITION:
		return s_pCameraPosition;	// �J�����ʒu
		break;

	case CAMERA_FOCUS:
		return s_pCameraGaze;		// �J�����̎�����
		break;

	case CAMERA_GAZE:
		return (s_pCameraGaze - s_pCameraPosition);	// �J�����̎�����
		break;

	case CAMERA_ROTATION:
		return s_rCameraRotation;	// �J�����̉�]�p(���W�A��)
		break;

	case CAMERA_UPSIDE:
		return s_vCameraUpVector;	// �J�����̏����
		break;

	default:
		// ���Ȃ�
		break;
	}

	return s_pCameraPosition;
}

//=============================================================================
// �J�������擾�֐�
//=============================================================================
void SetCameraStatus(int status, D3DXVECTOR3 vec)
{
	switch (status)
	{
	case CAMERA_POSITION:
		s_pCameraPosition = vec;	// �J�����ʒu
		break;

	case CAMERA_FOCUS:
		s_pCameraGaze = vec;		// �J�����̎�����
		break;

	case CAMERA_ROTATION:
		s_rCameraRotation = vec;	// �J�����̉�]�p(���W�A��)
		break;

	case CAMERA_UPSIDE:
		s_vCameraUpVector = vec;	// �J�����̏����
		break;

	default:
		// ���Ȃ�
		break;
	}
}

//=============================================================================
// �J��������x�N�g������ (���������ɑ΂�����)
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
// �r���[�}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return s_mtxView;
}

