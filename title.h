//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/2/21
//
//=============================================================================


// 多重インクルード防止の為
#ifndef _TITLE_H_
#define _TITLE_H_

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

#define	TITLE_BASE_TEXTURE			("data/TEXTURE/title.png")						// 読み込むテクスチャファイル名
#define	TITLE_BASE_SIZE_X			(SCREEN_WIDTH/2)											// テクスチャの幅
#define	TITLE_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// テクスチャの高さ
#define TITLE_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// タイトル背景の位置

#define	TITLE_ANIM_TEXTURE			("data/TEXTURE/doraivu03.png")					// 読み込むテクスチャファイル名
#define	TITLE_ANIM_SIZE_X			(250/2)											// テクスチャの幅
#define	TITLE_ANIM_SIZE_Y			(200/2)											// テクスチャの高さ
#define TITLE_BASE_POS_A			D3DXVECTOR3(700/2.0f,250/2.0f,0.0f)				// アニメーション:Aの位置
#define TITLE_BASE_POS_D			D3DXVECTOR3(1550/2.0f,250/2.0f,0.0f)			// アニメーション:Dの位置

#define TITLE_ANIM_PATTERN_DIVIDE_X	(4)															// アニメパターンのテクスチャ内分割数（X)
#define TITLE_ANIM_PATTERN_DIVIDE_Y	(2)															// アニメパターンのテクスチャ内分割数（Y)
#define TITLE_ANIM_PATTERN_NUM		(TITLE_ANIM_PATTERN_DIVIDE_X*TITLE_ANIM_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TITLE_ANIM_TIME				(6)															// アニメーションの切り替わるカウント

#define	TITLE_LOGO_TEXTURE			("data/TEXTURE/titleLogo.png")					// 読み込むテクスチャファイル名
#define	TITLE_LOGO_SIZE_X			(850/2)											// テクスチャの幅
#define	TITLE_LOGO_SIZE_Y			(270/2)											// テクスチャの高さ
#define TITLE_LOGO_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,300/2.0f,0.0f)	// タイトル上部の位置

#define	TITLE_CPY_TEXTURE			("data/TEXTURE/コピーライト.png")				// 読み込むテクスチャファイル名
#define	TITLE_CPY_SIZE_X			(250/2)											// テクスチャの幅
#define	TITLE_CPY_SIZE_Y			(40/2)											// テクスチャの高さ
#define TITLE_CPY_POS				D3DXVECTOR3(150.0f,660.0f,0.0f)					// コピーライトの位置

#define	TITLE_ANY_TEXTURE			("data/TEXTURE/ボタンをおしてね.png")			// 読み込むテクスチャファイル名
#define	TITLE_ANY_SIZE_X			(280/2)											// テクスチャの幅
#define	TITLE_ANY_SIZE_Y			(70/2)											// テクスチャの高さ
#define TITLE_ANY_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.,0.0f)		// UI:"ボタンをおしてね"

#define	TITLE_START_TEXTURE			("data/TEXTURE/はじめる.png")					// 読み込むテクスチャファイル名
#define	TITLE_START_SIZE_X			(280/2)											// テクスチャの幅
#define	TITLE_START_SIZE_Y			(70/2)											// テクスチャの高さ
#define TITLE_START_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,450.,0.0f)		// UI:"はじめる"

#define	TITLE_CREDIT_TEXTURE			("data/TEXTURE/クレジット.png")				// 読み込むテクスチャファイル名
#define	TITLE_CREDIT_SIZE_X			(280/2)											// タイトルの幅
#define	TITLE_CREDIT_SIZE_Y			(70/2)											// タイトルの高さ
#define TITLE_CREDIT_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,600.0f,0.0f)	// UI:"クレジット"

#define	TITLE_BOAD_TEXTURE			("data/TEXTURE/クレジットED.png")							// 読み込むテクスチャファイル名
#define	TITLE_BOAD_SIZE_X			(1100/2)													// テクスチャの幅
#define	TITLE_BOAD_SIZE_Y			(650/2)														// テクスチャの高さ
#define TITLE_BOAD_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// UI:"クレジットED"(クレジットテクスチャ)

#define	TITLE_ANY_EFFECT_SIZE_X		(290/2)											// テクスチャの幅
#define	TITLE_ANY_EFFECT_SIZE_Y		(80/2)											// テクスチャの高さ

#define COLOR_WHITE					D3DCOLOR_RGBA(255, 255, 255, 255);				// UIカーソルの色:白
#define COLOR_YELLOW				D3DCOLOR_RGBA(255, 175, 0, 255);				// UIカーソルの色:黄色
#define COLOR_GREEN					D3DCOLOR_RGBA(0, 255, 50, 255);					// UIカーソルの色:緑色


// タイトル構造体制御マクロ
enum
{
	TITLE_BASE,						// タイトル下部
	TITLE_ANIM_A,					// アニメーション:A
	TITLE_ANIM_D,					// アニメーション:D
	TITLE_LOGO,						// タイトル上部
	TITLE_CPY,						// コピーライト

	TITLE_ANY,						// UI:"ボタンをおしてね"
	TITLE_ANY_EFFECT,				// UIエフェクト:"ボタンをおしてね"
	TITLE_START,					// UI:"はじめる"
	TITLE_START_EFFECT,				// UIエフェクト:"はじめる"
	TITLE_CREDIT,					// UI:"クレジット"
	TITLE_CREDIT_EFFECT,			// UIエフェクト:"クレジット"

	TITLE_BOAD,						// UI:"クレジットED"(クレジットテクスチャ)
	TITLE_MAX,						// タイトル構造体最大数
};

// UIカーソル制御マクロ
enum
{
	TITLE_UI_START,					// UI:"はじめる"
	TITLE_UI_CREDIT,				// UI:"クレジット"
	TITLE_UI_MAX,					// UIカーソル最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	bool					use;						// 描画制御変数 true:使用 false:未使用

	int						CountAnim;					// アニメーションカウント変数
	int						PatternAnim;				// アニメーションパターンナンバー変数

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}TITLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(int type);							// 初期化処理関数
void UninitTitle(void);									// 終了処理関数
void UpdateTitle(void);									// 更新処理関数
void DrawTitle(void);									// 描画処理関数
void SetTextureTitle(int no, int cntPattern);			// テクスチャ座標の設定

#endif
