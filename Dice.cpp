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

	// 頂点情報
	VERTEX vertices[] =
	{
		//1
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f) },	// ダイスの頂点（左上１）0
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },  // ダイスの頂点（右上１）1
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// ダイスの頂点（右下１）2
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f) },   // ダイスの頂点（左下１）3		
		
		//2
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },   // ダイスの頂点（左上２）4
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上２）5
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },  // ダイスの頂点（右下２）6
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,0.5f, 0.0f, 0.0f) },	// ダイスの頂点（左下２）7

		//3
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },   // ダイスの頂点（左上２）8
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上２）9
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },   // ダイスの頂点（右下３）10
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	// ダイスの頂点（左下３）11

		//4
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },// ダイスの頂点（左上４）12
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上４）13
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f) },   // ダイスの頂点（右下４）14
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f) },   // ダイスの頂点（左下４）15
	
		//5
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },   // ダイスの頂点（左上５）16
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f) },   // ダイスの頂点（右上５）17
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f) },   // ダイスの頂点（右下５）18
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// ダイスの頂点（左下５）19

		//6
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// ダイスの頂点（左上６）20
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },   // ダイスの頂点（右上６）21
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f) },   // ダイスの頂点（右下６）22
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	// ダイスの頂点（左下６）23


	};


	// 頂点データ用バッファの設定
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
		//エラー処理
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//インデックス情報
	int index[] = {  0, 2, 3,  0, 1, 2,  7, 4, 5,  7, 5, 6,  8, 9,11,  9,10,11,
					15,12,13, 15,13,14, 18,19,16, 18,16,17, 20,21,22,  20,22,23 }; //2,3,0でも3,0,2でも時計回りならいい

	// インデックスバッファを生成する
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
		//エラー処理
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice__->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(36, 0, 0);
	//int index[] = { 0,2,3, 0,1,2 };６はこれの数
}

void Dice::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
