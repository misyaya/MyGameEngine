//�C���N���[�h
#include <Windows.h>
#include "Direct3D.h"
//#include "Quad.h"
#include"Camera.h"
#include "Dice.h"
#include "Sprite.h"
#include"Fbx.h"
#include"Input.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const char* WIN_GAME_NAME = "�T���v���Q�[��";  //�Q�[����
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���


//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ID3D11Device* pDevice_;		//�f�o�C�X
ID3D11DeviceContext* pContext_;		//�f�o�C�X�R���e�L�X�g
IDXGISwapChain* pSwapChain_;		//�X���b�v�`�F�C��
ID3D11RenderTargetView* pRenderTargetView_;	//�����_�[�^�[�Q�b�g�r���[



//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W�� ��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		WIN_GAME_NAME,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂��� = CW_USEDEFAULT�j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);
	//�E�B���h�E��\��
//	ShowWindow(hWnd, nCmdShow);

	//Direct3D������
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0); //�v���O�����I��
	}

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	Camera::Initialize(winW, winH);


	//Quad* pQuad = new Quad;
	//hr = pQuad->Initialize();
	//Dice* pDice = new Dice;
	//hr = pDice->Initialize();
	//Sprite* pSprite = new Sprite;
	//hr = pSprite->Initialize();
	Fbx* pFbx = new Fbx;
	pFbx->Load("Assets/Oden.fbx");
	
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "Quad�̌Ăяo���Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0); //�v���O�����I��
	}

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (Input::IsKey(DIK_ESCAPE))
			{
				PostQuitMessage(0);
			}

		}

		//���b�Z�[�W�Ȃ�
		else
		{
			//�J�����X�V
			Camera::Update();

			//�Q�[���̏���
			Direct3D::BeginDraw();

			//���͏��̍X�V
			Input::Update();

			static float angle = 0;
			angle += 0.05;

			
			//�`�揈��
			
				/*XMMATRIX matR = XMMatrixRotationY(XMConvertToRadians(45));
				XMMATRIX matT = XMMatrixTranslation(0, 0, 0);
				XMMATRIX matT2 = XMMatrixTranslation(0, 0, 0);
				XMMATRIX matT3 = XMMatrixTranslation(3,3,3)*XMMatrixScaling(0.2, 0.2, 0.2);
				XMMATRIX matS = XMMatrixScaling(0.2, 0.2, 0.2);*/

				//static float a = 0;
				//a += 0.01;

					//XMMATRIX mat = matT * mats;
					//XMMATRIX mat = matT * matR * matS;
					//XMMATRIX mat = matS * XMMatrixRotationZ(XMConvertToRadians(170)) * XMMatrixTranslation(3, 0, 0);
					//XMMATRIX mat = XMMatrixRotationZ(XMConvertToRadians(a));
					//XMMATRIX mat = XMMatrixRotationZ(XMConvertToRadians(a)) * matS;
					//XMMATRIX mat = matS * XMMatrixRotationZ(XMConvertToRadians(a));


				//XMMATRIX mat = XMMatrixScaling(2.0, 2.0, 2.0) * XMMatrixRotationY(XMConvertToRadians(a));
				//XMMATRIX mat =  XMMatrixRotationY(XMConvertToRadians(a))* XMMatrixRotationZ(XMConvertToRadians(a));
				
			
			Transform diceTransform;
			diceTransform.position_.y = 3.0f;
			diceTransform.rotate_.y = angle;
			

			Transform spriteTransform;
			spriteTransform.scale_.x = 512.0f / 800.0f;
			spriteTransform.scale_.y = 256.0f / 600.0f;

			Transform fbxTransform;
			fbxTransform.position_.y = 0.0f;
			fbxTransform.rotate_.y = angle;

			//pQuad->Draw(mat);
			//pDice->Draw(diceTransform);
			//pSprite->Draw(spriteTransform);
			pFbx->Draw(fbxTransform);

			
			Direct3D::EndDraw();
			
			
			
		}
	}
	//�������

	//SAFE_RELEASE(pQuad);
	//SAFE_RELEASE(pDice);
	//SAFE_RELEASE(pSprite);
	SAFE_RELEASE(pFbx);

	//SAFE_DELETE(pQuad);
	//SAFE_DELETE(pDice);
	//SAFE_DELETE(pSprite);
	SAFE_DELETE(pFbx);

	Input::Release();
	Direct3D::Release();
	
	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: //Window�������
		PostQuitMessage(0);  //�v���O�����I��(���������Window�����Ă��v���O����������������j
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

