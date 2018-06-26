//=============================================================================
//
// �n�ʃN���X <Field.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _FIELD_CLASS_INCLUDE_H_
#define _FIELD_CLASS_INCLUDE_H_

#include "source/class/Aclass_object.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class FieldA : public class_ObjectA
{
	LPDIRECT3DTEXTURE9 *FieldTexture[2];
	int MapMax;

public:
	FieldA() {};
	~FieldA() {};

	void LoadTexture(void);
	void LoadStatus(float x, float y);

	void Init(void);
	void Update(void);
	void Draw(int sides, int map);
	void Uninit(void);

	void ReleaseBuffer(void);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



#endif
