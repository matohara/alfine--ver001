//=============================================================================
//
// Object-AClass <object.cpp>
// Author : �� �i�V
//
//=============================================================================
#ifndef __CLASS_OBJECT_CLASS_INCLUDE_H__
#define __CLASS_OBJECT_CLASS_INCLUDE_H__


#include "../../main.h"
#include "../../Camera.h"

using namespace std;

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
/* �I�u�W�F�N�gA�N���X */
class class_ObjectA
{

protected:
	LPDIRECT3DTEXTURE9		Texture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXVECTOR3 Position;	// �ʒu���W
	D3DXVECTOR3 Rotation;	// ��]�p�x
	D3DXVECTOR2 Size;		// �|���S���T�C�Y
	float Scale;			// �T�C�Y�{��

	int TexPattern_X;		// �e�N�X�`���p�^�[���i���j
	int TexPattern_Y;		// �e�N�X�`���p�^�[���i�c�j
	int AnimeCount;			// �A�j���[�V�����J�E���g
	int AnimePattern;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	int ChangeAnimeTime;	// �A�j���[�V�����؂�ւ��Ҏ���

	virtual int MakeVertex(void);				// ���_�쐬
	virtual void SetVertex(void);				// ���_���W�ݒ�@���_�ʒu�̂�
	virtual void SetVertex(D3DXCOLOR color);	// ���_���W�ݒ�@���_�F����

public:
	class_ObjectA();
	~class_ObjectA();

	virtual void Draw(void);						// �`�揈��(�ʏ�)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�ʏ�)(�e�N�X�`���w��)
	virtual void DrawBillboard(void);						// �`�揈��(�r���{�[�h)
	virtual void DrawBillboard(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�r���{�[�h)(�e�N�X�`���w��)

	virtual void ReleaseBuffer(void);	// �o�b�t�@�n�J��
	virtual void LoadTexture(const char *texture);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);	//�e�N�X�`�����@�A�j���[�V�����Ȃ�

private:

};


/* �I�u�W�F�N�gG�N���X */
class class_ObjectG
{

protected:
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXVECTOR3 Position;	// �ʒu���W
	D3DXVECTOR3 Rotation;	// ��]�p�x
	D3DXVECTOR2 Size;		// �|���S���T�C�Y
	float Scale;			// �T�C�Y�{��

	virtual int MakeVertex(void);				// ���_�쐬
	virtual void SetVertex(void);				// ���_���W�ݒ�@���_�ʒu�̂�
	virtual void SetVertex(D3DXCOLOR color);	// ���_���W�ݒ�@���_�F����

public:
	class_ObjectG();
	~class_ObjectG();

	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��

	virtual void ReleaseBuffer(void);	// �o�b�t�@�n�J��

private:

};


/* �I�u�W�F�N�gG�N���X */
class class_ObjectU
{
	
protected:
	LPDIRECT3DTEXTURE9	Texture;			// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D			Vertex[NUM_VERTEX];	// ���_���

	virtual void MakeVertex(float sizeX, float sizeY, float posX, float posY);	// ���_�쐬
	virtual void SetVertex(float sizeX, float sizeY, float posX, float posY);	// ���_���W�ݒ�@���_�ʒu�̂�
	virtual void SetVertex(D3DXCOLOR color);			// ���_���W�ݒ�@���_�F����

public:
	class_ObjectU();
	~class_ObjectU();

	virtual void Draw(void);						// �`�揈��(�ʏ�)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�ʏ�)(�e�N�X�`���w��)

	virtual void ReleaseBuffer(void);	// �o�b�t�@�n�J��
	virtual void LoadTexture(const char *texture);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif