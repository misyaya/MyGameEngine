#include "Texture.h"
#include"Direct3D.h"

#include<DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

Texture::Texture()
	:pSampler_(nullptr),pSRV_(nullptr)
{
}

Texture::~Texture()
{
	Release();
}

HRESULT Texture::Load(string filename)
{
	using namespace DirectX;

	//画像読み込み部分(変更)
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, filename.c_str(), filename.length());

	TexMetadata metadata;
	ScratchImage image;
	HRESULT hr;
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE,
		&metadata, image);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "画像の読み込みに失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	

	//サンプラーの作成
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pSampler_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "サンプラーの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	//シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice_,
		image.GetImages(),image.GetImageCount(), metadata, &pSRV_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "シェーダーリソースビューの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Texture::Release()
{
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}
