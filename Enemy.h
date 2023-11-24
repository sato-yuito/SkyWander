#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
class Enemy :public GameObject
{
    int hModel_;    //モデル番号
    float movement_;
    float angle_;
    int time_;
    int timing_;
   
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;


    //視野角の設定
    bool EenmyPOV(XMFLOAT3 PlayerVec);

    //プレイヤーを見つけたら追跡
    void ShowPlayer(Player&player,float speed);
};

