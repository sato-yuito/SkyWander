#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/SphereCollider.h"
namespace
{
    const float PlayerSpeed = 0.1f;//プレイヤーのスピード
    const float gravity = 0.01f;//プレイヤーの重力
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1),playerstate_(Playeraction::wait),
                                     PlayerOnFloor_(true)
{

}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);
   FindObject("Map");
}

//更新
void Player::Update()
{
    Camera::SetTarget(transform_.position_);
   

    switch (playerstate_)
    {
    case Playeraction::wait:
        PlayerWait();
        break;
    case Playeraction::Walk:
        PlayerWalk();
        break;
    case Playeraction::run:
        PlayerRun();
        break;
    case Playeraction::jump:
        PlayerJump();
        break;
    case Playeraction::attack:
        PlayerAttack();
        break;
    }

    //ジャンプなどをしてマップ上にいない場合
    if (!PlayerOnFloor_){
        transform_.position_.y -= gravity;
        return;
    }
    Collision(FindObject("Map"));
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{

}

void Player::OnCollistion(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Map")
    {
        if (transform_.position_.y <= 0.0f)
        {
            transform_.position_.y = 0.0f;
            PlayerOnFloor_ = true;
        }
       
    }
}

void Player::PlayerWait()
{
    
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
    {
        PlayerWalk();
    }
    if (Input::IsKey(DIK_SPACE))
    {
        PlayerJump();
    }

   
}

void Player::PlayerWalk()
{
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.z+= PlayerSpeed;
    }
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= PlayerSpeed;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += PlayerSpeed;

    }
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= PlayerSpeed;
    }
    //向きを変える処理

}
void Player::PlayerRun()
{

    if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_W)) ||  Input::IsKey(DIK_S))
    {
        // W、A、S、Dのいずれかが押されている場合に走る
        transform_.position_.x = PlayerSpeed * 2;
    }

    else if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_D)) || (Input::IsKey(DIK_A)))
    {
        transform_.position_.z = PlayerSpeed * 2;
    }
}
void Player::PlayerJump()
{
    if (!PlayerOnFloor_)
    {
        return;
    }
    if (Input::IsKey(DIK_SPACE))
    {
        transform_.position_.y += 0.3f;
        PlayerOnFloor_ = false;
    }
    
  
}
void Player::PlayerAttack()
{

}

void Player::UseAitem()
{

}
