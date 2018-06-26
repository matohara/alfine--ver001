//=============================================================================
//
// �Z���N�g�I����ʏ��� [select.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/6/12
//
//=============================================================================

#include "select.h"					// �\���́��}�N���g�p�̈�
#include "main.h"					// �}�N���g�p�̈�
#include "input.h"					// �֐��g�p�̈�
#include "game.h"					// �֐����}�N���g�p�̈�
#include "fade.h"					// �֐��g�p�̈�
#include "input.h"					// ����
#include "fade.h"					// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSelect(int no);					// ���_�쐬�֐�
void SetVertexSelectEffect(int no);					// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


SELECT					selectWk[SELECT_MAX];			// �Z���N�g�\���̍ő吔�錾

bool					selectflag;					// �G�t�F�N�g�p����ϐ�
int						selecteffect;				// �G�t�F�N�g�p�ϐ�

int						S_Alpha;					// ���e�X�g��臒l

int						selectserect;						// ��ʑJ�ڐ���ϐ�
int						selectcnt;					// �J�[�\������ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitSelect(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SELECT *select = &selectWk[0];

	// �G�t�F�N�g�֌W�̏�����
	selectflag = true;				// true:�v���X���� false:�}�C�i�X����
	selecteffect=INIT_EFFECT;				// �G�t�F�N�g�̃��l�̏�����

	// ��ʐ���ϐ��̏�����
	selectserect = 0;
	selectcnt = 0;

	// �A���t�@�e�X�g�̒l�̐ݒ�
	S_Alpha = ALPHA_TEST;


	// �\���̍ő吔����������
	for(int i = 0; i < SELECT_MAX;i++, select++)
	{

		// �A�j���[�V��������ϐ��̏�����
		select->PatternAnim = rand() % SELECT_ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		select->CountAnim = 0;									// �A�j���J�E���g��������

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			select->Texture = NULL;

			// �Z���N�g�w�i
			if (i == SELECT_BASE)
			{
				// �ʒu�̐ݒ�
				select->use = true;					// �g�p�ŏ�����
				select->pos = SELECT_BASE_POS;		// �Z���N�g�w�i�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					SELECT_BASE_TEXTURE,				// �t�@�C���̖��O
					&select->Texture);				// �ǂݍ��ރ������[
			}

			// �A�j���[�V����:A
			else if (i == SELECT_ANIM_A)
			{
				// �ʒu�̐ݒ�
				select->use = false;					// �g�p�ŏ�����
				select->pos = SELECT_BASE_POS_A;		// �A�j���[�V����:A�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					SELECT_ANIM_TEXTURE,				// �t�@�C���̖��O
					&select->Texture);				// �ǂݍ��ރ������[
			}

			// �A�j���[�V����:D
			else if (i == SELECT_ANIM_D)
			{
				// �ʒu�̐ݒ�
				select->use = false;					// �g�p�ŏ�����
				select->pos = SELECT_BASE_POS_D;		// �A�j���[�V����:D�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					SELECT_ANIM_TEXTURE,				// �t�@�C���̖��O
					&select->Texture);				// �ǂݍ��ރ������[
			}


			// UI:"�I�v�V����"
			// UI�G�t�F�N�g:"�I�v�V����"
			else if ((i == SELECT_OPTION)||(i == SELECT_OPTION_EFFECT))
			{
				// �ʒu�̐ݒ�
				select->use = true;						// �g�p�ŏ�����
				select->pos = SELECT_OPTION_POS;		// UI:"�I�v�V����"��UI�G�t�F�N�g:"�I�v�V����"�̈ʒu�̏�����


				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					SELECT_OPTION_TEXTURE,			// �t�@�C���̖��O
					&select->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�`���[�g���A��"
			// UI�G�t�F�N�g:"�`���[�g���A��"
			else if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT)
				|| (i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_A_EFFECT)
				|| (i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_B_EFFECT)
				|| (i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_C_EFFECT)
				|| (i == SELECT_TUTORIAL_D) || (i == SELECT_TUTORIAL_D_EFFECT))
			{
				// �ʒu�̐ݒ�
				select->use = false;					// ���g�p�ŏ�����

				if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_POS;		// UI:"�`���[�g���A��"��UI�G�t�F�N�g:"�`���[�g���A��"�̈ʒu�̏�����
				}

				else if ((i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_A_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_A_POS;		// UI:"�`���[�g���A��"��UI�G�t�F�N�g:"�`���[�g���A��"�̈ʒu�̏�����
				}

				else if ((i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_B_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_B_POS;		// UI:"�`���[�g���A��"��UI�G�t�F�N�g:"�`���[�g���A��"�̈ʒu�̏�����
				}

				else if ((i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_C_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_C_POS;		// UI:"�`���[�g���A��"��UI�G�t�F�N�g:"�`���[�g���A��"�̈ʒu�̏�����
				}

				else if((i == SELECT_TUTORIAL_D) || (i == SELECT_TUTORIAL_D_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_D_POS;		// UI:"�`���[�g���A��"��UI�G�t�F�N�g:"�`���[�g���A��"�̈ʒu�̏�����
				}


				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					SELECT_TUTORIAL_TEXTURE,			// �t�@�C���̖��O
					&select->Texture);				// �ǂݍ��ރ������[
			}

		}

		// �Q�[���X�V��
		else if (type == UPDATE)
		{
			// �ЂƂ܂��g�p�ŏ�����
			select->use = true;

			// �Z���N�g�ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			// UI:"�`���[�g���A��"
			// UI�G�t�F�N�g:"�`���[�g���A��"
			// UI:"�N���W�b�g"
			// UI�G�t�F�N�g:"�N���W�b�g"
			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
			if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT))
			{
				select->use = false;		// ���g�p
			}
		}

		// ���_���̍쐬
		MakeVertexSelect(i);
	}

	return S_OK;
}
//=============================================================================
// �I�������֐�
//=============================================================================
void UninitSelect(void)
{
	// �|�C���^�̏�����
	SELECT *select = &selectWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (select->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			select->Texture->Release();
			select->Texture = NULL;
		}
	}

}
//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateSelect(void)
{

	// �|�C���^�̏�����
	SELECT *select = &selectWk[0];

	// �G�t�F�N�g����
	// �v���X�t���O
	if (selectflag == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		selecteffect += EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (selecteffect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			selectflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (selectflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		selecteffect -= EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (selecteffect == ALPHA_BASE)
		{
			// �t���O���v���X��
			selectflag = true;
		}

	}

	// �A�j���[�V����
	// �\���̍ő吔�X�V����
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{
		// �A�j���[�V����:A���A�j���[�V����:D
		if ((i == SELECT_ANIM_A) || (i == SELECT_ANIM_D))
		{
			// ���t���[���C���N�������g
			select->CountAnim++;

			// �A�j���[�V�����؂�ւ�����
			if ((select->CountAnim % SELECT_ANIM_TIME) == 0)
			{
				// �p�^�[���̐؂�ւ�
				select->PatternAnim = (select->PatternAnim + 1) % SELECT_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureSelect(i, select->PatternAnim);
			}
		}

		// �G�t�F�N�g����
		SetVertexSelectEffect(i);
	}

	// �Z���N�g�J�ڏ���
	// ����
	if (selectserect == FIRST)
	{

		// �|�C���^�̏�����
		SELECT *select = &selectWk[SELECT_OPTION];

		// UI�����̍X�V����
		for (int i = SELECT_OPTION;i < SELECT_MAX;i++, select++)
		{

			// �ŏ��ɕ\��������̂��g�p
			if ((i == SELECT_OPTION) || (i == SELECT_OPTION_EFFECT) || (i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT) || (i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_D))
			{
				select->use = true;
			}

			// ����ȊO�𖢎g�p
			else
			{
				select->use = false;
			}

		}

		// �Z���N�gUI�̕\��
		selectserect = UPDATE;
	}

	// �Z���N�gUI�̕\����
	else if(selectserect == UPDATE)
	{
		// �g�p����\���̂̃|�C���^�̏�����
		SELECT *selects = &selectWk[SELECT_TUTORIAL];						// UI:"�`���[�g���A��"
		SELECT *selectS = &selectWk[SELECT_TUTORIAL_EFFECT];				// UI�G�t�F�N�g:"�`���[�g���A��"

		// �Z���N�g���j���[�̕\����
		switch (selectcnt)
		{

		// UI:"�`���[�g���A��"�̏���
		case SELECT_UI_TUTORIAL:
		{

			// UI�G�t�F�N�g:"�`���[�g���A��"���g�p��
			selectS->use = true;


			// UI:"�`���[�g���A��"�̐F�����F��
			selects->vertex[0].diffuse = COLOR_YELLOW;
			selects->vertex[1].diffuse = COLOR_YELLOW;
			selects->vertex[2].diffuse = COLOR_YELLOW;
			selects->vertex[3].diffuse = COLOR_YELLOW;

			// Enter����������A�Z���N�g��؂�ւ���
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// ��ʑJ��:�Z���N�g�I��
				SetFade(FADE_OUT, SCENE_GAME);

			}

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
			{

				// �J�[�\������Ɉړ�
				selectcnt--;
			}

			// S����������A�J�[�\���ړ�
			else if (GetKeyboardTrigger(DIK_S))
			{

				// �J�[�\�������Ɉړ�
				selectcnt++;
			}

			break;
		}

		// UI:"�N���W�b�g"�̏���
		case SELECT_UI_CREDIT:
		{


			// UI�G�t�F�N�g:"�`���[�g���A��"�𖢎g�p��
			selectS->use = false;

			// UI:"�`���[�g���A��"�̐F�����ɖ߂�
			selects->vertex[0].diffuse = COLOR_WHITE;
			selects->vertex[1].diffuse = COLOR_WHITE;
			selects->vertex[2].diffuse = COLOR_WHITE;
			selects->vertex[3].diffuse = COLOR_WHITE;

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
			{

				// �J�[�\������Ɉړ�
				selectcnt--;
			}

			// S����������A�J�[�\���ړ�
			else if(GetKeyboardTrigger(DIK_S))
			{

				// �J�[�\�������Ɉړ�
				selectcnt++;
			}

			break;
		}

		}

		// �J�[�\�����[�v�ړ�����
		// UI:"�`���[�g���A��"�Ł����͎�
		if (selectcnt < SELECT_UI_TUTORIAL)
		{
			// UI:"�N���W�b�g"�Ɉړ�
			selectcnt = SELECT_UI_MAX - 1;
		}

		// UI:"�N���W�b�g"�Ł����͎�
		else if (selectcnt > SELECT_UI_MAX - 1)
		{
			// UI:"�`���[�g���A��"�Ɉړ�
			selectcnt = SELECT_UI_TUTORIAL;
		}
	}



}
//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawSelect(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SELECT *select = &selectWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, S_Alpha);		 //�����F�ϐ����l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//����:�傫��������

	// �\���̍ő吔�I������
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{

		// �e�N�X�`���g�p��
		if (select->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, select->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, select->vertex, sizeof(VERTEX_2D));
		}
	}

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexSelect(int no)
{
	
	// �|�C���^�̏�����
	SELECT *select = &selectWk[no];

	// �Z���N�g�w�i�Ȃ�
	if (no==SELECT_BASE)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_BASE_SIZE_X, select->pos.y - SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_BASE_SIZE_X, select->pos.y - SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_BASE_SIZE_X, select->pos.y + SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_BASE_SIZE_X, select->pos.y + SELECT_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �A�j���[�V����:A���A�j���[�V����:D
	else if ((no == SELECT_ANIM_A) || (no == SELECT_ANIM_D))
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANIM_SIZE_X, select->pos.y - SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANIM_SIZE_X, select->pos.y - SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANIM_SIZE_X, select->pos.y + SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANIM_SIZE_X, select->pos.y + SELECT_ANIM_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"�I�v�V����"
	else if (no == SELECT_OPTION)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_SIZE_X, select->pos.y - SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_SIZE_X, select->pos.y - SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_SIZE_X, select->pos.y + SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_SIZE_X, select->pos.y + SELECT_OPTION_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"�I�v�V����"
	else if (no == SELECT_OPTION_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_EFFECT_SIZE_X, select->pos.y - SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_EFFECT_SIZE_X, select->pos.y - SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_EFFECT_SIZE_X, select->pos.y + SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_EFFECT_SIZE_X, select->pos.y + SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	// UI:"�`���[�g���A��"
	else if (no == SELECT_TUTORIAL)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_SIZE_X, select->pos.y - SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_SIZE_X, select->pos.y - SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_SIZE_X, select->pos.y + SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_SIZE_X, select->pos.y + SELECT_TUTORIAL_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UI�G�t�F�N�g:"�`���[�g���A��"
	else if (no == SELECT_TUTORIAL_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}

	// UI:"�`���[�g���A��A"
	else if (no == SELECT_TUTORIAL_A)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}


	// UI�G�t�F�N�g:"�`���[�g���A��A"
	else if (no == SELECT_TUTORIAL_A_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	// UI:"�`���[�g���A��B"
	else if (no == SELECT_TUTORIAL_B)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}

	// UI�G�t�F�N�g:"�`���[�g���A��B"
	else if (no == SELECT_TUTORIAL_B_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}


	// UI:"�`���[�g���A��C"
	else if (no == SELECT_TUTORIAL_C)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}


	// UI�G�t�F�N�g:"�`���[�g���A��C"
	else if (no == SELECT_TUTORIAL_C_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}

	// UI:"�`���[�g���A��D"
	else if (no == SELECT_TUTORIAL_D)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}



	// UI�G�t�F�N�g:"�`���[�g���A��D"
	else if (no == SELECT_TUTORIAL_D_EFFECT)
	{
		// ���_���W�̐ݒ�
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	select->vertex[0].rhw =
	select->vertex[1].rhw =
	select->vertex[2].rhw =
	select->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	select->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	select->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	select->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	select->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSelect(int no, int cntPattern)
{

	// �|�C���^�̏�����
	SELECT *select = &selectWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % SELECT_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / SELECT_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / SELECT_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / SELECT_ANIM_PATTERN_DIVIDE_Y;
	select->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	select->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	select->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	select->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexSelectEffect(int no)
{

	// �|�C���^�̏�����
	SELECT *select = &selectWk[no];

	// �ύX���ꂽ�G�t�F�N�g�̃��l�̐ݒ�
	// UI�G�t�F�N�g:"�I�v�V����"
	 if (no == SELECT_OPTION_EFFECT)
	{

		// ���ˌ��̐ݒ�
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	 // UI�G�t�F�N�g:"�`���[�g���A��"
	 if (no == SELECT_TUTORIAL_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UI�G�t�F�N�g:"�`���[�g���A��"
	 if (no == SELECT_TUTORIAL_A_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UI�G�t�F�N�g:"�`���[�g���A��"
	 if (no == SELECT_TUTORIAL_B_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UI�G�t�F�N�g:"�`���[�g���A��"
	 if (no == SELECT_TUTORIAL_C_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UI�G�t�F�N�g:"�`���[�g���A��"
	 if (no == SELECT_TUTORIAL_D_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }



}
