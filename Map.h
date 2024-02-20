
#pragma once
#include "Engine/GameObject.h"

class Map :public GameObject
{
    int hModel_;    //モデル番号
    int TestModel_;//テストモデル表示

    Transform TestModelPos;
public:
    //コンストラクタ
    Map(GameObject* parent);

    //デストラクタ
    ~Map();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    int GetModelHandle() { return hModel_; }
};
