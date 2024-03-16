#pragma once
#include<vector>
#include"Engine/GameObject.h"
class Floor:public GameObject
{
	
	int floorModel_;

public:
	Floor(GameObject* parent);

	//デストラクタ
	~Floor();

	//初期化
	void Initialize() override;

	//更新
	void Update()override;

	//モデル表示
	void Draw() override;

	//開放
	void Release() override;

	//モデル番号の取得
	int GetModelHandle() { return floorModel_; }
};

