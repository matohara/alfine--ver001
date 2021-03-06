//=============================================================================
//
// Object-AClass <object.cpp>
// Author : 初 景新
//
//=============================================================================
#ifndef __CLASS_OBJECT_CLASS_INCLUDE_H__
#define __CLASS_OBJECT_CLASS_INCLUDE_H__


#include "../../main.h"
#include "../../Camera.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************
/* オブジェクトAクラス */
class class_ObjectA
{

protected:
	LPDIRECT3DTEXTURE9		Texture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;	// 頂点バッファインターフェースへのポインタ

	D3DXVECTOR3 Position;	// 位置座標
	D3DXVECTOR3 Rotation;	// 回転角度
	D3DXVECTOR2 Size;		// ポリゴンサイズ
	float Scale;			// サイズ倍率

	int TexPattern_X;		// テクスチャパターン（横）
	int TexPattern_Y;		// テクスチャパターン（縦）
	int AnimeCount;			// アニメーションカウント
	int AnimePattern;		// 現在のアニメーションパターン番号
	int ChangeAnimeTime;	// アニメーション切り替え待時間

	virtual int MakeVertex(void);				// 頂点作成
	virtual void SetVertex(void);				// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);	// 頂点座標設定@頂点色込み

public:
	class_ObjectA();
	~class_ObjectA();

	virtual void Draw(void);						// 描画処理(通常)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理(通常)(テクスチャ指定)
	virtual void DrawBillboard(void);						// 描画処理(ビルボード)
	virtual void DrawBillboard(LPDIRECT3DTEXTURE9 texture);	// 描画処理(ビルボード)(テクスチャ指定)

	virtual void ReleaseBuffer(void);	// バッファ系開放
	virtual void LoadTexture(const char *texture);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);	//テクスチャ情報@アニメーションなし

private:

};


/* オブジェクトGクラス */
class class_ObjectG
{

protected:
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;	// 頂点バッファインターフェースへのポインタ

	D3DXVECTOR3 Position;	// 位置座標
	D3DXVECTOR3 Rotation;	// 回転角度
	D3DXVECTOR2 Size;		// ポリゴンサイズ
	float Scale;			// サイズ倍率

	virtual int MakeVertex(void);				// 頂点作成
	virtual void SetVertex(void);				// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);	// 頂点座標設定@頂点色込み

public:
	class_ObjectG();
	~class_ObjectG();

	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理

	virtual void ReleaseBuffer(void);	// バッファ系開放

private:

};


/* オブジェクトGクラス */
class class_ObjectU
{
	
protected:
	LPDIRECT3DTEXTURE9	Texture;			// テクスチャへのポインタ
	VERTEX_2D			Vertex[NUM_VERTEX];	// 頂点情報

	virtual void MakeVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点作成
	virtual void SetVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);			// 頂点座標設定@頂点色込み

public:
	class_ObjectU();
	~class_ObjectU();

	virtual void Draw(void);						// 描画処理(通常)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理(通常)(テクスチャ指定)

	virtual void ReleaseBuffer(void);	// バッファ系開放
	virtual void LoadTexture(const char *texture);

private:

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
