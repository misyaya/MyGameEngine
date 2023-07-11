#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr),IsDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(nullptr), IsDead_(false)
{
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
