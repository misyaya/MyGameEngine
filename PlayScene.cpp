#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayeScene")
{
}

void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this); //プレイヤーの親は、自分(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer); //PlaySceneの子として、プレイヤーを登録

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	//this->transform_.rotate_.y += 1;
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
