#include "Oden.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"

Oden::Oden(GameObject* parent)
	:GameObject(parent, "Oden"),hModel_(-1)
{
}

Oden::~Oden()
{
}

void Oden::Initialize()
{
	hModel_ = Model::Load("Assets/oden.fbx");
	assert(hModel_ >= 0);

	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;

	//transform_.position_.x = 1.5f;
	//transform_.position_.y = 1.4f;
}

void Oden::Update()
{
	/*if (transform_.rotate_.y++ > 300)
		KillMe();*/
	//transform_.rotate_.y++;

	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;

	if (transform_.position_.z > 50) 
	{
		KillMe();
	}
}

void Oden::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Oden::Release()
{
}

