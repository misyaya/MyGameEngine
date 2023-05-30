#pragma once
#include "Direct3D.h"
#include <DirectXMath.h> //XM���g�������Ƃ��͂��̓�i����ƇA)�������

using namespace DirectX; //�A

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;   //XMMATRIX = �s��
	
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;   //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};