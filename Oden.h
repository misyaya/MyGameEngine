#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

class Oden :
	public GameObject
{
	Fbx* pFbx;
	int hModel_; //���f���ԍ�

public:
	//�R���X�g���N�^
	Oden(GameObject* parent);

	//�f�X�g���N�^
	~Oden();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

