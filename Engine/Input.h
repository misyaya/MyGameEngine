#pragma once

#include <dInput.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	//�L�[�{�[�h
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	void Release();


	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F������Ă����true
	bool IsMouseButton(int buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonDown(int buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonUp(int buttonCode);

	//�}�E�X�J�[�\���̈ʒu���擾
	//�ߒl�F�}�E�X�J�[�\���̈ʒu
	XMFLOAT3 GetMousePosition();

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	//�����F�}�E�X�J�[�\���̈ʒu
	void SetMousePosition(int x, int y);

	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	//�ߒl�FX,Y �}�E�X�̈ړ��ʁ@�^�@Z,�z�C�[���̉�]��
	XMFLOAT3 GetMouseMove();
};


