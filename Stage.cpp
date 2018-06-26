//=============================================================================
//
// ゲームステージ処理 [Stage.cpp]
// Author : 初 景新
//
//=============================================================================
#include "source/object/Player.h"

#include "Game.h"
#include "Stage.h"
#include "NotesUI.h"
#include "bg.h"

#include "fade.h"
#include "light.h"
#include "Camera.h"

#include "Field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NOTES_FILE  "data/STAGE/Datafile01.txt"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PlayerA TestPlayer;
FieldA TestField;
CNotes *Notes;

int GameCounter;
int NotesCounter;
int NotesCounter2;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage(void)
{
	Notes = NULL;
	GameCounter = 0;
	NotesCounter = 0;
	NotesCounter2 = 0;

	CNotes notes[] = {
		{  328 },
		{  408 },
		{  488 },
		{  564 },
		{  647 },
		{  688 },
		{  726 },
		{  805 },
		{  885 },
		{  965 },
		{ 1046 },
		{ 1125 },
		{ 1204 },
		{ 1284 },
		{ 1365 },
		{ 1445 },
		{ 1524 },
		{ 1607 },
		{ 1645 },
		{ 1684 },
		{ 1724 },
		{ 1766 },
		{ 1801 },
		{ 1844 },
		{ 1885 },
		{ 1924 },
		{ 2005 },
		{ 2084 },
		{ 2166 },
		{ 2245 },
		{ 2327 },
		{ 2404 },
		{ 2485 },
		{ 2566 },
		{ 2646 },
		{ 2724 },
		{ 2806 },
		{ 2886 },
		{ 2964 },
		{ 3044 },
		{ 3125 },
		{ 3206 },
		{ 3285 },
		{ 3364 },
		{ 3445 },
		{ 3525 },
		{ 3604 },
		{ 3684 },
		{ 3765 },
		{ 3844 },
		{ 3925 },
		{ 4006 },
		{ 4085 },
		{ 4166 },
		{ 4244 },
		{ 4326 },
		{ 4406 },
		{ 4484 },
		{ 4564 },
		{ 4644 },
		{ 4725 },
		{ 4805 },
		{ 4847 },
		{ 4886 } };
	const int notesSize = sizeof(notes) / sizeof(CNotes);
	Notes = new CNotes[notesSize];

	for (int iCnt = 0; iCnt < notesSize; iCnt++)
	{
		Notes[iCnt] = notes[iCnt];
	}

	// プレイヤー
	TestPlayer.Init();

	// 背景の初期化
	InitBG();

	// フィールド
	TestField.Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	delete[] Notes;
	Notes = NULL;

	// プレイヤー
	TestPlayer.Uninit();

	// 背景の終了処理
	//UninitBG();

	// フィールド
	TestField.Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
	/* ノーツ */
	GameCounter++;

	// 判定
	if (GameCounter == Notes[NotesCounter].Timing - 8)
	{
		CallGuideUI(TestPlayer.GetPosition(0.0f, 46.0f, 10.0f));
	}
	if (GameCounter == Notes[NotesCounter].Timing + 12)
	{
		if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) != SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);	// 現在の表裏判定を更新
		}
		SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHANGE);	// 次の表裏判定を更新
		NotesCounter++;
	}

	// UI
	if (GameCounter == Notes[NotesCounter2].Timing - 300)
	{
		CallNotesUI();
		NotesCounter2++;
		if (NotesCounter2 >= 64)
		{
			NotesCounter2 = 64;
		}
	}

	// プレイヤー
	TestPlayer.Update();

	// 背景の更新処理
	//UpdateBG();

	// フィールド
	TestField.Update();

	// デバッグ
	if (SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
	{
		PrintDebugProcess("現在は表です\n");
	}
	else
	{
		PrintDebugProcess("現在は裏です\n");
	}
	PrintDebugProcess("ゲームタイマー : %d\n", GameCounter);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	// プレイヤー
	TestPlayer.Draw();

	// 背景の描画処理
	DrawBG();

	// フィールド
	TestField.Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
}


