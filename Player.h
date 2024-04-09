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
        useitem,//アイテムを使う
        walkjump
    }playerstate_;

    int playerModel;    //モデル番号

    int HP = 0;//体力

    int Attack = 0;//攻撃力

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

    //プレイヤーの後ろを常に追尾してくれるようにする
    void PlayerCamTarget();

    //jsonファイルをLoad
    void Load();

    //jsonファイルをセーブ
    void Save();
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

