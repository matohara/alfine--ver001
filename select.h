//=============================================================================
//
// �Z���N�g�I����ʏ��� [select.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/6/12
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _SELECT_H_
#define _SELECT_H_

// �}�N�������C�u�����g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define INIT_EFFECT					(1)												// �G�t�F�N�g��RGB�̏����l
#define ALPHA_TEST					(125)											// �A���t�@�e�X�g�̃��̒l
#define ALPHA_BASE					(1)												// �e�N�X�`���̃��̒l
#define ALPHA_MAX					(255)											// ���̒l�̍ő�l
#define EFFECT_SPEED				(2)												// �_�ő��x���x

#define	SELECT_BASE_TEXTURE			("data/TEXTURE/Background.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SELECT_BASE_SIZE_X			(SCREEN_WIDTH/2)											// �e�N�X�`���̕�
#define	SELECT_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// �e�N�X�`���̍���
#define SELECT_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// �Z���N�g�����̈ʒu

#define	SELECT_ANIM_TEXTURE			("data/TEXTURE/doraivu03.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SELECT_ANIM_SIZE_X			(250/2)											// �e�N�X�`���̕�
#define	SELECT_ANIM_SIZE_Y			(200/2)											// �e�N�X�`���̍���
#define SELECT_BASE_POS_A			D3DXVECTOR3(700/2.0f,250/2.0f,0.0f)				// �A�j���[�V����:A�̈ʒu
#define SELECT_BASE_POS_D			D3DXVECTOR3(1550/2.0f,250/2.0f,0.0f)			// �A�j���[�V����:D�̈ʒu

#define SELECT_ANIM_PATTERN_DIVIDE_X	(4)															// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SELECT_ANIM_PATTERN_DIVIDE_Y	(2)															// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SELECT_ANIM_PATTERN_NUM		(SELECT_ANIM_PATTERN_DIVIDE_X*SELECT_ANIM_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define SELECT_ANIM_TIME				(6)															// �A�j���[�V�����̐؂�ւ��J�E���g

#define	SELECT_OPTION_TEXTURE			("data/TEXTURE/OptionLogo0.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SELECT_OPTION_SIZE_X			(350/2)											// �e�N�X�`���̕�
#define	SELECT_OPTION_SIZE_Y			(150/2)											// �e�N�X�`���̍���
#define SELECT_OPTION_POS				D3DXVECTOR3(200.0f,600.0f,0.0f)		// UI:"�{�^���������Ă�"

#define	SELECT_OPTION_EFFECT_SIZE_X		(360/2)											// �e�N�X�`���̕�
#define	SELECT_OPTION_EFFECT_SIZE_Y		(160/2)											// �e�N�X�`���̍���

#define	SELECT_TUTORIAL_TEXTURE			("data/TEXTURE/�`���[�g���A���o�[.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SELECT_TUTORIAL_SIZE_X			(600/2)											// �e�N�X�`���̕�
#define	SELECT_TUTORIAL_SIZE_Y			(200/2)											// �e�N�X�`���̍���
#define SELECT_TUTORIAL_POS				D3DXVECTOR3(850.0f,SCREEN_HEIGHT/2.0,0.0f)		// UI:"�`���[�g���A��"

#define SELECT_TUTORIAL_A_POS			D3DXVECTOR3(1000.0f,510.0f,0.0f)		// UI:"�`���[�g���A��A"

#define	SELECT_TUTORIAL_B_SIZE_X		(400/2)											// �e�N�X�`���̕�
#define	SELECT_TUTORIAL_B_SIZE_Y		(150/2)											// �e�N�X�`���̍���
#define SELECT_TUTORIAL_B_POS			D3DXVECTOR3(1100.0f,610.0f,0.0f)		// UI:"�`���[�g���A��A"

#define	SELECT_TUTORIAL_C_SIZE_X		(300/2)											// �e�N�X�`���̕�
#define	SELECT_TUTORIAL_C_SIZE_Y		(100/2)											// �e�N�X�`���̍���
#define SELECT_TUTORIAL_C_POS			D3DXVECTOR3(1100.0f,100,0.0f)		// UI:"�`���[�g���A��A"

#define SELECT_TUTORIAL_D_POS			D3DXVECTOR3(1000.0f,210,0.0f)		// UI:"�`���[�g���A��A"

#define	SELECT_ANY_EFFECT_SIZE_X		(610/2)											// �e�N�X�`���̕�
#define	SELECT_ANY_EFFECT_SIZE_Y		(210/2)											// �e�N�X�`���̍���

#define	SELECT_ANY_B_EFFECT_SIZE_X		(610/2)											// �e�N�X�`���̕�
#define	SELECT_ANY_B_EFFECT_SIZE_Y		(210/2)											// �e�N�X�`���̍���

#define	SELECT_ANY_C_EFFECT_SIZE_X		(610/2)											// �e�N�X�`���̕�
#define	SELECT_ANY_C_EFFECT_SIZE_Y		(210/2)											// �e�N�X�`���̍���


#define COLOR_WHITE						D3DCOLOR_RGBA(255, 255, 255, 255);				// UI�J�[�\���̐F:��
#define COLOR_YELLOW					D3DCOLOR_RGBA(255, 175, 0, 255);				// UI�J�[�\���̐F:���F

// �Z���N�g�\���̐���}�N��
enum
{
	SELECT_BASE,					// �Z���N�g����
	SELECT_ANIM_A,					// �A�j���[�V����:A
	SELECT_ANIM_D,					// �A�j���[�V����:D

	SELECT_OPTION,					// UI:"�I�v�V����"
	SELECT_OPTION_EFFECT,			// UI�G�t�F�N�g:"�I�v�V����"
	SELECT_TUTORIAL,				// UI:"�`���[�g���A��"
	SELECT_TUTORIAL_EFFECT,			// UI�G�t�F�N�g:"�`���[�g���A��"
	SELECT_TUTORIAL_A,				// UI:"�`���[�g���AA\"
	SELECT_TUTORIAL_A_EFFECT,		// UI�G�t�F�N�g:"�`���[�g���A��A"
	SELECT_TUTORIAL_B,				// UI:"�`���[�g���AB\"
	SELECT_TUTORIAL_B_EFFECT,		// UI�G�t�F�N�g:"�`���[�g���A��B"
	SELECT_TUTORIAL_C,				// UI:"�`���[�g���AC\"
	SELECT_TUTORIAL_C_EFFECT,		// UI�G�t�F�N�g:"�`���[�g���A��C"
	SELECT_TUTORIAL_D,				// UI:"�`���[�g���AD\"
	SELECT_TUTORIAL_D_EFFECT,		// UI�G�t�F�N�g:"�`���[�g���A��D"

	SELECT_MAX,						// �Z���N�g�\���̍ő吔
};

// UI�J�[�\������}�N��
enum
{
	SELECT_UI_TUTORIAL,				// UI:"�͂��߂�"
	SELECT_UI_CREDIT,				// UI:"�N���W�b�g"
	SELECT_UI_MAX,					// UI�J�[�\���ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

// �Z���N�g�\����
typedef struct
{

	bool					use;						// �`�搧��ϐ� true:�g�p false:���g�p

	int						CountAnim;					// �A�j���[�V�����J�E���g�ϐ�
	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[�ϐ�

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSelect(int type);							// �����������֐�
void UninitSelect(void);								// �I�������֐�
void UpdateSelect(void);								// �X�V�����֐�
void DrawSelect(void);									// �`�揈���֐�
void SetTextureSelect(int no, int cntPattern);			// �e�N�X�`�����W�̐ݒ�

#endif
