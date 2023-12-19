#pragma once
#include "Engine/GameObject.h"

class Enemy :public GameObject
{
    int hModel_;    //モデル番号
    float movement_;
    float angle_;
    XMVECTOR front_;//向いている方向を表す関数
    XMVECTOR EnemyMove_;//移動量

    struct EnemyFan
    {
        float EnemyDegree;//視野角の範囲（角度）
        float EnemyLength;//中心から扇までの長さ
    } enemyfan;

    
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

private:
    //見つけているか
    bool IsFindPlayer(const XMFLOAT3& PlayerPos);

    //プレイヤーを見つけたら追跡
    void ChasePlayer(XMFLOAT3 playerPos);

    //移動処理
    void EnemyMove();

};

