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
	void Initialize();
	//更新
	void Update();
	//描画
	void Drow();
	//解放
	void Release();
};

