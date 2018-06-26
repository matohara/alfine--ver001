//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/6/12
//
//=============================================================================
#include "result.h"				// 構造体＆マクロ使用の為
#include "main.h"				// マクロ使用の為
#include "input.h"				// 関数使用の為
#include "game.h"				// 関数＆マクロ使用の為
#include "fade.h"				// 関数使用の為
#include "title.h"				// マクロ使用の為

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult(int no);					// 頂点作成関数
void SetVertexResultEffect(int no);					// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


RESULT resultWk[RESULT_MAX];						// タイトル構造体最大数宣言

bool resultflag;									// エフェクト用制御変数
int resulteffect;									// エフェクト用変数

int resultserect;									// 画面遷移制御変数
int resultcnt;										// カーソル制御変数

//float sizex, sizey;								// デバッグ用テクスチャ移動処理変数


//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitResult(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// エフェクト関係の初期化
	resultflag = true;				// true:プラスする false:マイナスする
	resulteffect = INIT_EFFECT;		// エフェクトのα値の初期化

	// 画面制御変数の初期化
	resultserect = 0;
	resultcnt = 0;

	// デバッグ用テクスチャ移動処理変数の初期化
	//sizex = RESULT_SAFU_SIZE_X;
	//sizey = RESULT_SAFU_SIZE_Y;

	// 構造体最大数初期化処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// アニメーション制御変数の初期化
		result->PatternAnim = rand() % RESULT_ANIM_PATTERN_NUM;	// アニメパターン番号をランダムで初期化
		result->CountAnim = 0;									// アニメカウントを初期化

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			result->Texture = NULL;

			// 砂浜
			if (i == RESULT_BASE)
			{
				// 位置の設定
				result->use = true;					// 使用で初期化
				result->pos = RESULT_BASE_POS;		// 砂浜の位置

			}

			// リザルトボード
			else if (i == RESULT_BOAD)
			{
				// 位置の設定
				result->use = true;					// 使用で初期化
				result->pos = RESULT_BOAD_POS;		// リザルトボードの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BOAD_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 黒板リザルト
			else if (i == RESULT_BLACK)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_BLACK_POS;		// 黒板リザルトの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BLACK_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 結果発表
			else if (i == RESULT_SCORE)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_SCORE_POS;		// 結果発表の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_SCORE_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 合計
			else if (i == RESULT_SUM)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_SUM_POS;		// 合計の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_SUM_TEXTURE,				// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 倒した敵の数
			else if (i == RESULT_ENEMY)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_ENEMY_POS;			// 倒した敵の数の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_ENEMY_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// ボス撃破
			else if (i == RESULT_BOSS)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_BOSS_POS;			// ボス撃破の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_BOSS_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// 残り時間
			else if (i == RESULT_TIME)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_TIME_POS;			// 残り時間の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_TIME_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// 評価
			else if (i == RESULT_RANK)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// 評価の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// エフェクト:評価
			else if (i == RESULT_RANK_EFFECT)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// エフェクト:評価の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}


			// サフ
			else if (i == RESULT_SAFU)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_SAFU_POS;			// サフの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_SAFU_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// アイビス
			else if (i == RESULT_AIBISU)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_AIBISU_POS;		// アイビスの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_AIBISU_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}


			// 黒板メニュー
			else if (i == RESULT_BLACK_S)
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_BLACK_S_POS;		// 黒板メニューの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_BLACK_S_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// UI:"やりなおす"
			// UIエフェクト:"やりなおす"
			else if ((i == RESULT_INIT) || (i == RESULT_INIT_EFFECT))
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_INIT_POS;			// UI:"やりなおす" UIエフェクト:"やりなおす"の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_INIT_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// UI:"おわる"
			// UIエフェクト:"おわる"
			else if ((i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_FINISH_POS;		// UI:"おわる" UIエフェクト:"おわる"の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_FINISH_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}
		}

		// ゲーム更新時
		else if (type == UPDATE)
		{
			result->use = true;							// 使用で初期化

			// メニューで最初表示するもの以外は未使用で初期化
			// 黒板メニュー
			// UI:"やりなおす"
			// UIエフェクト:"やりなおす"
			// UI:"おわる"
			// UIエフェクト:"おわる"
			if ((i == RESULT_BLACK_S) || (i == RESULT_INIT) || (i == RESULT_INIT_EFFECT) || (i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				result->use = false;					// 未使用で初期化
			}
		}

		// 頂点情報の作成
		MakeVertexResult(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitResult(void)
{
	// ポインタの初期化
	RESULT *result = &resultWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// テクスチャの開放出来ていなかったら
		if (result->Texture != NULL)
		{

			// テクスチャの開放
			result->Texture->Release();
			result->Texture = NULL;
		}
	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateResult(void)
{

	// ポインタの初期化
	RESULT *result = &resultWk[0];

	// エフェクト処理
	if (resultflag == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		resulteffect += RESULT_EFFECT_SPEED;

		// エフェクトα値が最大
		if (resulteffect == ALPHA_MAX)
		{
			// フラグをマイナスに
			resultflag = false;
		}
	}

	// マイナスフラグ
	else if (resultflag == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		resulteffect -= RESULT_EFFECT_SPEED;

		// エフェクトα値が最小
		if (resulteffect == ALPHA_BASE)
		{
			// フラグをプラスに
			resultflag = true;
		}

	}

	// アニメーション
	// 構造体最大数更新処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// デバッグ用移動拡大処理
		//if (i == RESULT_SAFU)
		//		{
		//
		//			// 左
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				result->pos.x--;
		//			}
		//			// 右
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				result->pos.x++;
		//			}
		//
		//			// 上
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				result->pos.y--;
		//
		//			}
		//			// 下
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				result->pos.y++;
		//			}
		//
		//			// x拡大
		//			if (GetKeyboardPress(DIK_I))
		//			{
		//				sizex++;
		//			}
		//
		//			// x縮小
		//			else if (GetKeyboardPress(DIK_O))
		//			{
		//				sizex--;
		//			}
		//
		//			// Y拡大
		//			if (GetKeyboardPress(DIK_K))
		//			{
		//				sizey++;
		//
		//			}
		//			// Y縮小
		//			else if (GetKeyboardPress(DIK_L))
		//			{
		//				sizey--;
		//			}
		//
		//			// デバック中
		//#ifdef _DEBUG
		//			// デバック表示
		//			PrintDebugProc("座標:X %f)\n", result->pos.x);
		//			PrintDebugProc("座標:Y %f)\n", result->pos.y);
		//			PrintDebugProc("サイズ:x%f)\n", sizex);
		//			PrintDebugProc("サイズ:y%f)\n", sizey);
		//#endif
		//		}


		// アニメーション
		// エフェクト:評価
		if ((i == RESULT_RANK_EFFECT))
		{

			// 毎フレームインクリメント
			result->CountAnim++;

			// アニメーション切り替え処理
			if ((result->CountAnim % RESULT_ANIM_TIME) == 0)
			{
				// パターンの切り替え
				result->PatternAnim = (result->PatternAnim + 1) % RESULT_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureResult(i, result->PatternAnim);
			}
		}

		// エフェクト処理
		SetVertexResultEffect(i);

	}

	// リザルト遷移処理
	// 初回
	if (resultserect == FIRST)
	{

		// Enter押したら、ステージを切り替える
		if ((GetKeyboardTrigger(DIK_A)) || (IsButtonTriggered(0, BUTTON_START)))
		{
			// ポインタの初期化
			RESULT *result = &resultWk[RESULT_BLACK_S];

			// リザルトカーソル部分の更新処理
			for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
			{
				// 最初に表示しないものを未使用
				if (i == RESULT_FINISH_EFFECT)
				{
					result->use = false;
				}

				// 最初に表示するものを使用
				else
				{
					result->use = true;
				}
			}

			// セレクトUIの表示
			resultserect = UPDATE;
		}
	}

	// セレクトUIの表示中
	else if (resultserect == UPDATE)
	{

		// 使用する構造体のポインタの初期化
		RESULT *resultI = &resultWk[RESULT_INIT];			// UI:"やりなおす"
		RESULT *resultIe = &resultWk[RESULT_INIT_EFFECT];	// UIエフェクト:"やりなおす"
		RESULT *resultF = &resultWk[RESULT_FINISH];			// UI:"おわる"
		RESULT *resultFe = &resultWk[RESULT_FINISH_EFFECT];	// UIエフェクト:"おわる

		// セレクトメニューの表示中
		switch (resultcnt)
		{

			// UI:"やりなおす"の処理
		case RESULT_UI_INIT:
		{

			// UIエフェクト:"やりなおす"の処理
			resultIe->use = true;

			// UIエフェクト:"おわる"を未使用に
			resultFe->use = false;

			// UI:"やりなおす"の色を黄色に
			resultI->vertex[0].diffuse = COLOR_YELLOW;
			resultI->vertex[1].diffuse = COLOR_YELLOW;
			resultI->vertex[2].diffuse = COLOR_YELLOW;
			resultI->vertex[3].diffuse = COLOR_YELLOW;

			// UI:"おわる"の色を元に戻す
			resultF->vertex[0].diffuse = COLOR_WHITE;
			resultF->vertex[1].diffuse = COLOR_WHITE;
			resultF->vertex[2].diffuse = COLOR_WHITE;
			resultF->vertex[3].diffuse = COLOR_WHITE;

			// Enterを押したら、ゲーム初期化
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				UninitGame();					// ゲームの終了処理
				InitGame();						// ゲームの再初期化処理
				SetFade(FADE_OUT, SCENE_GAME);	// 画面遷移:ゲーム
			}

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
			{
				// カーソルを上に移動
				resultcnt--;
			}

			// Sを押したら、カーソル移動
			else if (GetKeyboardTrigger(DIK_S))
			{
				// カーソルを下に移動
				resultcnt++;
			}

			// ×ボタンを押したら黒板リザルトを非表示
			if (GetKeyboardTrigger(DIK_Z))
			{

				// ポインタの初期化
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// 黒板リザルト以下を全て非表示に
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// 日表示

				}

				// 初回に戻す
				resultserect = FIRST;
			}



			break;
		}

		// UI:"おわる"の処理
		case RESULT_UI_FINISH:
		{

			// UIエフェクト:"おわる"を使用に
			resultFe->use = true;

			// UIエフェクト:"やりなおす"を未使用に
			resultIe->use = false;

			// UIエフェクト:"おわる"の色を黄色に
			resultF->vertex[0].diffuse = COLOR_YELLOW;
			resultF->vertex[1].diffuse = COLOR_YELLOW;
			resultF->vertex[2].diffuse = COLOR_YELLOW;
			resultF->vertex[3].diffuse = COLOR_YELLOW;

			// UIエフェクト:"やりなおす"の色を元に戻す
			resultI->vertex[0].diffuse = COLOR_WHITE;
			resultI->vertex[1].diffuse = COLOR_WHITE;
			resultI->vertex[2].diffuse = COLOR_WHITE;
			resultI->vertex[3].diffuse = COLOR_WHITE;


			// Enterを押したら、ステージを切り替える
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				UninitGame();					// ゲームの終了処理
				InitGame();							// ゲームの再初期化処理
				SetFade(FADE_OUT, SCENE_TITLE);		// 画面遷移:タイトル

			}

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
				{
					// カーソルを上に移動
					resultcnt--;
				}

			// Sを押したら、カーソル移動
			else if (GetKeyboardTrigger(DIK_S))
				{
					// カーソルを下に移動
					resultcnt++;
				}


			 // ×ボタンを押したら黒板リザルトを非表示
			if (IsButtonTriggered(0, BUTTON_B))
			{

				// ポインタの初期化
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// 黒板リザルト以下を全て非表示に
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// 日表示

				}

				// 初回に戻す
				resultserect = FIRST;
			}


			break;

	}

		}
	}

	// カーソルループ移動処理
	// UI:"やりなおす"で↑入力時
	if (resultcnt < RESULT_UI_INIT)
	{
		// UI:"おわる"に移動
		resultcnt = RESULT_UI_MAX - 1;
	}

	// UI:"おわる"で↓入力時
	if (resultcnt > RESULT_UI_MAX - 1)
	{
		// UI:"やりなおす"に移動
		resultcnt = RESULT_UI_INIT;
	}

}
//=============================================================================
// 描画処理関数
//=============================================================================
void DrawResult(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	 // 構造体最大数終了処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{
		if (result->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, result->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, result->vertex, sizeof(VERTEX_2D));
		}
	}


}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexResult(int no)
{

	// ポインタの初期化
	RESULT *result = &resultWk[no];

	// 砂浜
	if (no == RESULT_BASE)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// リザルトボード
	else if (no == RESULT_BOAD)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOAD_SIZE_X, result->pos.y - RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOAD_SIZE_X, result->pos.y - RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOAD_SIZE_X, result->pos.y + RESULT_BOAD_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOAD_SIZE_X, result->pos.y + RESULT_BOAD_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// 黒板リザルト
	else if (no == RESULT_BLACK)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_SIZE_X, result->pos.y - RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_SIZE_X, result->pos.y - RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_SIZE_X, result->pos.y + RESULT_BLACK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_SIZE_X, result->pos.y + RESULT_BLACK_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 結果発表
	else if (no == RESULT_SCORE)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SCORE_SIZE_X, result->pos.y - RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SCORE_SIZE_X, result->pos.y - RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SCORE_SIZE_X, result->pos.y + RESULT_SCORE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SCORE_SIZE_X, result->pos.y + RESULT_SCORE_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 合計
	else if (no == RESULT_SUM)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SUM_SIZE_X, result->pos.y - RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SUM_SIZE_X, result->pos.y - RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SUM_SIZE_X, result->pos.y + RESULT_SUM_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SUM_SIZE_X, result->pos.y + RESULT_SUM_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 倒した敵の数
	else if (no == RESULT_ENEMY)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ENEMY_SIZE_X, result->pos.y - RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ENEMY_SIZE_X, result->pos.y - RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ENEMY_SIZE_X, result->pos.y + RESULT_ENEMY_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ENEMY_SIZE_X, result->pos.y + RESULT_ENEMY_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// ボス撃破
	else if (no == RESULT_BOSS)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOSS_SIZE_X, result->pos.y - RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOSS_SIZE_X, result->pos.y - RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BOSS_SIZE_X, result->pos.y + RESULT_BOSS_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BOSS_SIZE_X, result->pos.y + RESULT_BOSS_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 残り時間
	else if (no == RESULT_TIME)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_TIME_SIZE_X, result->pos.y - RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_TIME_SIZE_X, result->pos.y - RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_TIME_SIZE_X, result->pos.y + RESULT_TIME_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_TIME_SIZE_X, result->pos.y + RESULT_TIME_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// 評価
	else if (no == RESULT_RANK_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// エフェクト:評価
	else if (no == RESULT_RANK_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// サフ
	else if (no == RESULT_SAFU)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_SAFU_SIZE_X, result->pos.y - RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_SAFU_SIZE_X, result->pos.y - RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_SAFU_SIZE_X, result->pos.y + RESULT_SAFU_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_SAFU_SIZE_X, result->pos.y + RESULT_SAFU_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);

	}

	// アイビス
	else if (no == RESULT_AIBISU)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_AIBISU_SIZE_X, result->pos.y - RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_AIBISU_SIZE_X, result->pos.y - RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_AIBISU_SIZE_X, result->pos.y + RESULT_AIBISU_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_AIBISU_SIZE_X, result->pos.y + RESULT_AIBISU_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 230, 230, 255);

	}


	// 黒板メニュー
	else if (no == RESULT_BLACK_S)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"やりなおす"
	else if (no == RESULT_INIT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"やりなおす"
	else if (no == RESULT_INIT_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}

	// UI:"おわる"
	else if (no == RESULT_FINISH)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}

	// UIエフェクト:"おわる"
	else if (no == RESULT_FINISH_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}


	// テクスチャのパースペクティブコレクト用
	result->vertex[0].rhw =
	result->vertex[1].rhw =
	result->vertex[2].rhw =
	result->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	result->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	result->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	result->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	result->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureResult(int no, int cntPattern)
{

	// ポインタの初期化
	RESULT *result = &resultWk[no];

	// テクスチャ座標の設定
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
// エフェクト関数
//=============================================================================
void SetVertexResultEffect(int no)
{

	// ポインタの初期化
	RESULT *result = &resultWk[no];


	// デバッグ用テクスチャ更新
	//// ボタンをおしてね:エフェクト
	//if (no == RESULT_SAFU)
	//{

	//	// 頂点座標の設定
	//	result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y + sizey, 0.0f);
	//	result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y + sizey, 0.0f);

	//}

	// エフェクト:評価
	if (no == RESULT_RANK_EFFECT)
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);

	}

	// UIエフェクト:"やりなおす"
	else if (no == RESULT_INIT_EFFECT)
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffect);

	}

	// UIエフェクト:"おわる"
	else if (no == RESULT_FINISH_EFFECT)
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, resulteffect);

	}

}
