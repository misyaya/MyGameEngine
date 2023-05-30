#pragma once
#include "Direct3D.h"
#include <DirectXMath.h> //XMを使いたいときはこの二つ（これと②)をいれる

using namespace DirectX; //②

//コンスタントバッファー

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;   //XMMATRIX = 行列
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;   //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};