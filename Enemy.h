#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class Enemy :public GameObject
{
    int hModel_;    //モデル番号
    
    float movement_;//移動量
   
    XMVECTOR front_;
    
    Player* pPlayer;
    float elaspsedTime_;//経過時間を追跡するための変数
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
    bool IsFindPlayer();

    //プレイヤーを見つけたら追跡
    void ChasePlayer();

    //見つけていない場合の回転移動(5～10秒の間に向きが変わるようにする)
    void EnemySearch();

};

