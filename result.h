//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/6/12
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _RESULT_H_
#define _RESULT_H_

// マクロ＆ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define RESULT_EFFECT_SPEED				(2)		// 点滅速度速度

#define	RESULT_BASE_TEXTURE				("data/TEXTURE/砂浜.png")									// 読み込むテクスチャファイル名
#define	RESULT_BASE_SIZE_X				(SCREEN_WIDTH/2.0f)											// テクスチャの幅
#define	RESULT_BASE_SIZE_Y				(SCREEN_HEIGHT/2.0f)										// テクスチャの高さ
#define RESULT_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// 砂浜の位置

#define	RESULT_BOAD_TEXTURE				("data/TEXTURE/ResultLogo.png")							// 読み込むテクスチャファイル名
#define	RESULT_BOAD_SIZE_X				(900/2.0f)													// テクスチャの幅
#define	RESULT_BOAD_SIZE_Y				(506/2.0f)													// テクスチャの高さ
#define RESULT_BOAD_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,281.0f,0.0f)					// リザルトボードの位置

#define	RESULT_BLACK_TEXTURE			("data/TEXTURE/黒板リザルト.png")							// 読み込むテクスチャファイル名
#define	RESULT_BLACK_SIZE_X				(744/2.0f)													// テクスチャの幅
#define	RESULT_BLACK_SIZE_Y				(458/2.0f)													// テクスチャの高さ
#define RESULT_BLACK_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,284.0f,0.0f)					// 黒板リザルトの位置

#define	RESULT_SCORE_TEXTURE			("data/TEXTURE/結果発表.png")								// 読み込むテクスチャファイル名
#define	RESULT_SCORE_SIZE_X				(270/2)														// テクスチャの幅
#define	RESULT_SCORE_SIZE_Y				(74/2)														// テクスチャの高さ
#define RESULT_SCORE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,133.0f,0.0f)					// 結果発表の位置

#define	RESULT_SUM_TEXTURE				("data/TEXTURE/合計.png")									// 読み込むテクスチャファイル名
#define	RESULT_SUM_SIZE_X				(82/2)														// テクスチャの幅
#define	RESULT_SUM_SIZE_Y				(52/2)														// テクスチャの高さ
#define RESULT_SUM_POS					D3DXVECTOR3(395.0f,449.0f,0.0f)								// 合計の位置

#define	RESULT_ENEMY_TEXTURE			("data/TEXTURE/倒した敵の数.png")							// 読み込むテクスチャファイル名
#define	RESULT_ENEMY_SIZE_X				(162/2)														// テクスチャの幅
#define	RESULT_ENEMY_SIZE_Y				(32/2)														// テクスチャの高さ
#define RESULT_ENEMY_POS				D3DXVECTOR3(395.0f,234.0f,0.0f)								// 倒した敵の数の位置

#define	RESULT_BOSS_TEXTURE				("data/TEXTURE/ボス撃破.png")								// 読み込むテクスチャファイル名
#define	RESULT_BOSS_SIZE_X				(110/2)														// テクスチャの幅
#define	RESULT_BOSS_SIZE_Y				(32/2)														// テクスチャの高さ
#define RESULT_BOSS_POS					D3DXVECTOR3(395.0f,296.5f,0.0f)								// ボス撃破の位置

#define	RESULT_TIME_TEXTURE				("data/TEXTURE/残り時間.png")								// 読み込むテクスチャファイル名
#define	RESULT_TIME_SIZE_X				(110/2)														// テクスチャの幅
#define	RESULT_TIME_SIZE_Y				(32/2)														// テクスチャの高さ
#define RESULT_TIME_POS					D3DXVECTOR3(395.0f,354.0f,0.0f)								// 残り時間の位置

#define	RESULT_RANK_TEXTURE				("data/TEXTURE/評価.png")									// 読み込むテクスチャファイル名
#define	RESULT_RANK_SIZE_X				(172/2)														// テクスチャの幅
#define	RESULT_RANK_SIZE_Y				(140/2)														// テクスチャの高さ
#define RESULT_RANK_POS					D3DXVECTOR3(803.0f,325.0f,0.0f)								// 評価の位置

#define	RESULT_RANK_EFFECT_SIZE_X		(182/2)														// テクスチャの幅
#define	RESULT_RANK_EFFECT_SIZE_Y		(150/2)														// テクスチャの高さ

