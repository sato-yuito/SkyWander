#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
#include"Map.h"
 

class Enemy :public GameObject
{
    int hModel_;    //モデル番号
    float movement_;
    float angle_;
    Map* map;
   

    struct EnemyFan
    {
        XMVECTOR EnemyPosition;//中心座標
        float EnemyDegree;//視野角の範囲（角度）
        float EnemyLength;//中心から扇までの長さ
        float DirectionDegree;//扇の方向を決めるために必要なもの

    } enemyfan;

    //視野角の範囲を入れるためのセッター
    void SetEnemyDegree(float degree)
    {
        enemyfan.EnemyDegree = degree;
    }
    
   
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
    bool EnemyPOV(const XMFLOAT3& PlayerVec);

    

    //プレイヤーを見つけたら追跡
    void ShowPlayer(Player&player,float speed);
};

