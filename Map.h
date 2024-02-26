#pragma once
#include "Engine/GameObject.h"
#include<vector>
class Map :public GameObject
{
   int TestMap;
   int TestAirMap;
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

   int  GetModelHandle() { return TestMap; }

  
};
