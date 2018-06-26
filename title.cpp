//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/2/26
//
//=============================================================================

#include "title.h"					// �\���́��}�N���g�p�̈�
#include "main.h"					// �}�N���g�p�̈�
#include "input.h"					// �֐��g�p�̈�
#include "game.h"					// �֐����}�N���g�p�̈�
#include "fade.h"					// �֐��g�p�̈�
#include "input.h"					// ����
#include "fade.h"					// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(int no);					// ���_�쐬�֐�
void SetVertexTitleEffect(int no);					// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


TITLE					titleWk[TITLE_MAX];			// �^�C�g���\���̍ő吔�錾

bool					effectflag;					// �G�t�F�N�g�p����ϐ�
int						effect;						// �G�t�F�N�g�p�ϐ�

int						g_Alpha;					// ���e�X�g��臒l

int						serect;						// ��ʑJ�ڐ���ϐ�
int						titlecnt;					// �J�[�\������ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitTitle(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// �G�t�F�N�g�֌W�̏�����
	effectflag = true;				// true:�v���X���� false:�}�C�i�X����
	effect=INIT_EFFECT;				// �G�t�F�N�g�̃��l�̏�����

	// ��ʐ���ϐ��̏�����
	serect = 0;
	titlecnt = 0;

	// �A���t�@�e�X�g�̒l�̐ݒ�
	g_Alpha = ALPHA_TEST;


	// �\���̍ő吔����������
	for(int i = 0; i < TITLE_MAX;i++, title++)
	{

		// �A�j���[�V��������ϐ��̏�����
		title->PatternAnim = rand() % TITLE_ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		title->CountAnim = 0;									// �A�j���J�E���g��������

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			title->Texture = NULL;

			// �^�C�g���w�i
			if (i == TITLE_BASE)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_BASE_POS;		// �^�C�g���w�i�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_BASE_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �A�j���[�V����:A
			else if (i == TITLE_ANIM_A)
			{
				// �ʒu�̐ݒ�
				title->use = false;					// �g�p�ŏ�����
				title->pos = TITLE_BASE_POS_A;		// �A�j���[�V����:A�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_ANIM_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �A�j���[�V����:D
			else if (i == TITLE_ANIM_D)
			{
				// �ʒu�̐ݒ�
				title->use = false;					// �g�p�ŏ�����
				title->pos = TITLE_BASE_POS_D;		// �A�j���[�V����:D�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_ANIM_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �^�C�g�����S
			else if (i == TITLE_LOGO)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_LOGO_POS;		// �^�C�g�����S�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_LOGO_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �R�s�[���C�g
			else if (i == TITLE_CPY)
			{
				// �ʒu�̐ݒ�
				title->use = false;					// �g�p�ŏ�����
				title->pos = TITLE_CPY_POS;			// �R�s�[���C�g�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_CPY_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�{�^���������Ă�"
			// UI�G�t�F�N�g:"�{�^���������Ă�"
			else if ((i == TITLE_ANY)||(i == TITLE_ANY_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_ANY_POS;			// UI:"�{�^���������Ă�"��UI�G�t�F�N�g:"�{�^���������Ă�"�̈ʒu�̏�����


				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_ANY_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			else if ((i == TITLE_START) || (i == TITLE_START_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_START_POS;		// UI:"�͂��߂�"��UI�G�t�F�N�g:"�͂��߂�"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_START_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			else if ((i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_CREDIT_POS;		// UI:"�N���W�b�g"��UI�G�t�F�N�g:"�N���W�b�g"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_CREDIT_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
			else if (i == TITLE_BOAD)
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_BOAD_POS;		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_BOAD_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}
		}

		// �Q�[���X�V��
		else if (type == UPDATE)
		{
			// �ЂƂ܂��g�p�ŏ�����
			title->use = true;

			// �^�C�g���ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			// UI:"�N���W�b�g"
			// UI�G�t�F�N�g:"�N���W�b�g"
			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
			if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT)||(i == TITLE_BOAD))
			{
				title->use = false;		// ���g�p
			}
		}

		// ���_���̍쐬
		MakeVertexTitle(i);
	}

	return S_OK;
}
//=============================================================================
// �I�������֐�
//=============================================================================
void UninitTitle(void)
{
	// �|�C���^�̏�����
	TITLE *title = &titleWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (title->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			title->Texture->Release();
			title->Texture = NULL;
		}
	}

}
//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateTitle(void)
{

	// �|�C���^�̏�����
	TITLE *title = &titleWk[0];

	// �G�t�F�N�g����
	// �v���X�t���O
	if (effectflag == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		effect += EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (effect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			effectflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (effectflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		effect -= EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (effect == ALPHA_BASE)
		{
			// �t���O���v���X��
			effectflag = true;
		}

	}

	// �A�j���[�V����
	// �\���̍ő吔�X�V����
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{
		// �A�j���[�V����:A���A�j���[�V����:D
		if ((i == TITLE_ANIM_A) || (i == TITLE_ANIM_D))
		{
			// ���t���[���C���N�������g
			title->CountAnim++;

			// �A�j���[�V�����؂�ւ�����
			if ((title->CountAnim % TITLE_ANIM_TIME) == 0)
			{
				// �p�^�[���̐؂�ւ�
				title->PatternAnim = (title->PatternAnim + 1) % TITLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureTitle(i, title->PatternAnim);
			}
		}

		// �G�t�F�N�g����
		SetVertexTitleEffect(i);
	}

	// �X�e�[�W�J�ڏ���
	// ����
	if (serect == FIRST)
	{

		// Enter�܂���START�{�^������������A�X�e�[�W��؂�ւ���
		if ((GetKeyboardTrigger(DIK_A))||(IsButtonTriggered(0, BUTTON_START)))
		{
			// �|�C���^�̏�����
			TITLE *title = &titleWk[TITLE_ANY];

			// UI�����̍X�V����
			for (int i = TITLE_ANY;i < TITLE_MAX;i++, title++)
			{

				// �ŏ��ɕ\��������̂��g�p
				if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT))
				{
					title->use = true;
				}

				// ����ȊO�𖢎g�p
				else
				{
					title->use = false;
				}

			}

			// �Z���N�gUI�̕\��
			serect = UPDATE;
		}
	}

	// �Z���N�gUI�̕\����
	else if(serect == UPDATE)
	{
		// �g�p����\���̂̃|�C���^�̏�����
		TITLE *titles = &titleWk[TITLE_START];						// UI:"�͂��߂�"
		TITLE *titleS = &titleWk[TITLE_START_EFFECT];				// UI�G�t�F�N�g:"�͂��߂�"
		TITLE *titlec = &titleWk[TITLE_CREDIT];						// UI:"�N���W�b�g"
		TITLE *titleC = &titleWk[TITLE_CREDIT_EFFECT];				// UI�G�t�F�N�g:"�N���W�b�g"

		// �Z���N�g���j���[�̕\����
		switch (titlecnt)
		{

		// UI:"�͂��߂�"�̏���
		case TITLE_UI_START:
		{

			// UI�G�t�F�N�g:"�͂��߂�"���g�p��
			titleS->use = true;

			// UI�G�t�F�N�g:"�N���W�b�g"�𖢎g�p��
			titleC->use = false;

			// UI:"�͂��߂�"�̐F�����F��
			titles->vertex[0].diffuse = COLOR_GREEN;
			titles->vertex[1].diffuse = COLOR_GREEN;
			titles->vertex[2].diffuse = COLOR_GREEN;
			titles->vertex[3].diffuse = COLOR_GREEN;

			// UI:"�N���W�b�g"�̐F�����ɖ߂�
			titlec->vertex[0].diffuse = COLOR_WHITE;
			titlec->vertex[1].diffuse = COLOR_WHITE;
			titlec->vertex[2].diffuse = COLOR_WHITE;
			titlec->vertex[3].diffuse = COLOR_WHITE;

			// Enter����������A�X�e�[�W��؂�ւ���
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// ��ʑJ��:�X�e�[�W�I��
				SetFade(FADE_OUT, SCENE_STAGE);

			}

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
			{

				// �J�[�\������Ɉړ�
				titlecnt--;
			}

			// S����������A�J�[�\���ړ�
			else if (GetKeyboardTrigger(DIK_S))
			{

				// �J�[�\�������Ɉړ�
				titlecnt++;
			}

			break;
		}

		// UI:"�N���W�b�g"�̏���
		case TITLE_UI_CREDIT:
		{

			// UI�G�t�F�N�g:"�N���W�b�g"���g�p��
			titleC->use = true;

			// UI�G�t�F�N�g:"�͂��߂�"�𖢎g�p��
			titleS->use = false;

			// UI:"�N���W�b�g"�̐F�����F��
			titlec->vertex[0].diffuse = COLOR_GREEN;
			titlec->vertex[1].diffuse = COLOR_GREEN;
			titlec->vertex[2].diffuse = COLOR_GREEN;
			titlec->vertex[3].diffuse = COLOR_GREEN;

			// UI:"�͂��߂�"�̐F�����ɖ߂�
			titles->vertex[0].diffuse = COLOR_WHITE;
			titles->vertex[1].diffuse = COLOR_WHITE;
			titles->vertex[2].diffuse = COLOR_WHITE;
			titles->vertex[3].diffuse = COLOR_WHITE;

			// Enter����������A�N���W�b�g��\��
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// �J�[�\������ϐ����N���W�b�g��
				serect = CREDIT;

			}

			// W����������A�J�[�\���ړ�
			if (GetKeyboardTrigger(DIK_W))
			{

				// �J�[�\������Ɉړ�
				titlecnt--;
			}

			// S����������A�J�[�\���ړ�
			else if(GetKeyboardTrigger(DIK_S))
			{

				// �J�[�\�������Ɉړ�
				titlecnt++;
			}

			break;
		}

		}

		// �J�[�\�����[�v�ړ�����
		// UI:"�͂��߂�"�Ł����͎�
		if (titlecnt < TITLE_UI_START)
		{
			// UI:"�N���W�b�g"�Ɉړ�
			titlecnt = TITLE_UI_MAX - 1;
		}

		// UI:"�N���W�b�g"�Ł����͎�
		else if (titlecnt > TITLE_UI_MAX - 1)
		{
			// UI:"�͂��߂�"�Ɉړ�
			titlecnt = TITLE_UI_START;
		}
	}

	// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	else if (serect == CREDIT)
	{

		// �g�p����\���̂̃|�C���^�̏����� UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
		TITLE *titleB = &titleWk[TITLE_BOAD];

		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)��\��
		titleB ->use= true;

		// Enter�܂��́~�{�^������������A�J�[�\���I���ɖ߂�
		if (GetKeyboardTrigger(DIK_RETURN))
		{

			titleB->use = false;			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)���\��
			serect = UPDATE;				// �O�̃J�[�\���I�������ɖ߂�
			titlecnt = TITLE_UI_START;		// �J�[�\���������ʒu�ɖ߂�
		}

	}


}
//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawTitle(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_Alpha);		 //�����F�ϐ����l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//����:�傫��������

	// �\���̍ő吔�I������
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// �e�N�X�`���g�p��
		if (title->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, title->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, title->vertex, sizeof(VERTEX_2D));
		}
	}

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	
	// �|�C���^�̏�����
	TITLE *title = &titleWk[no];

	// �^�C�g���w�i�Ȃ�
	if (no==TITLE_BASE)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �A�j���[�V����:A���A�j���[�V����:D
	else if ((no == TITLE_ANIM_A) || (no == TITLE_ANIM_D))
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANIM_SIZE_X, title->pos.y - TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANIM_SIZE_X, title->pos.y - TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANIM_SIZE_X, title->pos.y + TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANIM_SIZE_X, title->pos.y + TITLE_ANIM_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �^�C�g�����S
	else if (no == TITLE_LOGO)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �R�s�[���C�g
	else if (no == TITLE_CPY)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CPY_SIZE_X, title->pos.y - TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CPY_SIZE_X, title->pos.y - TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CPY_SIZE_X, title->pos.y + TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CPY_SIZE_X, title->pos.y + TITLE_CPY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI:"�{�^���������Ă�"
	else if (no == TITLE_ANY)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"�{�^���������Ă�"
	else if (no == TITLE_ANY_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"�͂��߂�"
	else if (no == TITLE_START)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UI�G�t�F�N�g:"�͂��߂�"
	else if (no == TITLE_START_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	}


	// UI:"�N���W�b�g"
	else if (no == TITLE_CREDIT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI�G�t�F�N�g:"�N���W�b�g"
	else if (no == TITLE_CREDIT_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	}

	// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	else if (no == TITLE_BOAD)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	title->vertex[0].rhw =
	title->vertex[1].rhw =
	title->vertex[2].rhw =
	title->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	title->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	title->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	title->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTitle(int no, int cntPattern)
{

	// �|�C���^�̏�����
	TITLE *title = &titleWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TITLE_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / TITLE_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / TITLE_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TITLE_ANIM_PATTERN_DIVIDE_Y;
	title->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	title->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	title->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	title->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexTitleEffect(int no)
{

	// �|�C���^�̏�����
	TITLE *title = &titleWk[no];

	// �ύX���ꂽ�G�t�F�N�g�̃��l�̐ݒ�
	// UI�G�t�F�N�g:"�{�^���������Ă�"
	 if (no == TITLE_ANY_EFFECT)
	{

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	 // UI�G�t�F�N�g:"�͂��߂�"
	 if (no == TITLE_START_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	 }

	 // UI�G�t�F�N�g:"�N���W�b�g"
	 if (no == TITLE_CREDIT_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	 }

}
