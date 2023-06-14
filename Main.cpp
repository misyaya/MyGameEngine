//インクルード
#include <Windows.h>
#include "Direct3D.h"
//#include "Quad.h"
#include"Camera.h"
#include "Dice.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* WIN_GAME_NAME = "サンプルゲーム";  //ゲーム名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ


//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ID3D11Device* pDevice__;		//デバイス
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
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
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

	Camera::Initialize(winW, winH);


	//Quad* pQuad = new Quad;
	//hr = pQuad->Initialize();
	Dice* pDice = new Dice;
	hr = pDice->Initialize();
	
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "Quadの呼び出しに失敗しました", "エラー", MB_OK);
		PostQuitMessage(0); //プログラム終了
	}

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
			//カメラ更新
			Camera::Update();

			//ゲームの処理
			Direct3D::BeginDraw();
			
			//描画処理
			XMMATRIX matR = XMMatrixRotationY(XMConvertToRadians(45));
			XMMATRIX matT = XMMatrixTranslation(0, 0, 0);
			XMMATRIX matS = XMMatrixScaling(1, 3, 1);
			//XMMATRIX mat = matT * mats;
			//XMMATRIX mat = matT * matR * matS;
			//XMMATRIX mat = matS * XMMatrixRotationZ(XMConvertToRadians(170)) * XMMatrixTranslation(3, 0, 0);
			
			static float a = 0;
			a += 0.01;

			//XMMATRIX mat = XMMatrixRotationZ(XMConvertToRadians(a));
			//XMMATRIX mat = XMMatrixRotationZ(XMConvertToRadians(a)) * matS;
			//XMMATRIX mat = matS * XMMatrixRotationZ(XMConvertToRadians(a));
			XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(a));
			//XMMATRIX mat =  XMMatrixRotationY(XMConvertToRadians(a))* XMMatrixRotationZ(XMConvertToRadians(a));
			//pQuad->Draw(mat);
			pDice->Draw(mat);
			Direct3D::EndDraw();
			
			
		}
	}
	//解放処理
	Direct3D::Release();
	//SAFE_RELEASE(pQuad);
	SAFE_RELEASE(pDice);

	//SAFE_DELETE(pQuad);
	SAFE_DELETE(pDice);
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: //Windowを閉じたら
		PostQuitMessage(0);  //プログラム終了(これ消すとWindowが閉じてもプログラムが動き続ける）
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

