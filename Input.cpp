#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };  //キーボードの数(200超えることはないでしょ)
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

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
		pKeyDevice->Acquire(); //これがないとたまにキーを見失う
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
		//今は押してて、前回は押してない
		if (keyState[keyCode] && !prevKeyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if (!keyState[keyCode] && prevKeyState[keyCode])
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
}