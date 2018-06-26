//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "../../main.h"
#include "../../input.h"

#include "../../Game.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----�v���C���[���Z�b�g--------
void PlayerA::LoadPlayerStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, 1, 1, 1);

	Position = D3DXVECTOR3(0.0f, y, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----���[�g�ǂݍ���--------
void PlayerA::LoadRoute(void)
{
	// Output �󂯎��
	FILE *fp = fopen(DATAFILE_PLAYER_ROUTE, "r");	// �t�@�C�����J��

	// �t�@�C�����J�������`�F�b�N
	if (fp == NULL)
	{
		MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Open\"", MB_YESNO);
	}

	// �}�b�v�f�[�^�����
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#MAP_NUMBER"))
		{
			MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Read\"", MB_YESNO);
		}
	}

	fscanf(fp, "%d", &MapMax);
	PointMax = new int[MapMax];

	// �t�@�C������ǂݍ���
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		fscanf(fp, "%d", &PointMax[iCnt]);
	}

	// ���[�g�f�[�^�����
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#ROUTE_DATA"))
		{
			MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// �������m��
	Route = new PlayerRoute*[MapMax];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		Route[iCnt] = new PlayerRoute[PointMax[iCnt]];
	}

	char skep;
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		for (int iCnt2 = 0; iCnt2 < PointMax[iCnt]; iCnt2++)
		{
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.x);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.y);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.z);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%d", &Route[iCnt][iCnt2].Time);
			fscanf(fp, "%c", &skep);
		}
	}

	fclose(fp);	// �t�@�C������I��

}


//----����������--------
void PlayerA::Init(void)
{
	// ��񃊃Z�b�g
	{
		Texture = NULL;		// �e�N�X�`���ւ̃|�C���^
		VtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu���W
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�p�x
		Size = D3DXVECTOR2(0.0f, 0.0f);				// �|���S���T�C�Y
		Scale = 1.0f;								// �T�C�Y�{��
		TexPattern_X = 1;		// �e�N�X�`���p�^�[���i���j
		TexPattern_Y = 1;		// �e�N�X�`���p�^�[���i�c�j
		AnimeCount = 0;			// �A�j���[�V�����J�E���g
		AnimePattern = 0;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
		ChangeAnimeTime = 0;	// �A�j���[�V�����؂�ւ��Ҏ���

		Route = NULL;		// �ړ����[�g�ۑ��p�|�C���^�[
		MapNumber = 0;		// ���̃}�b�v�ԍ�
		NextPoint = 0;		// ���̈ړ���ԍ�
		RouteCounter = 0;	// �ړ��i�s�x
		PointMax = NULL;	// �ړ��|�C���g��
		MapMax = 0;			// �}�b�v�ő吔
	}

	// �e�N�X�`���ǂݍ���
	LoadTexture(TEXTURE_PLAYER);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(21.4f, 32.4f);

	// �ړ����[�g��ݒ�
	LoadRoute();
}

//----�X�V����--------
void PlayerA::Update(void)
{
	if (NextPoint == 0)
	{// ���_�͏u���ړ�
		Position = Route[MapNumber][NextPoint].Point;
		NextPoint++;
	}
	else
	{// �w��|�C���g�܂ňړ�
		// �ړ��x�N�g�������߂�
		Position += (Route[MapNumber][NextPoint].Point - Route[MapNumber][NextPoint - 1].Point) / (float)Route[MapNumber][NextPoint].Time;
		RouteCounter++;
		if (RouteCounter == Route[MapNumber][NextPoint].Time)
		{// �w��t���[�����ړ��I��
			RouteCounter = 0;
			NextPoint++;
		}

		// �S�|�C���g���ړ��㎟�̃}�b�v��
		if (NextPoint >= PointMax[MapNumber])
		{
			MapNumber++;
			NextPoint = 0;
		}

		// *�S�}�b�v�I����I��
		if (MapNumber >= MapMax)
		{
			MapNumber = MapMax - 1;
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
		}
	}

	PrintDebugProcess("�v���C���[�ʒu : �i%f, %f, %f�j\n", Position.x, Position.y, Position.z);
}

//----�`�揈��--------
void PlayerA::Draw(void)
{
	// �`��
	this->class_ObjectA::DrawBillboard();
}

//----�I������--------
void PlayerA::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	ReleaseBuffer();

	// ���[�g�f�[�^�������J��
	ReleaseRouteData();
}


//----�������J��--------
void PlayerA::ReleaseRouteData(void)
{
	for (int i = 0; i < MapMax; i++)
	{
		delete[] Route[i];
	}
	delete[] Route;
	Route = NULL;

	delete[] PointMax;
	PointMax = NULL;
}


