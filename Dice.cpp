#include "Dice.h"


//頂点情報の準備
void Dice::InitVertexData()
{
	// 頂点情報
	vertices_ =
	{
		//1
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },	// ダイスの頂点（左上１）0
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },  // ダイスの頂点（右上１）1
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },	// ダイスの頂点（右下１）2
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },   // ダイスの頂点（左下１）3		

		//2
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   // ダイスの頂点（左上２）4
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上２）5
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},  // ダイスの頂点（右下２）6
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// ダイスの頂点（左下２）7

		//3
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // ダイスの頂点（左上２）8
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上２）9
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // ダイスの頂点（右下３）10
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// ダイスの頂点（左下３）11

		//4
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f) },// ダイスの頂点（左上４）12
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f) },	// ダイスの頂点（右上４）13
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f) },   // ダイスの頂点（右下４）14
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // ダイスの頂点（左下４）15

		//5
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f) },   // ダイスの頂点（左上５）16
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // ダイスの頂点（右上５）17
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f) },   // ダイスの頂点（右下５）18
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f) },	// ダイスの頂点（左下５）19

		//6
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f) },	// ダイスの頂点（左上６）20
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f) },   // ダイスの頂点（右上６）21
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // ダイスの頂点（右下６）22
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f) },	// ダイスの頂点（左下６）23


	};
	
	//頂点の数
	vertexNum_ = vertices_.size();

}


//インデックス情報を準備
void Dice::InitIndexData()
{
	//インデックス情報
	index_ = { 0, 2, 3,  0, 1, 2,  7, 4, 5,  7, 5, 6,  8, 9,11,  9,10,11,
					15,12,13, 15,13,14, 18,19,16, 18,16,17, 20,21,22,  20,22,23 }; //2,3,0でも3,0,2でも時計回りならいい

	//インデックス数
	indexNum_ = index_.size();
}