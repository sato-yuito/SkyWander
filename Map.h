#pragma once
#include "Engine/GameObject.h"
#include<vector>
class Map :public GameObject
{
    std::vector<int> models;
  
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

   std::vector<int> GetModelHandles() { return models ; }

  
};
