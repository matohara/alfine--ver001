//=============================================================================
//
// ゲーム画面処理 [Game.h]
// Author : 
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FIRST		(0)						// 初起動時
#define UPDATE		(1)						// 更新中
#define CREDIT		(2)						// クレジット表示

/* Notes & Lane */
#define NL_CHECK_POS_X	(SCREEN_CENTER_X)
#define NL_CHECK_POS_Y	(64)
#define NL_SIZE_X		(480)
#define NL_SIZE_Y		(60)


/* GameFlag */
#define FLAG_GAME_PLAYING   (0x80000000)	// ゲーム中かどうか
#define FLAG_GAME_MAPSIDES  (0x00000001)	// 現在の表裏 (0:表, 1:裏)
#define FLAG_GAME_NEXTSIDES (0x00000002)	// 次になるべき表裏 (0:表, 1:裏)
#define FLAG_GAME_   (0x00000000)
#define FLAG_GAME_INIT      (FLAG_GAME_NEXTSIDES)

/* SoundVolume */
#define VOLUME_MAX (DSBVOLUME_MAX)
#define VOLUME_MIN (DSBVOLUME_MIN)

enum FLAGTYPE
{
	FT_CHANGE = -1,
	FT_OR,
	FT_DELETE,
	FT_UPDATE,
	FT_CHECK,
	FT_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
bool *GetMenu(void);

UINT SetGameFlag(UINT flg, FLAGTYPE type);

void CallGuideUI(D3DXVECTOR3 pos);
int CallNotesUI(void);

#endif
