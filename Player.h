#pragma once
#include "Engine/GameObject.h"


class Player:public GameObject
{ 
private:
    enum class Playeraction
    {
        wait,//何もしていない状態
        walk,//歩く
        jump,//ジャンプ
        attack,//攻撃
        fall//落下
    }playerstate_;

    float PlayerSpeed;//プレイヤーの速さ
    
    float gravity;//重力
    
    float PlayerUP;//ジャンプの上昇量
    
    XMFLOAT3 PlayerVelocity ;//移動量
    
    XMFLOAT3 JumpVelocity ;//ジャンプの移動量
    
    int HP;//体力
    
    int Attack;//攻撃力
    
    int playerModelhandle_; //モデル番号

    bool PlayerFalling;//プレイヤーが落下しているかどうか

    float footRayCast;//足元からrayを飛ばすための変数(foot:足元)

    float returnpPosy;//プレイヤーがジャンプして戻る距離
    /// <summary>
    /// 何もしてない状態
    /// </summary>
    void PlayerWait();

    /// <summary>
    /// 歩く
    /// </summary>
    void PlayerWalk();
    
    /// <summary>
    /// ジャンプ
    /// </summary>
    /// <returns></returns>
    void PlayerJump();
    
    /// <summary>
    /// 落下
    /// </summary>
    void PlayerFall();

    /// <summary>
    /// 着地しているかどうか
    /// </summary>
    bool stageDatahit();

    RayCastData PlayerRayCast();
    

    /// <summary>
    /// 攻撃
    /// </summary>
    void PlayerAttack();
    
    /// <summary>
    /// カメラの追尾
    /// </summary>
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

