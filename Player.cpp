#include "Player.h"
#include "Engine/Fbx.h"
#include "Oden.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;

	Instantiate<Oden>(this);
	GameObject *pCO2 =Instantiate<Oden>(this);
	pCO2->SetPosition(-1.5f,1.4f,0.0f);
}

void Player::Update()
{
	transform_.rotate_.y++;
	if (transform_.rotate_.y > 600)
		KillMe();

	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.5f;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.5f;
	}
	//KillMe();
}

void Player::Draw()
{
	pFbx->Draw(transform_);
}

void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}
