#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
class Sword:public GameObject
{
private:
	int swordModelHandle_;
public:
	//コンストラクタ
	Sword(GameObject* parent);
	//デストラクタ
	~Sword();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//解放
	void Release() override;
};

