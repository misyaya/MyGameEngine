#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayeScene")
{
}

void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this); //�v���C���[�̐e�́A����(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer); //PlayScene�̎q�Ƃ��āA�v���C���[��o�^

	Instantiate<Player>(this);
}

void PlayScene::Update()
{
	this->transform_.rotate_.y += 1;
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
