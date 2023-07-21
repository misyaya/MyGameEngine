#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
class Enemy :
	public GameObject
{

	Fbx* pFbx;
	int hModel_;

public:
	//�R���X�g���N�^
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="pTarget">������������</param>
	void OnCollision(GameObject* pTarget) override;
};



