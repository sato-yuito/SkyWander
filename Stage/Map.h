#pragma once
#include "../Engine/GameObject.h"
#include<vector>
#include"Floor.h"

class Map :public GameObject
{
    std::vector<Floor*>floorData;
    
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

    std::vector<Floor*>GetfloorData() { return floorData; }
  
};
