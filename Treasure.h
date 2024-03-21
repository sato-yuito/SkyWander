#pragma once
#include"Engine/GameObject.h"
class Treasure:public GameObject
{
	int treasureModel_;
public:
	Treasure(GameObject*parent);

	~Treasure();
	//初期化
	void Initialize() override;

	//更新
	void Update()override;

	//モデル表示
	void Draw() override;

	//開放
	void Release() override;

	//モデル番号を取得
	int GetModelHandle() { return treasureModel_; }
};

