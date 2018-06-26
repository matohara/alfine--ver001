//=============================================================================
//
// セレクト選択画面処理 [select.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/6/12
//
//=============================================================================

#include "select.h"					// 構造体＆マクロ使用の為
#include "main.h"					// マクロ使用の為
#include "input.h"					// 関数使用の為
#include "game.h"					// 関数＆マクロ使用の為
#include "fade.h"					// 関数使用の為
#include "input.h"					// 同上
#include "fade.h"					// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSelect(int no);					// 頂点作成関数
void SetVertexSelectEffect(int no);					// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


SELECT					selectWk[SELECT_MAX];			// セレクト構造体最大数宣言

bool					selectflag;					// エフェクト用制御変数
int						selecteffect;				// エフェクト用変数

int						S_Alpha;					// αテストの閾値

int						selectserect;						// 画面遷移制御変数
int						selectcnt;					// カーソル制御変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitSelect(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SELECT *select = &selectWk[0];

	// エフェクト関係の初期化
	selectflag = true;				// true:プラスする false:マイナスする
	selecteffect=INIT_EFFECT;				// エフェクトのα値の初期化

	// 画面制御変数の初期化
	selectserect = 0;
	selectcnt = 0;

	// アルファテストの値の設定
	S_Alpha = ALPHA_TEST;


	// 構造体最大数初期化処理
	for(int i = 0; i < SELECT_MAX;i++, select++)
	{

		// アニメーション制御変数の初期化
		select->PatternAnim = rand() % SELECT_ANIM_PATTERN_NUM;	// アニメパターン番号をランダムで初期化
		select->CountAnim = 0;									// アニメカウントを初期化

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			select->Texture = NULL;

			// セレクト背景
			if (i == SELECT_BASE)
			{
				// 位置の設定
				select->use = true;					// 使用で初期化
				select->pos = SELECT_BASE_POS;		// セレクト背景の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					SELECT_BASE_TEXTURE,				// ファイルの名前
					&select->Texture);				// 読み込むメモリー
			}

			// アニメーション:A
			else if (i == SELECT_ANIM_A)
			{
				// 位置の設定
				select->use = false;					// 使用で初期化
				select->pos = SELECT_BASE_POS_A;		// アニメーション:Aの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					SELECT_ANIM_TEXTURE,				// ファイルの名前
					&select->Texture);				// 読み込むメモリー
			}

			// アニメーション:D
			else if (i == SELECT_ANIM_D)
			{
				// 位置の設定
				select->use = false;					// 使用で初期化
				select->pos = SELECT_BASE_POS_D;		// アニメーション:Dの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					SELECT_ANIM_TEXTURE,				// ファイルの名前
					&select->Texture);				// 読み込むメモリー
			}


			// UI:"オプション"
			// UIエフェクト:"オプション"
			else if ((i == SELECT_OPTION)||(i == SELECT_OPTION_EFFECT))
			{
				// 位置の設定
				select->use = true;						// 使用で初期化
				select->pos = SELECT_OPTION_POS;		// UI:"オプション"＆UIエフェクト:"オプション"の位置の初期化


				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					SELECT_OPTION_TEXTURE,			// ファイルの名前
					&select->Texture);				// 読み込むメモリー
			}

			// UI:"チュートリアル"
			// UIエフェクト:"チュートリアル"
			else if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT)
				|| (i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_A_EFFECT)
				|| (i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_B_EFFECT)
				|| (i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_C_EFFECT)
				|| (i == SELECT_TUTORIAL_D) || (i == SELECT_TUTORIAL_D_EFFECT))
			{
				// 位置の設定
				select->use = false;					// 未使用で初期化

				if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_POS;		// UI:"チュートリアル"＆UIエフェクト:"チュートリアル"の位置の初期化
				}

				else if ((i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_A_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_A_POS;		// UI:"チュートリアル"＆UIエフェクト:"チュートリアル"の位置の初期化
				}

				else if ((i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_B_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_B_POS;		// UI:"チュートリアル"＆UIエフェクト:"チュートリアル"の位置の初期化
				}

				else if ((i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_C_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_C_POS;		// UI:"チュートリアル"＆UIエフェクト:"チュートリアル"の位置の初期化
				}

				else if((i == SELECT_TUTORIAL_D) || (i == SELECT_TUTORIAL_D_EFFECT))
				{
					select->pos = SELECT_TUTORIAL_D_POS;		// UI:"チュートリアル"＆UIエフェクト:"チュートリアル"の位置の初期化
				}


				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					SELECT_TUTORIAL_TEXTURE,			// ファイルの名前
					&select->Texture);				// 読み込むメモリー
			}

		}

		// ゲーム更新時
		else if (type == UPDATE)
		{
			// ひとまず使用で初期化
			select->use = true;

			// セレクトで最初表示するもの以外は未使用で初期化
			// UI:"チュートリアル"
			// UIエフェクト:"チュートリアル"
			// UI:"クレジット"
			// UIエフェクト:"クレジット"
			// UI:"クレジットED"(クレジットテクスチャ)
			if ((i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT))
			{
				select->use = false;		// 未使用
			}
		}

		// 頂点情報の作成
		MakeVertexSelect(i);
	}

	return S_OK;
}
//=============================================================================
// 終了処理関数
//=============================================================================
void UninitSelect(void)
{
	// ポインタの初期化
	SELECT *select = &selectWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{

		// テクスチャの開放出来ていなかったら
		if (select->Texture != NULL)
		{

			// テクスチャの開放
			select->Texture->Release();
			select->Texture = NULL;
		}
	}

}
//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateSelect(void)
{

	// ポインタの初期化
	SELECT *select = &selectWk[0];

	// エフェクト処理
	// プラスフラグ
	if (selectflag == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		selecteffect += EFFECT_SPEED;

		// エフェクトα値が最大
		if (selecteffect == ALPHA_MAX)
		{
			// フラグをマイナスに
			selectflag = false;
		}
	}

	// マイナスフラグ
	else if (selectflag == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		selecteffect -= EFFECT_SPEED;

		// エフェクトα値が最小
		if (selecteffect == ALPHA_BASE)
		{
			// フラグをプラスに
			selectflag = true;
		}

	}

	// アニメーション
	// 構造体最大数更新処理
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{
		// アニメーション:A＆アニメーション:D
		if ((i == SELECT_ANIM_A) || (i == SELECT_ANIM_D))
		{
			// 毎フレームインクリメント
			select->CountAnim++;

			// アニメーション切り替え処理
			if ((select->CountAnim % SELECT_ANIM_TIME) == 0)
			{
				// パターンの切り替え
				select->PatternAnim = (select->PatternAnim + 1) % SELECT_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureSelect(i, select->PatternAnim);
			}
		}

		// エフェクト処理
		SetVertexSelectEffect(i);
	}

	// セレクト遷移処理
	// 初回
	if (selectserect == FIRST)
	{

		// ポインタの初期化
		SELECT *select = &selectWk[SELECT_OPTION];

		// UI部分の更新処理
		for (int i = SELECT_OPTION;i < SELECT_MAX;i++, select++)
		{

			// 最初に表示するものを使用
			if ((i == SELECT_OPTION) || (i == SELECT_OPTION_EFFECT) || (i == SELECT_TUTORIAL) || (i == SELECT_TUTORIAL_EFFECT) || (i == SELECT_TUTORIAL_A) || (i == SELECT_TUTORIAL_B) || (i == SELECT_TUTORIAL_C) || (i == SELECT_TUTORIAL_D))
			{
				select->use = true;
			}

			// それ以外を未使用
			else
			{
				select->use = false;
			}

		}

		// セレクトUIの表示
		selectserect = UPDATE;
	}

	// セレクトUIの表示中
	else if(selectserect == UPDATE)
	{
		// 使用する構造体のポインタの初期化
		SELECT *selects = &selectWk[SELECT_TUTORIAL];						// UI:"チュートリアル"
		SELECT *selectS = &selectWk[SELECT_TUTORIAL_EFFECT];				// UIエフェクト:"チュートリアル"

		// セレクトメニューの表示中
		switch (selectcnt)
		{

		// UI:"チュートリアル"の処理
		case SELECT_UI_TUTORIAL:
		{

			// UIエフェクト:"チュートリアル"を使用に
			selectS->use = true;


			// UI:"チュートリアル"の色を黄色に
			selects->vertex[0].diffuse = COLOR_YELLOW;
			selects->vertex[1].diffuse = COLOR_YELLOW;
			selects->vertex[2].diffuse = COLOR_YELLOW;
			selects->vertex[3].diffuse = COLOR_YELLOW;

			// Enterを押したら、セレクトを切り替える
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// 画面遷移:セレクト選択
				SetFade(FADE_OUT, SCENE_GAME);

			}

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
			{

				// カーソルを上に移動
				selectcnt--;
			}

			// Sを押したら、カーソル移動
			else if (GetKeyboardTrigger(DIK_S))
			{

				// カーソルを下に移動
				selectcnt++;
			}

			break;
		}

		// UI:"クレジット"の処理
		case SELECT_UI_CREDIT:
		{


			// UIエフェクト:"チュートリアル"を未使用に
			selectS->use = false;

			// UI:"チュートリアル"の色を元に戻す
			selects->vertex[0].diffuse = COLOR_WHITE;
			selects->vertex[1].diffuse = COLOR_WHITE;
			selects->vertex[2].diffuse = COLOR_WHITE;
			selects->vertex[3].diffuse = COLOR_WHITE;

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
			{

				// カーソルを上に移動
				selectcnt--;
			}

			// Sを押したら、カーソル移動
			else if(GetKeyboardTrigger(DIK_S))
			{

				// カーソルを下に移動
				selectcnt++;
			}

			break;
		}

		}

		// カーソルループ移動処理
		// UI:"チュートリアル"で↑入力時
		if (selectcnt < SELECT_UI_TUTORIAL)
		{
			// UI:"クレジット"に移動
			selectcnt = SELECT_UI_MAX - 1;
		}

		// UI:"クレジット"で↓入力時
		else if (selectcnt > SELECT_UI_MAX - 1)
		{
			// UI:"チュートリアル"に移動
			selectcnt = SELECT_UI_TUTORIAL;
		}
	}



}
//=============================================================================
// 描画処理関数
//=============================================================================
void DrawSelect(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SELECT *select = &selectWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, S_Alpha);		 //条件：変数数値
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//条件:大きかったら

	// 構造体最大数終了処理
	for (int i = 0; i < SELECT_MAX;i++, select++)
	{

		// テクスチャ使用中
		if (select->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, select->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, select->vertex, sizeof(VERTEX_2D));
		}
	}

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexSelect(int no)
{
	
	// ポインタの初期化
	SELECT *select = &selectWk[no];

	// セレクト背景なら
	if (no==SELECT_BASE)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_BASE_SIZE_X, select->pos.y - SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_BASE_SIZE_X, select->pos.y - SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_BASE_SIZE_X, select->pos.y + SELECT_BASE_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_BASE_SIZE_X, select->pos.y + SELECT_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// アニメーション:A＆アニメーション:D
	else if ((no == SELECT_ANIM_A) || (no == SELECT_ANIM_D))
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANIM_SIZE_X, select->pos.y - SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANIM_SIZE_X, select->pos.y - SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANIM_SIZE_X, select->pos.y + SELECT_ANIM_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANIM_SIZE_X, select->pos.y + SELECT_ANIM_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"オプション"
	else if (no == SELECT_OPTION)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_SIZE_X, select->pos.y - SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_SIZE_X, select->pos.y - SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_SIZE_X, select->pos.y + SELECT_OPTION_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_SIZE_X, select->pos.y + SELECT_OPTION_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"オプション"
	else if (no == SELECT_OPTION_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_EFFECT_SIZE_X, select->pos.y - SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_EFFECT_SIZE_X, select->pos.y - SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_OPTION_EFFECT_SIZE_X, select->pos.y + SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_OPTION_EFFECT_SIZE_X, select->pos.y + SELECT_OPTION_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	// UI:"チュートリアル"
	else if (no == SELECT_TUTORIAL)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_SIZE_X, select->pos.y - SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_SIZE_X, select->pos.y - SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_SIZE_X, select->pos.y + SELECT_TUTORIAL_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_SIZE_X, select->pos.y + SELECT_TUTORIAL_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UIエフェクト:"チュートリアル"
	else if (no == SELECT_TUTORIAL_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}

	// UI:"チュートリアルA"
	else if (no == SELECT_TUTORIAL_A)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}


	// UIエフェクト:"チュートリアルA"
	else if (no == SELECT_TUTORIAL_A_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	// UI:"チュートリアルB"
	else if (no == SELECT_TUTORIAL_B)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}

	// UIエフェクト:"チュートリアルB"
	else if (no == SELECT_TUTORIAL_B_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_C_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}


	// UI:"チュートリアルC"
	else if (no == SELECT_TUTORIAL_C)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y - SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_C_SIZE_X, select->pos.y + SELECT_TUTORIAL_C_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}


	// UIエフェクト:"チュートリアルC"
	else if (no == SELECT_TUTORIAL_C_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_C_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}

	// UI:"チュートリアルD"
	else if (no == SELECT_TUTORIAL_D)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y - SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_TUTORIAL_B_SIZE_X, select->pos.y + SELECT_TUTORIAL_B_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

	}



	// UIエフェクト:"チュートリアルD"
	else if (no == SELECT_TUTORIAL_D_EFFECT)
	{
		// 頂点座標の設定
		select->vertex[0].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[1].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y - SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[2].vtx = D3DXVECTOR3(select->pos.x - SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);
		select->vertex[3].vtx = D3DXVECTOR3(select->pos.x + SELECT_ANY_B_EFFECT_SIZE_X, select->pos.y + SELECT_ANY_B_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	}


	// テクスチャのパースペクティブコレクト用
	select->vertex[0].rhw =
	select->vertex[1].rhw =
	select->vertex[2].rhw =
	select->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	select->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	select->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	select->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	select->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureSelect(int no, int cntPattern)
{

	// ポインタの初期化
	SELECT *select = &selectWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % SELECT_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / SELECT_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / SELECT_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / SELECT_ANIM_PATTERN_DIVIDE_Y;
	select->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	select->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	select->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	select->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// エフェクト関数
//=============================================================================
void SetVertexSelectEffect(int no)
{

	// ポインタの初期化
	SELECT *select = &selectWk[no];

	// 変更されたエフェクトのα値の設定
	// UIエフェクト:"オプション"
	 if (no == SELECT_OPTION_EFFECT)
	{

		// 反射光の設定
		select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);
		select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, selecteffect);

	}

	 // UIエフェクト:"チュートリアル"
	 if (no == SELECT_TUTORIAL_EFFECT)
	 {

		 // 反射光の設定
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UIエフェクト:"チュートリアル"
	 if (no == SELECT_TUTORIAL_A_EFFECT)
	 {

		 // 反射光の設定
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UIエフェクト:"チュートリアル"
	 if (no == SELECT_TUTORIAL_B_EFFECT)
	 {

		 // 反射光の設定
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UIエフェクト:"チュートリアル"
	 if (no == SELECT_TUTORIAL_C_EFFECT)
	 {

		 // 反射光の設定
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }

	 // UIエフェクト:"チュートリアル"
	 if (no == SELECT_TUTORIAL_D_EFFECT)
	 {

		 // 反射光の設定
		 select->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);
		 select->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, selecteffect);

	 }



}
