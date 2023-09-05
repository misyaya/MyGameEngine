#include "Input.h"
#include <string>

namespace Input
{
	//�L�[�{�[�h
	LPDIRECTINPUT8   pDInput_ = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr;
	BYTE keyState[256] = { 0 };  //�L�[�{�[�h�̐�(200�����邱�Ƃ͂Ȃ��ł���)
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8 pMouseDevice_; //�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_; //�}�E�X�̏��
	DIMOUSESTATE prevMouseState;//�O�t���[���̃}�E�X�̏��
	XMFLOAT3 mousePosition_;							//�}�E�X�J�[�\���̈ʒu

	void Initialize(HWND hWnd)
	{
		//�L�[�{�[�h
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		//�L�[�{�[�h
		memcpy(prevKeyState,keyState,sizeof(BYTE)*256);
		pKeyDevice_->Acquire(); //���ꂪ�Ȃ��Ƃ��܂ɃL�[��������
		pKeyDevice_->GetDeviceState(sizeof(keyState), &keyState);

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
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
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
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
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}


	//////////�@�@�}�E�X�@�@//////////
	bool IsMouseButton(int buttonCode)
	{
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		if (IsMouseButton(buttonCode) && !(prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && (prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	XMFLOAT3 GetMousePosition()
	{
		return mousePosition_;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition_.x = x;
		mousePosition_.y = y;
		std::string resStr = std::to_string(x) + "." + std::to_string(y) + "\n";
		OutputDebugString(resStr.c_str());
	}

	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX,
								   (float)mouseState_.lY,
								   (float)mouseState_.lZ);
		return result;
	}

	
}