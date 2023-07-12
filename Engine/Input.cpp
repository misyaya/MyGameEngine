#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };  //�L�[�{�[�h�̐�(200�����邱�Ƃ͂Ȃ��ł���)
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(BYTE)*256);
		pKeyDevice->Acquire(); //���ꂪ�Ȃ��Ƃ��܂ɃL�[��������
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����ĂȂ��āA�O��͉����ĂȂ�
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{
				return true;
		}
		return false;
	}


	void Release()
	{
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}

	//XMVECTOR GetMousePosition()
	//{
	//	return mousePosition;
	//}

	//void SetMousePosition(int x, int y)
	//{
	//	mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	//}
	
}