#pragma once
#include "Engine/GameObject.h"
#include"json.hpp"
#include<fstream>

using json = nlohmann::json;

class Player:public GameObject
{ 

    enum class Playeraction
    {
        wait,//何もしていない状態
        walk,//歩く
        jump,//ジャンプ
        attack,//攻撃
        fall//落下
    }playerstate_;

    int playerModel;    //モデル番号

    

    //何もしていない状態
    void PlayerWait();

    //歩く
    void PlayerWalk();
    
    //ジャンプ
    void PlayerJump();
    
    //ステージに着地しているかどうか
    bool stageDatahit();

    //攻撃
    void PlayerAttack();
    
    //プレイヤーの後ろを常に追尾してくれるようにする
    void PlayerCamTarget();

    void PlayerFall();//プレイヤーの落下処理

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    
    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    int GetModelHandle() { return playerModel; }
};

