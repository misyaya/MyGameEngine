#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//���f�����
	struct ModelData
	{
		//FBX��
		Fbx* pfbx_;
		Transform transform_; //�g�����X�t�H�[��
		std::string filename_; //�t�@�C����
	};


	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*>modelList;
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
	void RayCast(int hModel, RayCastData& rayData);

};