#define RESULT_ANIM_PATTERN_DIVIDE_X	(4)															// アニメパターンのテクスチャ内分割数（X)
#define RESULT_ANIM_PATTERN_DIVIDE_Y	(1)															// アニメパターンのテクスチャ内分割数（Y)
#define RESULT_ANIM_PATTERN_NUM			(RESULT_ANIM_PATTERN_DIVIDE_X*RESULT_ANIM_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define RESULT_ANIM_TIME				(6)															// アニメーションの切り替わるカウント

#define	RESULT_SAFU_TEXTURE				("data/TEXTURE/safu01.png")									// 読み込むテクスチャファイル名
#define	RESULT_SAFU_SIZE_X				(438/2)														// テクスチャの幅
#define	RESULT_SAFU_SIZE_Y				(920/2)														// テクスチャの高さ
#define RESULT_SAFU_POS					D3DXVECTOR3(1116.0f,540.0f,0.0f)							// サフの位置

#define	RESULT_AIBISU_TEXTURE			("data/TEXTURE/アイビス０１.png")							// 読み込むテクスチャファイル名
#define	RESULT_AIBISU_SIZE_X			(408/2)														// テクスチャの幅
#define	RESULT_AIBISU_SIZE_Y			(724/2)														// テクスチャの高さ
#define RESULT_AIBISU_POS				D3DXVECTOR3(121.0f,539.0f,0.0f)								// アイビスの位置


#define	RESULT_BLACK_S_TEXTURE			("data/TEXTURE/黒板メニュー.png")							// 読み込むテクスチャファイル名
#define	RESULT_BLACK_S_SIZE_X			(310/2)														// テクスチャの幅
#define	RESULT_BLACK_S_SIZE_Y			(318/2)														// テクスチャの高さ
#define RESULT_BLACK_S_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.0f,0.0f)					// 黒板メニューの位置

#define	RESULT_INIT_TEXTURE				("data/TEXTURE/やりなおす.png")								// 読み込むテクスチャファイル名
#define	RESULT_INIT_SIZE_X				(280/2)														// テクスチャの幅
#define	RESULT_INIT_SIZE_Y				(70/2)														// テクスチャの高さ
#define RESULT_INIT_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,430.,0.0f)					// やりなおすの位置

#define	RESULT_FINISH_TEXTURE			("data/TEXTURE/おわる.png")									// 読み込むテクスチャファイル名
#define	RESULT_FINISH_SIZE_X			(180/2)														// テクスチャの幅
#define	RESULT_FINISH_SIZE_Y			(70/2)														// テクスチャの高さ
#define RESULT_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,570.0f,0.0f)					// おわるの位置

#define	RESULT_ANY_EFFECT_SIZE_X		(290/2)														// テクスチャの幅
#define	RESULT_ANY_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ
#define	RESULT_FINISH_EFFECT_SIZE_X		(190/2)														// テクスチャの幅
#define	RESULT_FINISH_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ


// タイトル構造体制御マクロ
enum
{
	RESULT_BASE,							// 砂浜
	RESULT_BOAD,							// リザルトボード
	RESULT_BLACK,							// 黒板リザルト
	RESULT_SCORE,							// 結果発表
	RESULT_SUM,								// 合計
	RESULT_ENEMY,							// 倒した敵の数
	RESULT_BOSS,							// ボス撃破
	RESULT_TIME,							// 残り時間
	RESULT_RANK,							// 評価
	RESULT_RANK_EFFECT,						// エフェクト:評価

	RESULT_SAFU,							// サフ
	RESULT_AIBISU,							// アイビス

	RESULT_BLACK_S,							// 黒板メニュー
	RESULT_INIT,							// UI:"やりなおす"
	RESULT_INIT_EFFECT,						// UIエフェクト:"やりなおす"
	RESULT_FINISH,							// UI:"おわる"
	RESULT_FINISH_EFFECT,					// UIエフェクト:"おわる"
	RESULT_MAX,								// 構造体最大数
};


// リザルトカーソル制御マクロ
enum
{
	RESULT_UI_INIT,					// UI:"やりなおす"
	RESULT_UI_FINISH,				// UI:"おわる"
	RESULT_UI_MAX,					// UIカーソル最大数
};

//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	int						CountAnim;					// アニメーションカウント変数
	int						PatternAnim;				// アニメーションパターンナンバー変数

	bool					use;						// 描画制御変数 true:使用 false:未使用

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}RESULT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int type);							// 初期化処理関数
void UninitResult(void);								// 終了処理関数
void UpdateResult(void);								// 更新処理関数
void DrawResult(void);									// 描画処理関数
void SetTextureResult(int no, int cntPattern);			// テクスチャ座標の設定

#endif
