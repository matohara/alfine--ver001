//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/6/12
//
//=============================================================================
#include "result.h"				// �\���́��}�N���g�p�̈�
#include "main.h"				// �}�N���g�p�̈�
#include "input.h"				// �֐��g�p�̈�
#include "game.h"				// �֐����}�N���g�p�̈�
#include "fade.h"				// �֐��g�p�̈�
#include "title.h"				// �}�N���g�p�̈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(int no);					// ���_�쐬�֐�
void SetVertexResultEffect(int no);					// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


RESULT resultWk[RESULT_MAX];						// �^�C�g���\���̍ő吔�錾

bool resultflag;									// �G�t�F�N�g�p����ϐ�
int resulteffect;									// �G�t�F�N�g�p�ϐ�

int resultserect;									// ��ʑJ�ڐ���ϐ�
int resultcnt;										// �J�[�\������ϐ�

//float sizex, sizey;								// �f�o�b�O�p�e�N�X�`���ړ������ϐ�


//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitResult(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// �G�t�F�N�g�֌W�̏�����
	resultflag = true;				// true:�v���X���� false:�}�C�i�X����
	resulteffect = INIT_EFFECT;		// �G�t�F�N�g�̃��l�̏�����

	// ��ʐ���ϐ��̏�����
	resultserect = 0;
	resultcnt = 0;

	// �f�o�b�O�p�e�N�X�`���ړ������ϐ��̏�����
	//sizex = RESULT_SAFU_SIZE_X;
	//sizey = RESULT_SAFU_SIZE_Y;

	// �\���̍ő吔����������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// �A�j���[�V��������ϐ��̏�����
		result->PatternAnim = rand() % RESULT_ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		result->CountAnim = 0;									// �A�j���J�E���g��������

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			result->Texture = NULL;

			// ���l
			if (i == RESULT_BASE)
			{
				// �ʒu�̐ݒ�
				result->use = true;					// �g�p�ŏ�����
				result->pos = RESULT_BASE_POS;		// ���l�̈ʒu

			}

			// ���U���g�{�[�h
			else if (i == RESULT_BOAD)
			{
				// �ʒu�̐ݒ�
				result->use = true;					// �g�p�ŏ�����
				result->pos = RESULT_BOAD_POS;		// ���U���g�{�[�h�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BOAD_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �����U���g
			else if (i == RESULT_BLACK)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_BLACK_POS;		// �����U���g�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BLACK_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// ���ʔ��\
			else if (i == RESULT_SCORE)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_SCORE_POS;		// ���ʔ��\�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_SCORE_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// ���v
			else if (i == RESULT_SUM)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_SUM_POS;		// ���v�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_SUM_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �|�����G�̐�
			else if (i == RESULT_ENEMY)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_ENEMY_POS;			// �|�����G�̐��̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_ENEMY_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �{�X���j
			else if (i == RESULT_BOSS)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_BOSS_POS;			// �{�X���j�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_BOSS_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �c�莞��
			else if (i == RESULT_TIME)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_TIME_POS;			// �c�莞�Ԃ̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_TIME_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �]��
			else if (i == RESULT_RANK)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �]���̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �G�t�F�N�g:�]��
			else if (i == RESULT_RANK_EFFECT)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �G�t�F�N�g:�]���̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}


			// �T�t
			else if (i == RESULT_SAFU)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_SAFU_POS;			// �T�t�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_SAFU_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �A�C�r�X
			else if (i == RESULT_AIBISU)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_AIBISU_POS;		// �A�C�r�X�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_AIBISU_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}


			// �����j���[
			else if (i == RESULT_BLACK_S)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_BLACK_S_POS;		// �����j���[�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_BLACK_S_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// UI:"���Ȃ���"
			// UI�G�t�F�N�g:"���Ȃ���"
			else if ((i == RESULT_INIT) || (i == RESULT_INIT_EFFECT))
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_INIT_POS;			// UI:"���Ȃ���" UI�G�t�F�N�g:"���Ȃ���"�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_INIT_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// UI:"�����"
			// UI�G�t�F�N�g:"�����"
			else if ((i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_FINISH_POS;		// UI:"�����" UI�G�t�F�N�g:"�����"�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_FINISH_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}
		}

		// �Q�[���X�V��
		else if (type == UPDATE)
		{
			result->use = true;							// �g�p�ŏ�����

			// ���j���[�ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			// �����j���[
			// UI:"���Ȃ���"
			// UI�G�t�F�N�g:"���Ȃ���"
			// UI:"�����"
			// UI�G�t�F�N�g:"�����"
			if ((i == RESULT_BLACK_S) || (i == RESULT_INIT) || (i == RESULT_INIT_EFFECT) || (i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				result->use = false;					// ���g�p�ŏ�����
			}
		}

		// ���_���̍쐬
		MakeVertexResult(i);
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitResult(void)
{
	// �|�C���^�̏�����
	RESULT *result = &resultWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (result->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			result->Texture->Release();
			result->Texture = NULL;
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateResult(void)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[0];

	// �G�t�F�N�g����
	if (resultflag == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		resulteffect += RESULT_EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (resulteffect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			resultflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (resultflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		resulteffect -= RESULT_EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (resulteffect == ALPHA_BASE)
		{
			// �t���O���v���X��
			resultflag = true;
		}

	}

	// �A�j���[�V����
	// �\���̍ő吔�X�V����
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// �f�o�b�O�p�ړ��g�又��
		//if (i == RESULT_SAFU)
		//		{
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				result->pos.x--;
		//			}
		//			// �E
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				result->pos.x++;
		//			}
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				result->pos.y--;
		//
		//			}
		//			// ��
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				result->pos.y++;
		//			}
		//
		//			// x�g��
		//			if (GetKeyboardPress(DIK_I))
		//			{
		//				sizex++;
		//			}
		//
		//			// x�k��
		//			else if (GetKeyboardPress(DIK_O))
		//			{
		//				sizex--;
		//			}
		//
		//			// Y�g��
		//			if (GetKeyboardPress(DIK_K))
		//			{
		//				sizey++;
		//
		//			}
		//			// Y�k��
		//			else if (GetKeyboardPress(DIK_L))
		//			{
		//				sizey--;
		//			}
		//
		//			// �f�o�b�N��
		//#ifdef _DEBUG
		//			// �f�o�b�N�\��
		//			PrintDebugProc("���W:X %f)\n", result->pos.x);
		//			PrintDebugProc("���W:Y %f)\n", result->pos.y);
		//			PrintDebugProc("�T�C�Y:x%f)\n", sizex);
		//			PrintDebugProc("�T�C�Y:y%f)\n", sizey);
		//#endif
		//		}


		// �A�j���[�V����
		// �G�t�F�N�g:�]��
		if ((i == RESULT_RANK_EFFECT))
		{

			// ���t���[���C���N�������g
			result->CountAnim++;

			// �A�j���[�V�����؂�ւ�����
			if ((result->CountAnim % RESULT_ANIM_TIME) == 0)
			{
				// �p�^�[���̐؂�ւ�
				result->PatternAnim = (result->PatternAnim + 1) % RESULT_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureResult(i, result->PatternAnim);
			}
		}

		// �G�t�F�N�g����
		SetVertexResultEffect(i);

	}

	// ���U���g�J�ڏ���
	// ����
	if (resultserect == FIRST)
	{

		// Enter��������A�X�e�[�W��؂�ւ���
		if ((GetKeyboardTrigger(DIK_A)) || (IsButtonTriggered(0, BUTTON_START)))
		{
			// �|�C���^�̏�����
			RESULT *result = &resultWk[RESULT_BLACK_S];

			// ���U���g�J�[�\�������̍X�V����
			for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
			{
				// �ŏ��ɕ\�����Ȃ����̂𖢎g�p
				if (i == RESULT_FINISH_EFFECT)
				{
					result->use = false;
				}

				// �ŏ��ɕ\��������̂��g�p
				else
				{
					result->use = true;
				}
			}

			// �Z���N�gUI�̕\��
			resultserect = UPDATE;
		}
	}

	// �Z���N�gUI�̕\����
	else if (resultserect == UPDATE)
	{

		// �g�p����\���̂̃|�C���^�̏�����
		RESULT *resultI = &resultWk[RESULT_INIT];			// UI:"���Ȃ���"
		RESULT *resultIe = &resultWk[RESULT_INIT_EFFECT];	// UI�G�t�F�N�g:"���Ȃ���"
		RESULT *resultF = &resultWk[RESULT_FINISH];			// UI:"�����"
		RESULT *resultFe = &resultWk[RESULT_FINISH_EFFECT];	// UI�G�t�F�N�g:"�����

		// �Z���N�g���j���[�̕\����
		switch (resultcnt)
		{

			// UI:"���Ȃ���"�̏���
		case RESULT_UI_INIT:
		{

			// UI�G�t�F�N�g:"���Ȃ���"�̏���
			resultIe->use = true;

			// UI�G�t�F�N�g:"�����"�𖢎g�p��
			resultFe->use = false;

			// UI:"���Ȃ���"�̐F�����F��
			resultI->vertex[0].diffuse = COLOR_YELLOW;
			resultI->vertex[1].diffuse = COLOR_YELLOW;
			resultI->vertex[2].diffuse = COLOR_YELLOW;
			resultI->vertex[3].diffuse = COLOR_YELLOW;

			// UI:"�����"�̐F�����ɖ߂�
			resultF->vertex[0].diffuse = COLOR_WHITE;
			resultF->vertex[1].diffuse = COLOR_WHITE;
			resultF->vertex[2].diffuse = COLOR_WHITE;
			resultF->vertex[3].diffuse = COLOR_WHITE;

			// Enter����������A�Q�[��������
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				UninitGame();					// �Q�[���̏I������
				InitGame();						// �Q�[���̍ď���������
				SetFade(FADE_OUT, SCENE_GAME);	// ��ʑJ��:�Q�[��
			}

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
			{
				// �J�[�\������Ɉړ�
				resultcnt--;
			}

			// S����������A�J�[�\���ړ�
			else if (GetKeyboardTrigger(DIK_S))
			{
				// �J�[�\�������Ɉړ�
				resultcnt++;
			}

			// �~�{�^�����������獕���U���g���\��
			if (GetKeyboardTrigger(DIK_Z))
			{

				// �|�C���^�̏�����
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// �����U���g�ȉ���S�Ĕ�\����
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// ���\��

				}

				// ����ɖ߂�
				resultserect = FIRST;
			}



			break;
		}

		// UI:"�����"�̏���
		case RESULT_UI_FINISH:
		{

			// UI�G�t�F�N�g:"�����"���g�p��
			resultFe->use = true;

			// UI�G�t�F�N�g:"���Ȃ���"�𖢎g�p��
			resultIe->use = false;

			// UI�G�t�F�N�g:"�����"�̐F�����F��
			resultF->vertex[0].diffuse = COLOR_YELLOW;
			resultF->vertex[1].diffuse = COLOR_YELLOW;
			resultF->vertex[2].diffuse = COLOR_YELLOW;
			resultF->vertex[3].diffuse = COLOR_YELLOW;

			// UI�G�t�F�N�g:"���Ȃ���"�̐F�����ɖ߂�
			resultI->vertex[0].diffuse = COLOR_WHITE;
			resultI->vertex[1].diffuse = COLOR_WHITE;
			resultI->vertex[2].diffuse = COLOR_WHITE;
			resultI->vertex[3].diffuse = COLOR_WHITE;


			// Enter����������A�X�e�[�W��؂�ւ���
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				UninitGame();					// �Q�[���̏I������
				InitGame();							// �Q�[���̍ď���������
				SetFade(FADE_OUT, SCENE_TITLE);		// ��ʑJ��:�^�C�g��

			}

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
				{
					// �J�[�\������Ɉړ�
					resultcnt--;
				}

			// S����������A�J�[�\���ړ�
			else if (GetKeyboardTrigger(DIK_S))
				{
					// �J�[�\�������Ɉړ�
					resultcnt++;
				}


			 // �~�{�^�����������獕���U���g���\��
			if (IsButtonTriggered(0, BUTTON_B))
			{

				// �|�C���^�̏�����
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// �����U���g�ȉ���S�Ĕ�\����
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// ���\��

				}

				// ����ɖ߂�
				resultserect = FIRST;
			}


			break;

	}

		}
	}

	// �J�[�\�����[�v�ړ�����
	// UI:"���Ȃ���"�Ł����͎�
	if (resultcnt < RESULT_UI_INIT)
	{
		// UI:"�����"�Ɉړ�
		resultcnt = RESULT_UI_MAX - 1;
	}

	// UI:"�����"�Ł����͎�
	if (resultcnt > RESULT_UI_MAX - 1)
	{
		// UI:"���Ȃ���"�Ɉړ�
		resultcnt = RESULT_UI_INIT;
	}

}
//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawResult(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	 // �\���̍ő吔�I������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{
		if (result->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, result->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, result->vertex, sizeof(VERTEX_2D));
		}
	}


}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexResult(int no)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[no];

	// ���l
	if (no == RESULT_BASE)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// ���U���g�{�[�h
	else if (no == RESULT_BOAD)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOAD_SIZE_X, result->pos.y - RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOAD_SIZE_X, result->pos.y - RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOAD_SIZE_X, result->pos.y + RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOAD_SIZE_X, result->pos.y + RESULT_BOAD_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �����U���g
	else if (no == RESULT_BLACK)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_SIZE_X, result->pos.y - RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_SIZE_X, result->pos.y - RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_SIZE_X, result->pos.y + RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_SIZE_X, result->pos.y + RESULT_BLACK_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// ���ʔ��\
	else if (no == RESULT_SCORE)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SCORE_SIZE_X, result->pos.y - RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SCORE_SIZE_X, result->pos.y - RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SCORE_SIZE_X, result->pos.y + RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SCORE_SIZE_X, result->pos.y + RESULT_SCORE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// ���v
	else if (no == RESULT_SUM)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SUM_SIZE_X, result->pos.y - RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SUM_SIZE_X, result->pos.y - RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SUM_SIZE_X, result->pos.y + RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SUM_SIZE_X, result->pos.y + RESULT_SUM_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �|�����G�̐�
	else if (no == RESULT_ENEMY)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ENEMY_SIZE_X, result->pos.y - RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ENEMY_SIZE_X, result->pos.y - RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ENEMY_SIZE_X, result->pos.y + RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ENEMY_SIZE_X, result->pos.y + RESULT_ENEMY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �{�X���j
	else if (no == RESULT_BOSS)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOSS_SIZE_X, result->pos.y - RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOSS_SIZE_X, result->pos.y - RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOSS_SIZE_X, result->pos.y + RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOSS_SIZE_X, result->pos.y + RESULT_BOSS_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �c�莞��
	else if (no == RESULT_TIME)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_TIME_SIZE_X, result->pos.y - RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_TIME_SIZE_X, result->pos.y - RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_TIME_SIZE_X, result->pos.y + RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_TIME_SIZE_X, result->pos.y + RESULT_TIME_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �]��
	else if (no == RESULT_RANK_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �G�t�F�N�g:�]��
	else if (no == RESULT_RANK_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �T�t
	else if (no == RESULT_SAFU)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SAFU_SIZE_X, result->pos.y - RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SAFU_SIZE_X, result->pos.y - RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SAFU_SIZE_X, result->pos.y + RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SAFU_SIZE_X, result->pos.y + RESULT_SAFU_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);

	}

	// �A�C�r�X
	else if (no == RESULT_AIBISU)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_AIBISU_SIZE_X, result->pos.y - RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_AIBISU_SIZE_X, result->pos.y - RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_AIBISU_SIZE_X, result->pos.y + RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_AIBISU_SIZE_X, result->pos.y + RESULT_AIBISU_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);

	}


	// �����j���[
	else if (no == RESULT_BLACK_S)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"���Ȃ���"
	else if (no == RESULT_INIT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"���Ȃ���"
	else if (no == RESULT_INIT_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}

	// UI:"�����"
	else if (no == RESULT_FINISH)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}

	// UI�G�t�F�N�g:"�����"
	else if (no == RESULT_FINISH_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	result->vertex[0].rhw =
	result->vertex[1].rhw =
	result->vertex[2].rhw =
	result->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	result->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	result->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	result->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	result->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureResult(int no, int cntPattern)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % RESULT_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / RESULT_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / RESULT_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / RESULT_ANIM_PATTERN_DIVIDE_Y;
	result->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	result->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	result->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	result->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexResultEffect(int no)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[no];


	// �f�o�b�O�p�e�N�X�`���X�V
	//// �{�^���������Ă�:�G�t�F�N�g
	//if (no == RESULT_SAFU)
	//{

	//	// ���_���W�̐ݒ�
	//	result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y + sizey, 0.0f);
	//	result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y + sizey, 0.0f);

	//}

	// �G�t�F�N�g:�]��
	if (no == RESULT_RANK_EFFECT)
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);

	}

	// UI�G�t�F�N�g:"���Ȃ���"
	else if (no == RESULT_INIT_EFFECT)
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);

	}

	// UI�G�t�F�N�g:"�����"
	else if (no == RESULT_FINISH_EFFECT)
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}

}
