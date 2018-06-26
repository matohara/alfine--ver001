//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _OBJECT_PLAYER_INCLUDE_H_
#define _OBJECT_PLAYER_INCLUDE_H_


#include "../class/Aclass_object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PLAYER		_T("data/TEXTURE/PLAYER/PLAYER.png")	// プレイヤー画像

#define DATAFILE_PLAYER_ROUTE	"data/STAGE/RouteData.txt"

#define PLAYER_MOVE_SPEED	(10.0f)	// プレイヤーの移動速度

#define PLAYER_MAX		(1)		//プレイヤー最大数

//*****************************************************************************
// クラス設計
//*****************************************************************************
class PlayerRoute
{
public:
	D3DXVECTOR3 Point;	// 次に向かうべき位置
	int Time;			// 到着までにかかるフレーム数

	PlayerRoute()
	{
		Point = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Time = 60;
	};
	PlayerRoute(D3DXVECTOR3 point, int time)
	{
		Point = point;
		Time = time;
	}
	~PlayerRoute() {};

private:

};

class PlayerA : public class_ObjectA
{
	PlayerRoute **Route;	// 移動ルート保存用ポインター
	int MapNumber;			// マップ番号
	int NextPoint;			// 次の移動先番号
	int RouteCounter;		// 移動進行度
	int *PointMax;			// 移動ポイント数
	int MapMax;				// マップ最大数
public:

	PlayerA() {};
	~PlayerA() {};

	void LoadPlayerStatus(float x, float y);
	void LoadRoute();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	void ReleaseRouteData(void);

	int GetMapNumber(void)
	{
		return MapNumber;
	};
	D3DXVECTOR3 GetPosition(float x, float y, float z)
	{
		return (Position + D3DXVECTOR3(x, y, z));
	}

private:

};


#endif
