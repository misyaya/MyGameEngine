#include "Oden.h"
#include "Engine/Fbx.h"

Oden::Oden(GameObject* parent)
	:GameObject(parent, "Oden"), pFbx(nullptr)
{
}

Oden::~Oden()
{
}

void Oden::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.2;
	this->transform_.scale_.y = 0.2;
	this->transform_.scale_.z = 0.2;
	this->transform_.position_.x = 1.5f;
	this->transform_.position_.y = 1.4f;
}

void Oden::Update()
{
	if (transform_.rotate_.y++ > 300)
		KillMe();
	//transform_.rotate_.y++;
}

void Oden::Draw()
{
	pFbx->Draw(transform_);
}

void Oden::Release()
{
	pFbx->Release();
	delete pFbx;
}

