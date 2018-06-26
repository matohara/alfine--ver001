//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Game.h"

#include "main.h"
#include "bg.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
//----��]--------
void CBackTexture::SetBGTStatus(float fX, float fY, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Size = { fX, fY };
	Position = pos;
	Rotation = rot;

	MakeVertex();
}

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBackTexture BackGroundTexture;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(void)
{
	// �e�N�X�`���ǂݍ���
	BackGroundTexture.LoadTexture(TEXTURE_GAME_BG);

	// �����Z�b�g
	BackGroundTexture.SetBGTStatus(700.0f, 400.0f, D3DXVECTOR3(0.0f, -200.0f, 200.0f), D3DXVECTOR3(D3DX_PI / 4.0f, 0.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	BackGroundTexture.ReleaseBuffer();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	BackGroundTexture.Draw();
}
