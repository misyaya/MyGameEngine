#pragma once
#include <DirectXMath.h> //XM���g�������Ƃ��͂��̓�i����ƇA)�������
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX; //�A

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;   //XMMATRIX = �s��

};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};


class Dice
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;   //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;

public:
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};