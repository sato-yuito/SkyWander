#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include"Engine/ImGui/imgui.h"
#include"Sword.h"
#include"Map.h"
#include"Floor.h"
#include"Treasure.h"
#include"json.hpp"

using json = nlohmann::json;

class Player:public GameObject
{ 
    enum class Playeraction
    {
        wait,//何もしていない状態
        walk,//歩く
        jump,//ジャンプ
        attack,//攻撃
    }playerstate_;

    float PlayerSpeed;//プレイヤーの速さ
    float gravity//重力
    float PlayerUP;//ジャンプの上昇量
    XMFLOAT3 PlayerVelocity ;//移動量
    XMFLOAT3 JumpVelocity ;//ジャンプの移動量
    int HP;//体力
    int Attack;//攻撃力
    int playerModelhandle_;    //モデル番号

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

    int GetModelHandle() { return playerModelhandle_; }

    int GetHP() { return HP; }

    int GetAttack() { return Attack; }
};

