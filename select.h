//=============================================================================
//
// セレクト選択画面処理 [select.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/6/12
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _SELECT_H_
#define _SELECT_H_

// マクロ＆ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define INIT_EFFECT					(1)												// エフェクトのRGBの初期値
#define ALPHA_TEST					(125)											// アルファテストのαの値
#define ALPHA_BASE					(1)												// テクスチャのαの値
#define ALPHA_MAX					(255)											// αの値の最大値
#define EFFECT_SPEED				(2)												// 点滅速度速度

#define	SELECT_BASE_TEXTURE			("data/TEXTURE/Background.png")				// 読み込むテクスチャファイル名
#define	SELECT_BASE_SIZE_X			(SCREEN_WIDTH/2)											// テクスチャの幅
#define	SELECT_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// テクスチャの高さ
#define SELECT_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// セレクト下部の位置

#define	SELECT_ANIM_TEXTURE			("data/TEXTURE/doraivu03.png")					// 読み込むテクスチャファイル名
#define	SELECT_ANIM_SIZE_X			(250/2)											// テクスチャの幅
#define	SELECT_ANIM_SIZE_Y			(200/2)											// テクスチャの高さ
#define SELECT_BASE_POS_A			D3DXVECTOR3(700/2.0f,250/2.0f,0.0f)				// アニメーション:Aの位置
#define SELECT_BASE_POS_D			D3DXVECTOR3(1550/2.0f,250/2.0f,0.0f)			// アニメーション:Dの位置

#define SELECT_ANIM_PATTERN_DIVIDE_X	(4)															// アニメパターンのテクスチャ内分割数（X)
#define SELECT_ANIM_PATTERN_DIVIDE_Y	(2)															// アニメパターンのテクスチャ内分割数（Y)
#define SELECT_ANIM_PATTERN_NUM		(SELECT_ANIM_PATTERN_DIVIDE_X*SELECT_ANIM_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define SELECT_ANIM_TIME				(6)															// アニメーションの切り替わるカウント

#define	SELECT_OPTION_TEXTURE			("data/TEXTURE/OptionLogo0.png")			// 読み込むテクスチャファイル名
#define	SELECT_OPTION_SIZE_X			(350/2)											// テクスチャの幅
#define	SELECT_OPTION_SIZE_Y			(150/2)											// テクスチャの高さ
#define SELECT_OPTION_POS				D3DXVECTOR3(200.0f,600.0f,0.0f)		// UI:"ボタンをおしてね"

#define	SELECT_OPTION_EFFECT_SIZE_X		(360/2)											// テクスチャの幅
#define	SELECT_OPTION_EFFECT_SIZE_Y		(160/2)											// テクスチャの高さ

#define	SELECT_TUTORIAL_TEXTURE			("data/TEXTURE/チュートリアルバー.png")			// 読み込むテクスチャファイル名
#define	SELECT_TUTORIAL_SIZE_X			(600/2)											// テクスチャの幅
#define	SELECT_TUTORIAL_SIZE_Y			(200/2)											// テクスチャの高さ
#define SELECT_TUTORIAL_POS				D3DXVECTOR3(850.0f,SCREEN_HEIGHT/2.0,0.0f)		// UI:"チュートリアル"

#define SELECT_TUTORIAL_A_POS			D3DXVECTOR3(1000.0f,510.0f,0.0f)		// UI:"チュートリアルA"

#define	SELECT_TUTORIAL_B_SIZE_X		(400/2)											// テクスチャの幅
#define	SELECT_TUTORIAL_B_SIZE_Y		(150/2)											// テクスチャの高さ
#define SELECT_TUTORIAL_B_POS			D3DXVECTOR3(1100.0f,610.0f,0.0f)		// UI:"チュートリアルA"

#define	SELECT_TUTORIAL_C_SIZE_X		(300/2)											// テクスチャの幅
#define	SELECT_TUTORIAL_C_SIZE_Y		(100/2)											// テクスチャの高さ
#define SELECT_TUTORIAL_C_POS			D3DXVECTOR3(1100.0f,100,0.0f)		// UI:"チュートリアルA"

#define SELECT_TUTORIAL_D_POS			D3DXVECTOR3(1000.0f,210,0.0f)		// UI:"チュートリアルA"

#define	SELECT_ANY_EFFECT_SIZE_X		(610/2)											// テクスチャの幅
#define	SELECT_ANY_EFFECT_SIZE_Y		(210/2)											// テクスチャの高さ

#define	SELECT_ANY_B_EFFECT_SIZE_X		(610/2)											// テクスチャの幅
#define	SELECT_ANY_B_EFFECT_SIZE_Y		(210/2)											// テクスチャの高さ

#define	SELECT_ANY_C_EFFECT_SIZE_X		(610/2)											// テクスチャの幅
#define	SELECT_ANY_C_EFFECT_SIZE_Y		(210/2)											// テクスチャの高さ


#define COLOR_WHITE						D3DCOLOR_RGBA(255, 255, 255, 255);				// UIカーソルの色:白
#define COLOR_YELLOW					D3DCOLOR_RGBA(255, 175, 0, 255);				// UIカーソルの色:黄色

// セレクト構造体制御マクロ
enum
{
	SELECT_BASE,					// セレクト下部
	SELECT_ANIM_A,					// アニメーション:A
	SELECT_ANIM_D,					// アニメーション:D

	SELECT_OPTION,					// UI:"オプション"
	SELECT_OPTION_EFFECT,			// UIエフェクト:"オプション"
	SELECT_TUTORIAL,				// UI:"チュートリアル"
	SELECT_TUTORIAL_EFFECT,			// UIエフェクト:"チュートリアル"
	SELECT_TUTORIAL_A,				// UI:"チュートリアA\"
	SELECT_TUTORIAL_A_EFFECT,		// UIエフェクト:"チュートリアルA"
	SELECT_TUTORIAL_B,				// UI:"チュートリアB\"
	SELECT_TUTORIAL_B_EFFECT,		// UIエフェクト:"チュートリアルB"
	SELECT_TUTORIAL_C,				// UI:"チュートリアC\"
	SELECT_TUTORIAL_C_EFFECT,		// UIエフェクト:"チュートリアルC"
	SELECT_TUTORIAL_D,				// UI:"チュートリアD\"
	SELECT_TUTORIAL_D_EFFECT,		// UIエフェクト:"チュートリアルD"

	SELECT_MAX,						// セレクト構造体最大数
};

// UIカーソル制御マクロ
enum
{
	SELECT_UI_TUTORIAL,				// UI:"はじめる"
	SELECT_UI_CREDIT,				// UI:"クレジット"
	SELECT_UI_MAX,					// UIカーソル最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

// セレクト構造体
typedef struct
{

	bool					use;						// 描画制御変数 true:使用 false:未使用

	int						CountAnim;					// アニメーションカウント変数
	int						PatternAnim;				// アニメーションパターンナンバー変数

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}SELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSelect(int type);							// 初期化処理関数
void UninitSelect(void);								// 終了処理関数
void UpdateSelect(void);								// 更新処理関数
void DrawSelect(void);									// 描画処理関数
void SetTextureSelect(int no, int cntPattern);			// テクスチャ座標の設定

#endif
