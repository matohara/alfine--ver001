//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/6/12
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _RESULT_H_
#define _RESULT_H_

// �}�N�������C�u�����g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define RESULT_EFFECT_SPEED				(2)		// �_�ő��x���x

#define	RESULT_BASE_TEXTURE				("data/TEXTURE/���l.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BASE_SIZE_X				(SCREEN_WIDTH/2.0f)											// �e�N�X�`���̕�
#define	RESULT_BASE_SIZE_Y				(SCREEN_HEIGHT/2.0f)										// �e�N�X�`���̍���
#define RESULT_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// ���l�̈ʒu

#define	RESULT_BOAD_TEXTURE				("data/TEXTURE/ResultLogo.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BOAD_SIZE_X				(900/2.0f)													// �e�N�X�`���̕�
#define	RESULT_BOAD_SIZE_Y				(506/2.0f)													// �e�N�X�`���̍���
#define RESULT_BOAD_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,281.0f,0.0f)					// ���U���g�{�[�h�̈ʒu

#define	RESULT_BLACK_TEXTURE			("data/TEXTURE/�����U���g.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BLACK_SIZE_X				(744/2.0f)													// �e�N�X�`���̕�
#define	RESULT_BLACK_SIZE_Y				(458/2.0f)													// �e�N�X�`���̍���
#define RESULT_BLACK_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,284.0f,0.0f)					// �����U���g�̈ʒu

#define	RESULT_SCORE_TEXTURE			("data/TEXTURE/���ʔ��\.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SCORE_SIZE_X				(270/2)														// �e�N�X�`���̕�
#define	RESULT_SCORE_SIZE_Y				(74/2)														// �e�N�X�`���̍���
#define RESULT_SCORE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,133.0f,0.0f)					// ���ʔ��\�̈ʒu

#define	RESULT_SUM_TEXTURE				("data/TEXTURE/���v.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SUM_SIZE_X				(82/2)														// �e�N�X�`���̕�
#define	RESULT_SUM_SIZE_Y				(52/2)														// �e�N�X�`���̍���
#define RESULT_SUM_POS					D3DXVECTOR3(395.0f,449.0f,0.0f)								// ���v�̈ʒu

#define	RESULT_ENEMY_TEXTURE			("data/TEXTURE/�|�����G�̐�.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_ENEMY_SIZE_X				(162/2)														// �e�N�X�`���̕�
#define	RESULT_ENEMY_SIZE_Y				(32/2)														// �e�N�X�`���̍���
#define RESULT_ENEMY_POS				D3DXVECTOR3(395.0f,234.0f,0.0f)								// �|�����G�̐��̈ʒu

#define	RESULT_BOSS_TEXTURE				("data/TEXTURE/�{�X���j.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BOSS_SIZE_X				(110/2)														// �e�N�X�`���̕�
#define	RESULT_BOSS_SIZE_Y				(32/2)														// �e�N�X�`���̍���
#define RESULT_BOSS_POS					D3DXVECTOR3(395.0f,296.5f,0.0f)								// �{�X���j�̈ʒu

#define	RESULT_TIME_TEXTURE				("data/TEXTURE/�c�莞��.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_TIME_SIZE_X				(110/2)														// �e�N�X�`���̕�
#define	RESULT_TIME_SIZE_Y				(32/2)														// �e�N�X�`���̍���
#define RESULT_TIME_POS					D3DXVECTOR3(395.0f,354.0f,0.0f)								// �c�莞�Ԃ̈ʒu

#define	RESULT_RANK_TEXTURE				("data/TEXTURE/�]��.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_RANK_SIZE_X				(172/2)														// �e�N�X�`���̕�
#define	RESULT_RANK_SIZE_Y				(140/2)														// �e�N�X�`���̍���
#define RESULT_RANK_POS					D3DXVECTOR3(803.0f,325.0f,0.0f)								// �]���̈ʒu

#define	RESULT_RANK_EFFECT_SIZE_X		(182/2)														// �e�N�X�`���̕�
#define	RESULT_RANK_EFFECT_SIZE_Y		(150/2)														// �e�N�X�`���̍���

#define RESULT_ANIM_PATTERN_DIVIDE_X	(4)															// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define RESULT_ANIM_PATTERN_DIVIDE_Y	(1)															// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define RESULT_ANIM_PATTERN_NUM			(RESULT_ANIM_PATTERN_DIVIDE_X*RESULT_ANIM_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define RESULT_ANIM_TIME				(6)															// �A�j���[�V�����̐؂�ւ��J�E���g

