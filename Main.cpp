//インクルード
#include <Windows.h>
#include <stdlib.h>
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/RootJob.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "DirectXCollision.h"
#include "resource.h"
#include "Stage.h"

#pragma comment(lib, "winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* WIN_GAME_NAME = "サンプルゲーム";  //ゲーム名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

RootJob* pRootJob = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

ID3D11Device* pDevice_;		//デバイス
ID3D11DeviceContext* pContext_;		//デバイスコンテキスト
IDXGISwapChain* pSwapChain_;		//スワップチェイン
ID3D11RenderTargetView* pRenderTargetView_;	//レンダーターゲットビュー



//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ 名
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		WIN_GAME_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ = CW_USEDEFAULT）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);
	//ウィンドウを表示
//	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0); //プログラム終了
	}


	/////////// RayCast　テストコード ///////////
	/*Fbx* pFbx = new Fbx;
	pFbx->Load("Assets/BoxBrick.fbx");
	RayCastData data;
	data.start = XMFLOAT4(0, 5, 0, 0);
	data.dir = XMFLOAT4(0, -1, 0, 0);

	pFbx->RayCast(data);
	int a = 6;
	a++;*/
	/////////// RayCast　テストコード ///////////


	//DirectInputの初期化
	Input::Initialize(hWnd);

	Camera::Initialize(winW, winH);

	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();
	

	//ダイアログボックス作成     モードレスダイアログ
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);
	//DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc); モーダルダイアログ

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//メッセージなし
		else
		{
			//デフォだと計測精度が高くないからかく
			timeBeginPeriod(1);

			static DWORD countFps = 0;
			
			//プログラム起動時の時間
			static DWORD startTime = timeGetTime();
			//Windowsが起動してからの時間
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if (nowTime - startTime >= 1000)
			{
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime) * 60 <= 1000)
			{
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;

		
			
			timeEndPeriod(1);

			//ゲームの処理
			//カメラ更新
			Camera::Update();

			//入力情報の更新
			Input::Update();

			//RootJob更新
			pRootJob->UpdateSub();

			//描画
			Direct3D::BeginDraw();

			//ルートジョブから、すべてのオブジェクトのドローを呼ぶ
			pRootJob->DrawSub();

			Direct3D::EndDraw();
			
		}
	}
	
	Model::Release();
	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);
	Input::Release();
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY: //Windowを閉じたら
		PostQuitMessage(0);  //プログラム終了(これ消すとWindowが閉じてもプログラムが動き続ける）
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_NEW:
			OutputDebugString("new FILE");
			break;

		case ID_MENU_OPEN:
			OutputDebugString("open FILE");
			((Stage*)pRootJob->FindObject("Stage"))->Load();
			break;

		case ID_MENU_SAVE:
			OutputDebugString("save FILE");
			((Stage*)pRootJob->FindObject("Stage"))->Save();
			//ファイル保存ダイアログで名前を決める
			//決めたファイル名でセーブ実行
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ダイアログプロシージャ(本体)
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	Stage* pStage = (Stage*)pRootJob->FindObject("Stage");
	return pStage->DialogProc(hDlg, msg, wp, lp);
}