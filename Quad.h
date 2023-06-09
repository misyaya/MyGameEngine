#pragma once
#include <DirectXMath.h> //XMを使いたいときはこの二つ（これと②)をいれる
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX; //②

//コンスタントバッファー

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;   //XMMATRIX = 行列
	
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};


class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;   //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};