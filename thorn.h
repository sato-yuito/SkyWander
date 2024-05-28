#pragma once
#include"Engine/GameObject.h"
class thorn:public GameObject
{
	int thornHandle_;

public:
	thorn(GameObject* parent);

	//デストラクタ
	~thorn();

	//初期化
	void Initialize() override;

	//更新
	void Update()override;

	//モデル表示
	void Draw() override;

	//開放
	void Release() override;

	
};

