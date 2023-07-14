#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Fbx;

class Oden :
	public GameObject
{
	Fbx* pFbx;
	int hModel_; //モデル番号

public:
	//コンストラクタ
	Oden(GameObject* parent);

	//デストラクタ
	~Oden();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