#define	RESULT_SAFU_TEXTURE				("data/TEXTURE/safu01.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SAFU_SIZE_X				(438/2)														// �e�N�X�`���̕�
#define	RESULT_SAFU_SIZE_Y				(920/2)														// �e�N�X�`���̍���
#define RESULT_SAFU_POS					D3DXVECTOR3(1116.0f,540.0f,0.0f)							// �T�t�̈ʒu

#define	RESULT_AIBISU_TEXTURE			("data/TEXTURE/�A�C�r�X�O�P.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_AIBISU_SIZE_X			(408/2)														// �e�N�X�`���̕�
#define	RESULT_AIBISU_SIZE_Y			(724/2)														// �e�N�X�`���̍���
#define RESULT_AIBISU_POS				D3DXVECTOR3(121.0f,539.0f,0.0f)								// �A�C�r�X�̈ʒu


#define	RESULT_BLACK_S_TEXTURE			("data/TEXTURE/�����j���[.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BLACK_S_SIZE_X			(310/2)														// �e�N�X�`���̕�
#define	RESULT_BLACK_S_SIZE_Y			(318/2)														// �e�N�X�`���̍���
#define RESULT_BLACK_S_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.0f,0.0f)					// �����j���[�̈ʒu

#define	RESULT_INIT_TEXTURE				("data/TEXTURE/���Ȃ���.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_INIT_SIZE_X				(280/2)														// �e�N�X�`���̕�
#define	RESULT_INIT_SIZE_Y				(70/2)														// �e�N�X�`���̍���
#define RESULT_INIT_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,430.,0.0f)					// ���Ȃ����̈ʒu

#define	RESULT_FINISH_TEXTURE			("data/TEXTURE/�����.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_FINISH_SIZE_X			(180/2)														// �e�N�X�`���̕�
#define	RESULT_FINISH_SIZE_Y			(70/2)														// �e�N�X�`���̍���
#define RESULT_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,570.0f,0.0f)					// �����̈ʒu

#define	RESULT_ANY_EFFECT_SIZE_X		(290/2)														// �e�N�X�`���̕�
#define	RESULT_ANY_EFFECT_SIZE_Y		(80/2)														// �e�N�X�`���̍���
#define	RESULT_FINISH_EFFECT_SIZE_X		(190/2)														// �e�N�X�`���̕�
#define	RESULT_FINISH_EFFECT_SIZE_Y		(80/2)														// �e�N�X�`���̍���


// �^�C�g���\���̐���}�N��
enum
{
	RESULT_BASE,							// ���l
	RESULT_BOAD,							// ���U���g�{�[�h
	RESULT_BLACK,							// �����U���g
	RESULT_SCORE,							// ���ʔ��\
	RESULT_SUM,								// ���v
	RESULT_ENEMY,							// �|�����G�̐�
	RESULT_BOSS,							// �{�X���j
	RESULT_TIME,							// �c�莞��
	RESULT_RANK,							// �]��
	RESULT_RANK_EFFECT,						// �G�t�F�N�g:�]��

	RESULT_SAFU,							// �T�t
	RESULT_AIBISU,							// �A�C�r�X

	RESULT_BLACK_S,							// �����j���[
	RESULT_INIT,							// UI:"���Ȃ���"
	RESULT_INIT_EFFECT,						// UI�G�t�F�N�g:"���Ȃ���"
	RESULT_FINISH,							// UI:"�����"
	RESULT_FINISH_EFFECT,					// UI�G�t�F�N�g:"�����"
	RESULT_MAX,								// �\���̍ő吔
};


// ���U���g�J�[�\������}�N��
enum
{
	RESULT_UI_INIT,					// UI:"���Ȃ���"
	RESULT_UI_FINISH,				// UI:"�����"
	RESULT_UI_MAX,					// UI�J�[�\���ő吔
};

//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	int						CountAnim;					// �A�j���[�V�����J�E���g�ϐ�
	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[�ϐ�

	bool					use;						// �`�搧��ϐ� true:�g�p false:���g�p

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}RESULT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);							// �����������֐�
void UninitResult(void);								// �I�������֐�
void UpdateResult(void);								// �X�V�����֐�
void DrawResult(void);									// �`�揈���֐�
void SetTextureResult(int no, int cntPattern);			// �e�N�X�`�����W�̐ݒ�

#endif
