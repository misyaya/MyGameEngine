#pragma once
#include <DirectXMath.h> //XMを使いたいときはこの二つ（これと②)をいれる
#include "Direct3D.h"
#include "Texture.h"
#include <vector>

using namespace DirectX; //②

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;   //XMMATRIX = 行列
	XMMATRIX	matW;
	
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};


class Quad
{
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報


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

/*
private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();
	*/
};