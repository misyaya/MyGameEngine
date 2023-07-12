#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr),IsDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name), IsDead_(false)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{
	Release();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{	(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
}

void GameObject::KillMe()
{
	IsDead_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

void GameObject::SetRotate(XMFLOAT3 rotate)
{
	transform_.rotate_ = rotate;
}

void GameObject::SetRotate(float x, float y, float z)
{
	SetRotate(XMFLOAT3(x, y, z));
}

void GameObject::SetScale(XMFLOAT3 scale)
{
	transform_.scale_ = scale;
}

void GameObject::SetScale(float x, float y, float z)
{
	SetScale(XMFLOAT3(x, y, z));
}
