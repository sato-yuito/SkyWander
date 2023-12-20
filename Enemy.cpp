#include "Enemy.h"
#include "Player.h"
#include"Map.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent,"Enemy"),hModel_(-1),front_  (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f))
{
	
	movement_ = 0.06f;
	

	enemyfan = {
		15.0f,
		10.0f,
	};
	
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = (float)(rand() % 401 - 200) / 10;
	transform_.position_.z = 20.0f;
}

void Enemy::Update()
{
	XMFLOAT3 playerPos = ((Player*)FindObject("Player"))->GetPosition();
	
	if (IsFindPlayer(playerPos))
	{
		//もし見つけているなら追撃する
		
		ChasePlayer(playerPos);
	}
	else
	{
		
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}



// <summary>
/// 視野の範囲にいるかどうか
/// </summary>
bool Enemy::IsFindPlayer(const XMFLOAT3& PlayerPos)
{
	//ヒント(視野角判定)
	/*
		視野内にいるかを判別するには、
		自分の向いてる向きのベクトル（長さ１）と、自分から対象へのベクトル
		（長さ１）で内積を取ると、cosΘが手に入ります。視野角が60°であれば、これがcos(60°)よりも大きければ、
		視野内にいます。
	*/
	
	// 向いてる方向に変換
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	frontVec = XMVector3Normalize(frontVec);

	
	XMVECTOR playerVec = frontVec - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//距離と視野内だったらの判定
	if (InnerProduct > enemyfan.EnemyDegree / 2.0)
	
		return false;
	


	   float length = XMVectorGetX(XMVector3Length(playerVec));

	   if (length > enemyfan.EnemyLength)

		   return true;
	   
	   
   
	  


}


/// <summary>
/// 追撃アルゴリズム
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos)
{


	XMVECTOR PlayerPos = XMLoadFloat3(&playerPos);
	XMVECTOR EnemyPositon = XMLoadFloat3(&transform_.position_);
	XMVECTOR EnemyChase = PlayerPos - EnemyPositon;
	EnemyChase = XMVector3Normalize(EnemyChase);
	XMVECTOR front_= (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
	float dot = XMVectorGetX(XMVector3Dot(EnemyChase, front_));
	float Eneangle_ = (float) acos(dot);
	XMVECTOR  EnemyCross = XMVector3Cross(front_, EnemyChase);
	if (XMVectorGetY(EnemyCross) < 0)
	{
		Eneangle_ *= -1.0f;
	}
	transform_.rotate_.y = XMConvertToDegrees(Eneangle_);

	XMVECTOR MoveEnemy = EnemyChase * movement_;
	XMStoreFloat3(&transform_.position_, EnemyPositon + MoveEnemy);

}

