//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 初 景新
//
//=============================================================================
#include "../../main.h"
#include "../../input.h"

#include "../../Game.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----プレイヤー情報セット--------
void PlayerA::LoadPlayerStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, 1, 1, 1);

	Position = D3DXVECTOR3(0.0f, y, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----ルート読み込み--------
void PlayerA::LoadRoute(void)
{
	// Output 受け取る
	FILE *fp = fopen(DATAFILE_PLAYER_ROUTE, "r");	// ファイルを開く

	// ファイルが開けたかチェック
	if (fp == NULL)
	{
		MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Open\"", MB_YESNO);
	}

	// マップデータを取る
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#MAP_NUMBER"))
		{
			MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Read\"", MB_YESNO);
		}
	}

	fscanf(fp, "%d", &MapMax);
	PointMax = new int[MapMax];

	// ファイルから読み込む
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		fscanf(fp, "%d", &PointMax[iCnt]);
	}

	// ルートデータを取る
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#ROUTE_DATA"))
		{
			MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// メモリ確保
	Route = new PlayerRoute*[MapMax];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		Route[iCnt] = new PlayerRoute[PointMax[iCnt]];
	}

	char skep;
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		for (int iCnt2 = 0; iCnt2 < PointMax[iCnt]; iCnt2++)
		{
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.x);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.y);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.z);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%d", &Route[iCnt][iCnt2].Time);
			fscanf(fp, "%c", &skep);
		}
	}

	fclose(fp);	// ファイル操作終了

}


//----初期化処理--------
void PlayerA::Init(void)
{
	// 情報リセット
	{
		Texture = NULL;		// テクスチャへのポインタ
		VtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置座標
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転角度
		Size = D3DXVECTOR2(0.0f, 0.0f);				// ポリゴンサイズ
		Scale = 1.0f;								// サイズ倍率
		TexPattern_X = 1;		// テクスチャパターン（横）
		TexPattern_Y = 1;		// テクスチャパターン（縦）
		AnimeCount = 0;			// アニメーションカウント
		AnimePattern = 0;		// 現在のアニメーションパターン番号
		ChangeAnimeTime = 0;	// アニメーション切り替え待時間

		Route = NULL;		// 移動ルート保存用ポインター
		MapNumber = 0;		// 次のマップ番号
		NextPoint = 0;		// 次の移動先番号
		RouteCounter = 0;	// 移動進行度
		PointMax = NULL;	// 移動ポイント数
		MapMax = 0;			// マップ最大数
	}

	// テクスチャ読み込み
	LoadTexture(TEXTURE_PLAYER);

	// プレイヤー情報をセット
	LoadPlayerStatus(21.4f, 32.4f);

	// 移動ルートを設定
	LoadRoute();
}

//----更新処理--------
void PlayerA::Update(void)
{
	if (NextPoint == 0)
	{// 原点は瞬時移動
		Position = Route[MapNumber][NextPoint].Point;
		NextPoint++;
	}
	else
	{// 指定ポイントまで移動
		// 移動ベクトルを求める
		Position += (Route[MapNumber][NextPoint].Point - Route[MapNumber][NextPoint - 1].Point) / (float)Route[MapNumber][NextPoint].Time;
		RouteCounter++;
		if (RouteCounter == Route[MapNumber][NextPoint].Time)
		{// 指定フレーム数移動終了
			RouteCounter = 0;
			NextPoint++;
		}

		// 全ポイントを移動後次のマップへ
		if (NextPoint >= PointMax[MapNumber])
		{
			MapNumber++;
			NextPoint = 0;
		}

		// *全マップ終了後終了
		if (MapNumber >= MapMax)
		{
			MapNumber = MapMax - 1;
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
		}
	}

	PrintDebugProcess("プレイヤー位置 : （%f, %f, %f）\n", Position.x, Position.y, Position.z);
}

//----描画処理--------
void PlayerA::Draw(void)
{
	// 描画
	this->class_ObjectA::DrawBillboard();
}

//----終了処理--------
void PlayerA::Uninit(void)
{
	// テクスチャバッファ開放
	ReleaseBuffer();

	// ルートデータメモリ開放
	ReleaseRouteData();
}


//----メモリ開放--------
void PlayerA::ReleaseRouteData(void)
{
	for (int i = 0; i < MapMax; i++)
	{
		delete[] Route[i];
	}
	delete[] Route;
	Route = NULL;

	delete[] PointMax;
	PointMax = NULL;
}


