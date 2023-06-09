#include "Dice.h"
#include "Camera.h"


Dice::Dice() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	HRESULT hr;

	// ���_���
	VERTEX vertices[] =
	{
		//1
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i����P�j0
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },  // �_�C�X�̒��_�i�E��P�j1
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E���P�j2
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�����P�j3		
		
		//2
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i����Q�j4
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��Q�j5
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },  // �_�C�X�̒��_�i�E���Q�j6
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,0.5f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����Q�j7

		//3
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i����Q�j8
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��Q�j9
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���R�j10
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����R�j11

		//4
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },// �_�C�X�̒��_�i����S�j12
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��S�j13
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���S�j14
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�����S�j15
	
		//5
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i����T�j16
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E��T�j17
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���T�j18
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����T�j19

		//6
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i����U�j20
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E��U�j21
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���U�j22
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����U�j23


	};


	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice__->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	//�C���f�b�N�X���
	int index[] = {  0, 2, 3,  0, 1, 2,  7, 4, 5,  7, 5, 6,  8, 9,11,  9,10,11,
					15,12,13, 15,13,14, 18,19,16, 18,16,17, 20,21,22,  20,22,23 }; //2,3,0�ł�3,0,2�ł����v���Ȃ炢��

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice__->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice__->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//�R���X�^���g�o�b�t�@�ɓn�����
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext_->DrawIndexed(36, 0, 0);
	//int index[] = { 0,2,3, 0,1,2 };�U�͂���̐�
}

void Dice::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
