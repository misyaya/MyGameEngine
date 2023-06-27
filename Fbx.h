#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Texture;  //前方宣言

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture; //これがポインタだからincludeじゃなくて前方宣言でいい
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};


	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数


	ID3D11Buffer* pVertexBuffer_;      //頂点バッファ
	ID3D11Buffer* pIndexBuffer_;       //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;    //コンスタントバッファ
	MATERIAL* pMaterialList_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void Release();
};