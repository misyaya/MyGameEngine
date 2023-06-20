#include "Sprite.h"
#include "Sprite.h"
#include "Camera.h"


Sprite::Sprite() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Sprite::~Sprite()
{
}

HRESULT Sprite::Initialize()
{
	HRESULT hr;

	// 頂点情報
	VERTEX vertices[] =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},  // 四角形の頂点（右上）
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下）
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},   // 四角形の頂点（左下）		

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
	int index[] = { 0,2,3, 0,1,2 }; //2,3,0でも3,0,2でも時計回りならいい

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

void Sprite::Draw(XMMATRIX& worldMatrix)
{

	Direct3D::SetShader(SHADER_2D);

	PassDataToCB(worldMatrix);

	SetBufferToPipeLine();

	Direct3D::pContext_->DrawIndexed(indexNum, 0, 0);
	////コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列

	//CONSTANT_BUFFER cb;
	//cb.matWVP = XMMatrixTranspose(view * proj);

	//D3D11_MAPPED_SUBRESOURCE pdata;
	//Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	//Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	//Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	//ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	//Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	////頂点バッファ
	//UINT stride = sizeof(VERTEX);
	//UINT offset = 0;
	//Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//// インデックスバッファーをセット
	//stride = sizeof(int);
	//offset = 0;
	//Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	////コンスタントバッファ
	//Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	//Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//Direct3D::pContext_->DrawIndexed(6, 0, 0);
	////int index[] = { 0,2,3, 0,1,2 };６はこれの数
}

void Sprite::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

void Sprite::InitVertexData()
{
}

HRESULT Sprite::CreateVertexBuffer()
{
	return E_NOTIMPL;
}

void Sprite::InitIndexData()
{
}

HRESULT Sprite::CreateIndexBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::CreeateConstantBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::LoadTexture()
{
	return E_NOTIMPL;
}

void Sprite::PassDataToCB(DirectX::XMMATRIX& worldMatrix)
{
}

void Sprite::SetBufferToPipeLine()
{
}
