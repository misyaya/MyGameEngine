#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
class Enemy :
	public GameObject
{

	Fbx* pFbx;
	int hModel_;

public:
	//コンストラクタ
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="pTarget">当たった相手</param>
	void OnCollision(GameObject* pTarget) override;
};



