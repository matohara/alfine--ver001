//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/2/26
//
//=============================================================================

#include "title.h"					// 構造体＆マクロ使用の為
#include "main.h"					// マクロ使用の為
#include "input.h"					// 関数使用の為
#include "game.h"					// 関数＆マクロ使用の為
#include "fade.h"					// 関数使用の為
#include "input.h"					// 同上
#include "fade.h"					// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(int no);					// 頂点作成関数
void SetVertexTitleEffect(int no);					// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


TITLE					titleWk[TITLE_MAX];			// タイトル構造体最大数宣言

bool					effectflag;					// エフェクト用制御変数
int						effect;						// エフェクト用変数

int						g_Alpha;					// αテストの閾値

int						serect;						// 画面遷移制御変数
int						titlecnt;					// カーソル制御変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitTitle(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// エフェクト関係の初期化
	effectflag = true;				// true:プラスする false:マイナスする
	effect=INIT_EFFECT;				// エフェクトのα値の初期化

	// 画面制御変数の初期化
	serect = 0;
	titlecnt = 0;

	// アルファテストの値の設定
	g_Alpha = ALPHA_TEST;


	// 構造体最大数初期化処理
	for(int i = 0; i < TITLE_MAX;i++, title++)
	{

		// アニメーション制御変数の初期化
		title->PatternAnim = rand() % TITLE_ANIM_PATTERN_NUM;	// アニメパターン番号をランダムで初期化
		title->CountAnim = 0;									// アニメカウントを初期化

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			title->Texture = NULL;

			// タイトル背景
			if (i == TITLE_BASE)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_BASE_POS;		// タイトル背景の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_BASE_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// アニメーション:A
			else if (i == TITLE_ANIM_A)
			{
				// 位置の設定
				title->use = false;					// 使用で初期化
				title->pos = TITLE_BASE_POS_A;		// アニメーション:Aの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_ANIM_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// アニメーション:D
			else if (i == TITLE_ANIM_D)
			{
				// 位置の設定
				title->use = false;					// 使用で初期化
				title->pos = TITLE_BASE_POS_D;		// アニメーション:Dの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_ANIM_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// タイトルロゴ
			else if (i == TITLE_LOGO)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_LOGO_POS;		// タイトルロゴの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_LOGO_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// コピーライト
			else if (i == TITLE_CPY)
			{
				// 位置の設定
				title->use = false;					// 使用で初期化
				title->pos = TITLE_CPY_POS;			// コピーライトの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_CPY_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"ボタンをおしてね"
			// UIエフェクト:"ボタンをおしてね"
			else if ((i == TITLE_ANY)||(i == TITLE_ANY_EFFECT))
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_ANY_POS;			// UI:"ボタンをおしてね"＆UIエフェクト:"ボタンをおしてね"の位置の初期化


				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_ANY_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			else if ((i == TITLE_START) || (i == TITLE_START_EFFECT))
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_START_POS;		// UI:"はじめる"＆UIエフェクト:"はじめる"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_START_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			else if ((i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT))
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_CREDIT_POS;		// UI:"クレジット"＆UIエフェクト:"クレジット"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_CREDIT_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"クレジットED"(クレジットテクスチャ)
			else if (i == TITLE_BOAD)
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_BOAD_POS;		// UI:"クレジットED"(クレジットテクスチャ)の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_BOAD_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}
		}

		// ゲーム更新時
		else if (type == UPDATE)
		{
			// ひとまず使用で初期化
			title->use = true;

			// タイトルで最初表示するもの以外は未使用で初期化
			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			// UI:"クレジット"
			// UIエフェクト:"クレジット"
			// UI:"クレジットED"(クレジットテクスチャ)
			if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT)||(i == TITLE_BOAD))
			{
				title->use = false;		// 未使用
			}
		}

		// 頂点情報の作成
		MakeVertexTitle(i);
	}

	return S_OK;
}
//=============================================================================
// 終了処理関数
//=============================================================================
void UninitTitle(void)
{
	// ポインタの初期化
	TITLE *title = &titleWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// テクスチャの開放出来ていなかったら
		if (title->Texture != NULL)
		{

			// テクスチャの開放
			title->Texture->Release();
			title->Texture = NULL;
		}
	}

}
//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateTitle(void)
{

	// ポインタの初期化
	TITLE *title = &titleWk[0];

	// エフェクト処理
	// プラスフラグ
	if (effectflag == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		effect += EFFECT_SPEED;

		// エフェクトα値が最大
		if (effect == ALPHA_MAX)
		{
			// フラグをマイナスに
			effectflag = false;
		}
	}

	// マイナスフラグ
	else if (effectflag == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		effect -= EFFECT_SPEED;

		// エフェクトα値が最小
		if (effect == ALPHA_BASE)
		{
			// フラグをプラスに
			effectflag = true;
		}

	}

	// アニメーション
	// 構造体最大数更新処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{
		// アニメーション:A＆アニメーション:D
		if ((i == TITLE_ANIM_A) || (i == TITLE_ANIM_D))
		{
			// 毎フレームインクリメント
			title->CountAnim++;

			// アニメーション切り替え処理
			if ((title->CountAnim % TITLE_ANIM_TIME) == 0)
			{
				// パターンの切り替え
				title->PatternAnim = (title->PatternAnim + 1) % TITLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureTitle(i, title->PatternAnim);
			}
		}

		// エフェクト処理
		SetVertexTitleEffect(i);
	}

	// ステージ遷移処理
	// 初回
	if (serect == FIRST)
	{

		// EnterまたはSTARTボタンを押したら、ステージを切り替える
		if ((GetKeyboardTrigger(DIK_A))||(IsButtonTriggered(0, BUTTON_START)))
		{
			// ポインタの初期化
			TITLE *title = &titleWk[TITLE_ANY];

			// UI部分の更新処理
			for (int i = TITLE_ANY;i < TITLE_MAX;i++, title++)
			{

				// 最初に表示するものを使用
				if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT))
				{
					title->use = true;
				}

				// それ以外を未使用
				else
				{
					title->use = false;
				}

			}

			// セレクトUIの表示
			serect = UPDATE;
		}
	}

	// セレクトUIの表示中
	else if(serect == UPDATE)
	{
		// 使用する構造体のポインタの初期化
		TITLE *titles = &titleWk[TITLE_START];						// UI:"はじめる"
		TITLE *titleS = &titleWk[TITLE_START_EFFECT];				// UIエフェクト:"はじめる"
		TITLE *titlec = &titleWk[TITLE_CREDIT];						// UI:"クレジット"
		TITLE *titleC = &titleWk[TITLE_CREDIT_EFFECT];				// UIエフェクト:"クレジット"

		// セレクトメニューの表示中
		switch (titlecnt)
		{

		// UI:"はじめる"の処理
		case TITLE_UI_START:
		{

			// UIエフェクト:"はじめる"を使用に
			titleS->use = true;

			// UIエフェクト:"クレジット"を未使用に
			titleC->use = false;

			// UI:"はじめる"の色を黄色に
			titles->vertex[0].diffuse = COLOR_GREEN;
			titles->vertex[1].diffuse = COLOR_GREEN;
			titles->vertex[2].diffuse = COLOR_GREEN;
			titles->vertex[3].diffuse = COLOR_GREEN;

			// UI:"クレジット"の色を元に戻す
			titlec->vertex[0].diffuse = COLOR_WHITE;
			titlec->vertex[1].diffuse = COLOR_WHITE;
			titlec->vertex[2].diffuse = COLOR_WHITE;
			titlec->vertex[3].diffuse = COLOR_WHITE;

			// Enterを押したら、ステージを切り替える
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// 画面遷移:ステージ選択
				SetFade(FADE_OUT, SCENE_STAGE);

			}

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
			{

				// カーソルを上に移動
				titlecnt--;
			}

			// Sを押したら、カーソル移動
			else if (GetKeyboardTrigger(DIK_S))
			{

				// カーソルを下に移動
				titlecnt++;
			}

			break;
		}

		// UI:"クレジット"の処理
		case TITLE_UI_CREDIT:
		{

			// UIエフェクト:"クレジット"を使用に
			titleC->use = true;

			// UIエフェクト:"はじめる"を未使用に
			titleS->use = false;

			// UI:"クレジット"の色を黄色に
			titlec->vertex[0].diffuse = COLOR_GREEN;
			titlec->vertex[1].diffuse = COLOR_GREEN;
			titlec->vertex[2].diffuse = COLOR_GREEN;
			titlec->vertex[3].diffuse = COLOR_GREEN;

			// UI:"はじめる"の色を元に戻す
			titles->vertex[0].diffuse = COLOR_WHITE;
			titles->vertex[1].diffuse = COLOR_WHITE;
			titles->vertex[2].diffuse = COLOR_WHITE;
			titles->vertex[3].diffuse = COLOR_WHITE;

			// Enterを押したら、クレジットを表示
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				// カーソル制御変数をクレジットに
				serect = CREDIT;

			}

			// Wを押したら、カーソル移動
			if (GetKeyboardTrigger(DIK_W))
			{

				// カーソルを上に移動
				titlecnt--;
			}

			// Sを押したら、カーソル移動
			else if(GetKeyboardTrigger(DIK_S))
			{

				// カーソルを下に移動
				titlecnt++;
			}

			break;
		}

		}

		// カーソルループ移動処理
		// UI:"はじめる"で↑入力時
		if (titlecnt < TITLE_UI_START)
		{
			// UI:"クレジット"に移動
			titlecnt = TITLE_UI_MAX - 1;
		}

		// UI:"クレジット"で↓入力時
		else if (titlecnt > TITLE_UI_MAX - 1)
		{
			// UI:"はじめる"に移動
			titlecnt = TITLE_UI_START;
		}
	}

	// UI:"クレジットED"(クレジットテクスチャ)
	else if (serect == CREDIT)
	{

		// 使用する構造体のポインタの初期化 UI:"クレジットED"(クレジットテクスチャ)
		TITLE *titleB = &titleWk[TITLE_BOAD];

		// UI:"クレジットED"(クレジットテクスチャ)を表示
		titleB ->use= true;

		// Enterまたは×ボタンを押したら、カーソル選択に戻る
		if (GetKeyboardTrigger(DIK_RETURN))
		{

			titleB->use = false;			// UI:"クレジットED"(クレジットテクスチャ)を非表示
			serect = UPDATE;				// 前のカーソル選択処理に戻す
			titlecnt = TITLE_UI_START;		// カーソルを初期位置に戻す
		}

	}


}
//=============================================================================
// 描画処理関数
//=============================================================================
void DrawTitle(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_Alpha);		 //条件：変数数値
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//条件:大きかったら

	// 構造体最大数終了処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// テクスチャ使用中
		if (title->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, title->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, title->vertex, sizeof(VERTEX_2D));
		}
	}

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	
	// ポインタの初期化
	TITLE *title = &titleWk[no];

	// タイトル背景なら
	if (no==TITLE_BASE)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// アニメーション:A＆アニメーション:D
	else if ((no == TITLE_ANIM_A) || (no == TITLE_ANIM_D))
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANIM_SIZE_X, title->pos.y - TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANIM_SIZE_X, title->pos.y - TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANIM_SIZE_X, title->pos.y + TITLE_ANIM_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANIM_SIZE_X, title->pos.y + TITLE_ANIM_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// タイトルロゴ
	else if (no == TITLE_LOGO)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// コピーライト
	else if (no == TITLE_CPY)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CPY_SIZE_X, title->pos.y - TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CPY_SIZE_X, title->pos.y - TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CPY_SIZE_X, title->pos.y + TITLE_CPY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CPY_SIZE_X, title->pos.y + TITLE_CPY_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI:"ボタンをおしてね"
	else if (no == TITLE_ANY)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"ボタンをおしてね"
	else if (no == TITLE_ANY_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"はじめる"
	else if (no == TITLE_START)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UIエフェクト:"はじめる"
	else if (no == TITLE_START_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	}


	// UI:"クレジット"
	else if (no == TITLE_CREDIT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UIエフェクト:"クレジット"
	else if (no == TITLE_CREDIT_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	}

	// UI:"クレジットED"(クレジットテクスチャ)
	else if (no == TITLE_BOAD)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// テクスチャのパースペクティブコレクト用
	title->vertex[0].rhw =
	title->vertex[1].rhw =
	title->vertex[2].rhw =
	title->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	title->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	title->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	title->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTitle(int no, int cntPattern)
{

	// ポインタの初期化
	TITLE *title = &titleWk[no];

	// テクスチャ座標の設定
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
// エフェクト関数
//=============================================================================
void SetVertexTitleEffect(int no)
{

	// ポインタの初期化
	TITLE *title = &titleWk[no];

	// 変更されたエフェクトのα値の設定
	// UIエフェクト:"ボタンをおしてね"
	 if (no == TITLE_ANY_EFFECT)
	{

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	 // UIエフェクト:"はじめる"
	 if (no == TITLE_START_EFFECT)
	 {

		 // 反射光の設定
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	 }

	 // UIエフェクト:"クレジット"
	 if (no == TITLE_CREDIT_EFFECT)
	 {

		 // 反射光の設定
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 50, effect);

	 }

}
