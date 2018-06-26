//=============================================================================
//
// ゲーム画面処理 [Game.cpp]
// Author : 初 景新
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
#include "menu.h"				// 関数使用の為

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

bool menuflag;						// ポーズメニュー制御変数

LPDIRECTSOUNDBUFFER8 g_pBGM[2];						// BGM用バッファ

UICGuide GuideUI;
UICNotesLane NotesLane;
UICNotes UINotes[10];

UINT GameFlag = 0x0;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// 影の初期化
	//InitShadow();

	// 背景の初期化
	//InitBG();

	// エフェクトの初期化
	//InitEffect();

	// タイマーの初期化
//	InitTimer();
//	ResetTimer(30);

	// スコアの初期化
	//InitScore();

	// メニューの初期化
	InitMenu(FIRST);

	// ガイドUI
	GuideUI.Init();

	// ステージ
	InitStage();

	// ロード
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

	// GameFlagを初期化
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

	// UIノーツレーン
	NotesLane.Init();

	// ノーツUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		UINotes[iCnt].Init();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 影の終了処理
	//UninitShadow();

	// 背景の終了処理
	//UninitBG();

	// エフェトの終了処理
	//UninitEffect();

	// タイマーの終了処理
//	UninitTimer();

	// スコアの終了処理
	//UninitScore();

	// メニューの終了処理
	UninitMenu();

	// ガイドUI
	GuideUI.Uninit();

	// ステージ
	UninitStage();

	// サウンド終了処理
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

	// ノーツレーン
	NotesLane.Uninit();

	// ノーツUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		UINotes[iCnt].Uninit();
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{

	// Gを押したらポーズ
	if (GetKeyboardPress(DIK_G))
	{
		menuflag = true;				// ポーズのフラグを使用に
	}

	// ゲーム中
	if (menuflag == false)
	{

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// ゲームへ
			SetFade(FADE_OUT, SCENE_RESULT);
		}

		if (GetKeyboardTrigger(DIK_P))
		{
			GameFlag |= FLAG_GAME_PLAYING;

			// 再生
			PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
			PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
		}

		// カメラ更新
		UpdateCamera();

		if (GameFlag & FLAG_GAME_PLAYING)
		{
			// ステージ
			UpdateStage();

			// 影処理の更新
			//UpdateShadow();

			// エフェクト処理の更新
			//UpdateEffect();

			// タイマー処理の更新
			//UpdateTimer();

			// スコア処理の更新
			//UpdateScore();

			// ガイドUI
			if (GuideUI.Active)
			{
				GuideUI.Update();
			}

			// サウンド更新
			if (GameFlag & FLAG_GAME_MAPSIDES)
			{
				VolumeControl(g_pBGM[0], VOLUME_MIN);
				VolumeControl(g_pBGM[1], VOLUME_MAX);
				PrintDebugProcess("裏BGM演奏中\n");
			}
			else
			{
				VolumeControl(g_pBGM[0], VOLUME_MAX);
				VolumeControl(g_pBGM[1], VOLUME_MIN);
				PrintDebugProcess("表BGM演奏中\n");
			}
		}

		// ノーツレーン
		//	NotesLane.Update();

		// ノーツUI
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			if (UINotes[iCnt].Active)
			{
				UINotes[iCnt].Update();
				PrintDebugProcess("ノーツUI : No.%d 稼働中\n", iCnt);
			}
		}

	}

	// ポーズメニュー中
	else if (menuflag == true)
	{

		// サウンド終了処理
		StopSound(g_pBGM[0]);
		StopSound(g_pBGM[1]);

		// ポーズメニューの更新処理
		UpdateMenu();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// 影処理の描画
	//DrawShadow();

	// 背景の描画処理
	//DrawBG();


	// エフェクト処理の描画
	//DrawEffect();

	// タイマー処理の描画
//	DrawTimer();

	// スコア処理の描画
	//DrawScore();

	// ガイドUI
	if (GuideUI.Active)
	{
		GuideUI.Draw();
	}

	// ステージ
	DrawStage();

	// ノーツレーン
	NotesLane.Draw();

	// ノーツUI
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		if (UINotes[iCnt].Active)
		{
			UINotes[iCnt].Draw();
		}
	}

	// ポーズメニュー中
	if (menuflag == true)
	{
		// メニューの描画処理
		DrawMenu();
	}

}

//=============================================================================
// GameFlag取得
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
// GameFlag取得
//=============================================================================
void CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}

//=============================================================================
// セットノーツUI
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
// ポーズフラグ取得関数
//=============================================================================
bool *GetMenu(void)
{
	return(&menuflag);
}
