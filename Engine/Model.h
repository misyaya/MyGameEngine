#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

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
	std::vector<ModelData*>modelList;
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
	void RayCast(int hModel, RayCastData& rayData);

};
