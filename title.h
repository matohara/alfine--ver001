//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/2/21
//
//=============================================================================


// ���d�C���N���[�h�h�~�̈�
#ifndef _TITLE_H_
#define _TITLE_H_

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

#define	TITLE_BASE_TEXTURE			("data/TEXTURE/title.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_BASE_SIZE_X			(SCREEN_WIDTH/2)											// �e�N�X�`���̕�
#define	TITLE_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// �e�N�X�`���̍���
#define TITLE_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// �^�C�g���w�i�̈ʒu

#define	TITLE_ANIM_TEXTURE			("data/TEXTURE/doraivu03.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_ANIM_SIZE_X			(250/2)											// �e�N�X�`���̕�
#define	TITLE_ANIM_SIZE_Y			(200/2)											// �e�N�X�`���̍���
#define TITLE_BASE_POS_A			D3DXVECTOR3(700/2.0f,250/2.0f,0.0f)				// �A�j���[�V����:A�̈ʒu
#define TITLE_BASE_POS_D			D3DXVECTOR3(1550/2.0f,250/2.0f,0.0f)			// �A�j���[�V����:D�̈ʒu

#define TITLE_ANIM_PATTERN_DIVIDE_X	(4)															// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TITLE_ANIM_PATTERN_DIVIDE_Y	(2)															// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TITLE_ANIM_PATTERN_NUM		(TITLE_ANIM_PATTERN_DIVIDE_X*TITLE_ANIM_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TITLE_ANIM_TIME				(6)															// �A�j���[�V�����̐؂�ւ��J�E���g

#define	TITLE_LOGO_TEXTURE			("data/TEXTURE/titleLogo.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_LOGO_SIZE_X			(850/2)											// �e�N�X�`���̕�
#define	TITLE_LOGO_SIZE_Y			(270/2)											// �e�N�X�`���̍���
#define TITLE_LOGO_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,300/2.0f,0.0f)	// �^�C�g���㕔�̈ʒu

#define	TITLE_CPY_TEXTURE			("data/TEXTURE/�R�s�[���C�g.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_CPY_SIZE_X			(250/2)											// �e�N�X�`���̕�
#define	TITLE_CPY_SIZE_Y			(40/2)											// �e�N�X�`���̍���
#define TITLE_CPY_POS				D3DXVECTOR3(150.0f,660.0f,0.0f)					// �R�s�[���C�g�̈ʒu

#define	TITLE_ANY_TEXTURE			("data/TEXTURE/�{�^���������Ă�.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_ANY_SIZE_X			(280/2)											// �e�N�X�`���̕�
#define	TITLE_ANY_SIZE_Y			(70/2)											// �e�N�X�`���̍���
#define TITLE_ANY_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.,0.0f)		// UI:"�{�^���������Ă�"

#define	TITLE_START_TEXTURE			("data/TEXTURE/�͂��߂�.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_START_SIZE_X			(280/2)											// �e�N�X�`���̕�
#define	TITLE_START_SIZE_Y			(70/2)											// �e�N�X�`���̍���
#define TITLE_START_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,450.,0.0f)		// UI:"�͂��߂�"

#define	TITLE_CREDIT_TEXTURE			("data/TEXTURE/�N���W�b�g.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_CREDIT_SIZE_X			(280/2)											// �^�C�g���̕�
#define	TITLE_CREDIT_SIZE_Y			(70/2)											// �^�C�g���̍���
#define TITLE_CREDIT_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,600.0f,0.0f)	// UI:"�N���W�b�g"

#define	TITLE_BOAD_TEXTURE			("data/TEXTURE/�N���W�b�gED.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_BOAD_SIZE_X			(1100/2)													// �e�N�X�`���̕�
#define	TITLE_BOAD_SIZE_Y			(650/2)														// �e�N�X�`���̍���
#define TITLE_BOAD_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)

#define	TITLE_ANY_EFFECT_SIZE_X		(290/2)											// �e�N�X�`���̕�
#define	TITLE_ANY_EFFECT_SIZE_Y		(80/2)											// �e�N�X�`���̍���

#define COLOR_WHITE					D3DCOLOR_RGBA(255, 255, 255, 255);				// UI�J�[�\���̐F:��
#define COLOR_YELLOW				D3DCOLOR_RGBA(255, 175, 0, 255);				// UI�J�[�\���̐F:���F
#define COLOR_GREEN					D3DCOLOR_RGBA(0, 255, 50, 255);					// UI�J�[�\���̐F:�ΐF


// �^�C�g���\���̐���}�N��
enum
{
	TITLE_BASE,						// �^�C�g������
	TITLE_ANIM_A,					// �A�j���[�V����:A
	TITLE_ANIM_D,					// �A�j���[�V����:D
	TITLE_LOGO,						// �^�C�g���㕔
	TITLE_CPY,						// �R�s�[���C�g

	TITLE_ANY,						// UI:"�{�^���������Ă�"
	TITLE_ANY_EFFECT,				// UI�G�t�F�N�g:"�{�^���������Ă�"
	TITLE_START,					// UI:"�͂��߂�"
	TITLE_START_EFFECT,				// UI�G�t�F�N�g:"�͂��߂�"
	TITLE_CREDIT,					// UI:"�N���W�b�g"
	TITLE_CREDIT_EFFECT,			// UI�G�t�F�N�g:"�N���W�b�g"

	TITLE_BOAD,						// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	TITLE_MAX,						// �^�C�g���\���̍ő吔
};

// UI�J�[�\������}�N��
enum
{
	TITLE_UI_START,					// UI:"�͂��߂�"
	TITLE_UI_CREDIT,				// UI:"�N���W�b�g"
	TITLE_UI_MAX,					// UI�J�[�\���ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	bool					use;						// �`�搧��ϐ� true:�g�p false:���g�p

	int						CountAnim;					// �A�j���[�V�����J�E���g�ϐ�
	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[�ϐ�

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}TITLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(int type);							// �����������֐�
void UninitTitle(void);									// �I�������֐�
void UpdateTitle(void);									// �X�V�����֐�
void DrawTitle(void);									// �`�揈���֐�
void SetTextureTitle(int no, int cntPattern);			// �e�N�X�`�����W�̐ݒ�

#endif
