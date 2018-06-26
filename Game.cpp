//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "source/object/Player.h"
#include "Field.h"

#include "Game.h"
#include "GuideUI.h"
#include "NotesUI.h"

#include "fade.h"
#include "light.h"
#include "Camera.h"
#include "menu.h"				// �֐��g�p�̈�

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

bool menuflag;						// �|�[�Y���j���[����ϐ�

LPDIRECTSOUNDBUFFER8 g_pBGM[2];						// BGM�p�o�b�t�@

UICGuide GuideUI;
UICNotesLane NotesLane;
UICNotes UINotes[10];

UINT GameFlag = 0x0;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �e�̏�����
	//InitShadow();

	// �w�i�̏�����
	//InitBG();

	// �G�t�F�N�g�̏�����
	//InitEffect();

	// �^�C�}�[�̏�����
//	InitTimer();
//	ResetTimer(30);

	// �X�R�A�̏�����
	//InitScore();

	// ���j���[�̏�����
	InitMenu(FIRST);

	// �K�C�hUI
	GuideUI.Init();

	// �X�e�[�W
	InitStage();

	// ���[�h
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

	// GameFlag��������
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

	// UI�m�[�c���[��
	NotesLane.Init();

	// �m�[�cUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		UINotes[iCnt].Init();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �e�̏I������
	//UninitShadow();

	// �w�i�̏I������
	//UninitBG();

	// �G�t�F�g�̏I������
	//UninitEffect();

	// �^�C�}�[�̏I������
//	UninitTimer();

	// �X�R�A�̏I������
	//UninitScore();

	// ���j���[�̏I������
	UninitMenu();

	// �K�C�hUI
	GuideUI.Uninit();

	// �X�e�[�W
	UninitStage();

	// �T�E���h�I������
	StopSound(g_pBGM[0]);
	StopSound(g_pBGM[1]);
	if (g_pBGM[0] != NULL)
	{
		g_pBGM[0]->Release();
		g_pBGM[0] = NULL;
	}
	if (g_pBGM[1] != NULL)
	{
		g_pBGM[1]->Release();
		g_pBGM[1] = NULL;
	}

	// �m�[�c���[��
	NotesLane.Uninit();

	// �m�[�cUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		UINotes[iCnt].Uninit();
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{

	// G����������|�[�Y
	if (GetKeyboardPress(DIK_G))
	{
		menuflag = true;				// �|�[�Y�̃t���O���g�p��
	}

	// �Q�[����
	if (menuflag == false)
	{

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// �Q�[����
			SetFade(FADE_OUT, SCENE_RESULT);
		}

		if (GetKeyboardTrigger(DIK_P))
		{
			GameFlag |= FLAG_GAME_PLAYING;

			// �Đ�
			PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
			PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
		}

		// �J�����X�V
		UpdateCamera();

		if (GameFlag & FLAG_GAME_PLAYING)
		{
			// �X�e�[�W
			UpdateStage();

			// �e�����̍X�V
			//UpdateShadow();

			// �G�t�F�N�g�����̍X�V
			//UpdateEffect();

			// �^�C�}�[�����̍X�V
			//UpdateTimer();

			// �X�R�A�����̍X�V
			//UpdateScore();

			// �K�C�hUI
			if (GuideUI.Active)
			{
				GuideUI.Update();
			}

			// �T�E���h�X�V
			if (GameFlag & FLAG_GAME_MAPSIDES)
			{
				VolumeControl(g_pBGM[0], VOLUME_MIN);
				VolumeControl(g_pBGM[1], VOLUME_MAX);
				PrintDebugProcess("��BGM���t��\n");
			}
			else
			{
				VolumeControl(g_pBGM[0], VOLUME_MAX);
				VolumeControl(g_pBGM[1], VOLUME_MIN);
				PrintDebugProcess("�\BGM���t��\n");
			}
		}

		// �m�[�c���[��
		//	NotesLane.Update();

		// �m�[�cUI
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			if (UINotes[iCnt].Active)
			{
				UINotes[iCnt].Update();
				PrintDebugProcess("�m�[�cUI : No.%d �ғ���\n", iCnt);
			}
		}

	}

	// �|�[�Y���j���[��
	else if (menuflag == true)
	{

		// �T�E���h�I������
		StopSound(g_pBGM[0]);
		StopSound(g_pBGM[1]);

		// �|�[�Y���j���[�̍X�V����
		UpdateMenu();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �e�����̕`��
	//DrawShadow();

	// �w�i�̕`�揈��
	//DrawBG();


	// �G�t�F�N�g�����̕`��
	//DrawEffect();

	// �^�C�}�[�����̕`��
//	DrawTimer();

	// �X�R�A�����̕`��
	//DrawScore();

	// �K�C�hUI
	if (GuideUI.Active)
	{
		GuideUI.Draw();
	}

	// �X�e�[�W
	DrawStage();

	// �m�[�c���[��
	NotesLane.Draw();

	// �m�[�cUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		if (UINotes[iCnt].Active)
		{
			UINotes[iCnt].Draw();
		}
	}

	// �|�[�Y���j���[��
	if (menuflag == true)
	{
		// ���j���[�̕`�揈��
		DrawMenu();
	}

}

//=============================================================================
// GameFlag�擾
//=============================================================================
UINT SetGameFlag(UINT flg, FLAGTYPE type)
{
	switch (type)
	{
	case FT_CHANGE:
		GameFlag ^= flg;
		break;
	case FT_OR:
		GameFlag |= flg;
		break;
	case FT_DELETE:
		GameFlag &= ~flg;
		break;
	case FT_UPDATE:
		GameFlag = flg;
		break;
	case FT_CHECK:
		return (GameFlag & flg) ? 1 : 0;
	}

	return GameFlag;
}

//=============================================================================
// GameFlag�擾
//=============================================================================
void CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}

//=============================================================================
// �Z�b�g�m�[�cUI
//=============================================================================
int CallNotesUI(void)
{
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		if (UINotes[iCnt].Active == false)
		{
			UINotes[iCnt].Active = true;
			UINotes[iCnt].ReSet();
			return iCnt;
		}
	}
}

//=============================================================================
// �|�[�Y�t���O�擾�֐�
//=============================================================================
bool *GetMenu(void)
{
	return(&menuflag);
}
