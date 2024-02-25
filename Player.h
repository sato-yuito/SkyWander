#pragma once
#include "Engine/GameObject.h"

class Player:public GameObject
{ 
    enum class Playeraction
    {
        wait,//何もしていない状態
        walk,//歩く
        jump,//ジャンプ
        attack,//攻撃
        useitem,//アイテムを使う
        walkjump
    }playerstate_;

    int playerModel;    //モデル番号

    //何もしていない状態
    void PlayerWait();

    //歩く
    void PlayerWalk();
    
    //ジャンプ
    void PlayerJump();
    
    //攻撃
    void PlayerAttack();
    
    //アイテムを使う
    void Useitem();

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
    
    int GetModelHandle() { return hModel_; }
};

