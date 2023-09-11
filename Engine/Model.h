#pragma once
#include <string>
#include "Fbx.h"

//-----------------------------------------------------------
//3Dモデル（FBXファイル）を管理する
//-----------------------------------------------------------
namespace Model
{
	//モデル情報
	struct ModelData
	{
		//FBX名
		Fbx* pfbx_;
		Transform transform_; //トランスフォーム
		std::string filename_; //ファイル名
	};


	//モデルのポインタをぶち込んでおくベクタ
	
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
	void RayCast(int hModel, RayCastData& rayData);

};
