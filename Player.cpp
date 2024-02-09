#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include"Map.h"

namespace
{
	const float PlayerSpeed = 0.1f;//プレイヤーのスピード
	const float gravity = 0.01f;//プレイヤーの重力
	const float PlayerInitialSpeed = 0.05f;//ジャンプの初速度
	const float JumpHeight = 2.0f;//ジャンプをした時の最高到達地点
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), playerstate_(Playeraction::wait)						 
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
	
	RayCastData data;
	data.start = transform_.position_;

	data.dir = XMFLOAT3(0, -1, 0);
	 
	Model::RayCast(((Map*)FindObject("Map"))->GetModelHandle(), &data);
	//ジャンプなどをしてマップ上にいない場合
   if (data.hit)
	{
		if(data.dist > 0.5f)
		{ 
			transform_.position_.y -= gravity;
			
		}
	}
  
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


void Player::PlayerWait()
{
	
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
	{
		playerstate_ = Playeraction::Walk;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		playerstate_  = Playeraction::jump;
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

}
void Player::PlayerRun()
{

	if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_W)) ||  Input::IsKey(DIK_S))
	{
		transform_.position_.x = PlayerSpeed * 2;
	}

	else if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_D)) || (Input::IsKey(DIK_A)))
	{
		transform_.position_.z = PlayerSpeed * 2;
	}

	
}

bool PlayerLower = false;//プレイヤーが一定の高さに到達したかどうか
void Player::PlayerJump()
{
	
	//プレイヤーの位置が最高到達地点より高かったら
	if (transform_.position_.y >= JumpHeight )
	{
		PlayerLower = true;

	}
	//最高地点に到達していない間
	if (PlayerLower == false)
	{
		transform_.position_.y += PlayerInitialSpeed;
	}
	if (JumpHeight)
	{
		playerstate_ = Playeraction::Walk;
	}
}


void Player::PlayerAttack()
{

}

void Player::UseAitem()
{

}