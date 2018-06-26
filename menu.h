//=============================================================================
//
// �|�[�Y���j���[���� [menu.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/2/26
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _MENU_H_
#define _MENU_H_

// �}�N�������C�u�����g�p�g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EFFECT_MENU_SPEED			(2)															// �_�ő��x���x

#define	MENU_BASE_SIZE_X			(SCREEN_WIDTH/2)											// �|���S���̕�
#define	MENU_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// �|���S���̍���
#define MENU_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// ���j���[�Ó]�̈ʒu

#define	MENU_BLACK_TEXTURE			("data/TEXTURE/�����j���[.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MENU_BLACK_SIZE_X			(380/2)														// �e�N�X�`���̕�
#define	MENU_BLACK_SIZE_Y			(500/2)														// �e�N�X�`���̍���
#define MENU_BLACK_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// �����j���[:A�̈ʒu

#define	MENU_ANY_TEXTURE			("data/TEXTURE/�Â���.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MENU_ANY_SIZE_X				(280/2)														// �e�N�X�`���̕�
#define	MENU_ANY_SIZE_Y				(70/2)														// �e�N�X�`���̍���
#define MENU_ANY_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,450/2.,0.0f)					// �Â���̈ʒu

#define	MENU_ANY_EFFECT_SIZE_X		(290/2)														// �e�N�X�`���̕�
#define	MENU_ANY_EFFECT_SIZE_Y		(80/2)														// �e�N�X�`���̍���

#define	MENU_INIT_TEXTURE			("data/TEXTURE/���Ȃ���.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MENU_INIT_SIZE_X			(280/2)														// �e�N�X�`���̕�
#define	MENU_INIT_SIZE_Y			(70/2)														// �e�N�X�`���̍���
#define MENU_INIT_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,700/2.,0.0f)					// ���Ȃ����̈ʒu

#define	MENU_FINISH_TEXTURE			("data/TEXTURE/�����.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MENU_FINISH_SIZE_X			(180/2)														// �e�N�X�`���̕�
#define	MENU_FINISH_SIZE_Y			(70/2)														// �e�N�X�`���̍���
#define MENU_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,950/2.,0.0f)					// �����̈ʒu

#define	MENU_FINISH_EFFECT_SIZE_X	(190/2)														// �e�N�X�`���̕�
#define	MENU_FINISH_EFFECT_SIZE_Y	(80/2)														// �e�N�X�`���̍���


// ���j���[�\���̐���}�N��
enum
{
	MENU_BASE,						// ���j���[�Ó]
	MENU_BLACK,						// �����j���[
	MENU_ANY,						// UI:"�Â���"
	MENU_ANY_EFFECT,				// UI�G�t�F�N�g:"�Â���"
	MENU_INIT,						// UI:"���Ȃ���"
	MENU_INIT_EFFECT,				// UI�G�t�F�N�g:"���Ȃ���"
	MENU_FINISH,					// UI:"�����"
	MENU_FINISH_EFFECT,				// UI�G�t�F�N�g:"�����"
	MENU_MAX,						// ���j���[�\���̍ő吔
};

// ���j���[�J�[�\������}�N��
enum
{
	MENU_UI_ANY,					// UI:"�Â���"
	MENU_UI_INIT,					// UI:"���Ȃ���"
	MENU_UI_FINISH,					// UI:"�����"
	MENU_UI_MAX,					// UI�J�[�\���ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

// ���j���[�\����
typedef struct
{

	bool					use;						// �`�搧��ϐ� true:�g�p false:���g�p

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}MENU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMenu(int type);								// �����������֐�
void UninitMenu(void);									// �I�������֐�
void UpdateMenu(void);									// �X�V�����֐�
void DrawMenu(void);									// �`�揈���֐�
void SetTextureMenu(int no, int cntPattern);			// �e�N�X�`�����W�̐ݒ�

#endif
