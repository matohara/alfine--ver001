//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "sound.h"

#include "fade.h"

#include "title.h"
#include "result.h"
#include "select.h"				// 関数使用の為
#include "game.h"

#include "Field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"HPTApplication"		// ウインドウのクラス名
#define WINDOW_NAME		"葉っぱ隊製作物"		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

HWND hWnd;

int					g_nCountFPS;			// FPS表記用カウンタ
bool				g_bDispDebug = true;	// デバッグ表示ON/OFF
GAMESCENE			g_GameScene = SCENE_MAX;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD dwExecLastTime;	// 前回実行時刻
	DWORD dwFPSLastTime;	// 前回FPS更新時刻保持
	DWORD dwCurrentTime;	// 現時刻保持
	DWORD dwFrameCount;		// FPSカウンタ
	DWORD dwHighTimer;		// 精密1Fタイマー
//	DWORD dwPrecisionTime;	// 精密1Sタイマー(現状でずれることがあったら使用する)

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);
	dwExecLastTime =
//	dwPrecisionTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();				// 現時刻取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに表記用FPSカウンタを更新
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// 前回のFPS表記用時刻を現時刻に
				dwFrameCount = 0;	// 再カウントのためにリセット
			}

			// 60FPSの精密化(誤差(+-)2)
			dwHighTimer = (dwFrameCount % 3) == 0 ? 16 : 17;

			DWORD dwloop = (dwCurrentTime - dwExecLastTime) / dwHighTimer;
			if (dwloop > 0)
			{
				PrintDebugProcess("FPS:%d\n", g_nCountFPS);
				dwExecLastTime = dwCurrentTime;

				for (UINT i = 0; i < dwloop & i < 3; i++)// 追加処理は3回まで(それ以上は処理中止の可能性がある)
				{
					// 更新処理
					Update();

					// 描画処理
					Draw();

					dwFrameCount++;
				}
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	timeEndPeriod(1);	// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージ加算合成処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// 入力の初期化
	InitInput(hInstance, hWnd);

	// デバッグ表示の初期化
	InitDebugProcess();

	// フェードの初期化
	InitFade();

	// サウンド初期化
	InitSound(hWnd);

	// タイトルシーンにセット
	SetGameScene(SCENE_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// 入力の終了処理
	UninitInput();

	// デバッグ表示処理の終了処理
	UninitDebugProcess();

	// フェードの終了処理
	UninitFade();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	if(GetKeyboardTrigger(DIK_F3))
	{// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false: true;
	}

	// 入力の更新処理
	UpdateInput();

	switch (g_GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの更新処理
		UpdateTitle();
		break;
	case SCENE_MENU:
		// メニューシーンの更新処理

		break;
	case SCENE_STAGE:
		// ステージ選択シーンの更新処理
		UpdateSelect();

		break;
	case SCENE_TUTORIAL:
		// チュートリアルシーンの更新処理

		break;
	case SCENE_GAME:
		// ゲームシーンの更新
		UpdateGame();
		break;
	case SCENE_RESULT:
		// リザルトシーンの更新処理
		UpdateResult();
		break;
	case SCENE_PAUSE:
		// ポーズシーンの更新処理

		break;
	default:
		break;
	}

	// フェード処理の更新
	UpdateFade();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_GameScene)
		{
		case SCENE_TITLE:
			// タイトルシーンの描画処理
			DrawTitle();
			break;
		case SCENE_MENU:
			// メニューシーンの描画処理
			
			break;
		case SCENE_STAGE:
			// ステージ選択シーンの描画処理
			DrawSelect();
			
			break;
		case SCENE_TUTORIAL:
			// チュートリアルシーンの描画処理

			break;
		case SCENE_GAME:
			// ゲームシーンの描画処理
			DrawGame();
			break;
		case SCENE_RESULT:
			// リザルトの描画処理
			DrawResult();
			break;
		case SCENE_PAUSE:
			// ポーズシーンの描画処理

			break;
		default:
			break;
		}

		// フェード描画
		DrawFade();

#ifdef _DEBUG
		// デバッグ表示の描画処理
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}
#endif

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// ゲームシーンの更新・取得
//=============================================================================
GAMESCENE SetGameScene(GAMESCENE scene)
{
	/* 指定シーンが同じ場合はリターン */
	if (g_GameScene == scene)
	{
		return g_GameScene;
	}

	/* 現在のシーンのお片付け */
	switch (g_GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの終了処理
		UninitTitle();
		break;
	case SCENE_MENU:
		// メニューシーンの終了処理

		break;
	case SCENE_STAGE:
		// ステージ選択シーンの終了処理
		UninitSelect();

		break;
	case SCENE_TUTORIAL:
		// チュートリアルシーンの終了処理

		// ポーズシーンの終了処理

		// カットインシーンの終了処理

		break;
	case SCENE_GAME:
		// ゲームシーンの終了処理

		// ポーズシーンの終了処理

		// カットインシーンの終了処理

		break;
	case SCENE_RESULT:
		// リザルトシーンの終了処理
		UninitResult();
		break;
	case SCENE_PAUSE:
		break;
	default:
		break;
	}

	/* 次のシーンの準備 */
	switch (scene)
	{
	case SCENE_TITLE:
		// タイトルシーンの初期化
		InitTitle(FIRST);

		g_GameScene = SCENE_TITLE;
		break;
	case SCENE_MENU:
		// メニューシーンの初期化

		g_GameScene = SCENE_MENU;
		break;
	case SCENE_STAGE:
		// ステージ選択シーンの初期化
		InitSelect(FIRST);

		g_GameScene = SCENE_STAGE;
		break;
	case SCENE_TUTORIAL:
		// チュートリアルシーンの初期化

		// ポーズシーンの初期化

		g_GameScene = SCENE_TUTORIAL;
		break;
	case SCENE_GAME:
		// ゲームシーンの初期化
		InitGame();

		// ポーズシーンの初期化

		g_GameScene = SCENE_GAME;
		break;
	case SCENE_RESULT:
		// リザルトシーンの初期化
		InitResult(FIRST);

		g_GameScene = SCENE_RESULT;
		break;
	case SCENE_PAUSE:
		g_GameScene = SCENE_PAUSE;
		break;
	default:
		return g_GameScene;
		break;
	}

	g_GameScene = scene;

	return g_GameScene;
}

//=============================================================================
// windowハンドル取得
//=============================================================================
HWND GethWnd(void)
{
	return hWnd;
}
