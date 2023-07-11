#pragma once

#include <string>
#include <list>
#include "Transform.h"
#include "Direct3D.h"

using std::string;
using std::list;

class GameObject
{
protected:
	list<GameObject*> childList_;
	Transform	transform_;
	GameObject*	pParent_;
	string		objectName_;
	bool IsDead_;
public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release()  = 0;


	void UpdateSub();
	void DrawSub();
	void ReleaseSub();
	
	void KillMe();

	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};