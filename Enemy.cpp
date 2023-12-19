#include "Enemy.h"
#include "Player.h"
#include"Map.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent,"Enemy"),hModel_(-1),front_(XMVectorSet(0.0f,0.0f,-1.0f,0.0f))
{
	XMFLOAT3 movement_{ 0.0f,0.0f,0.15f };
	EnemyMove_ = XMLoadFloat3(&movement_);

	enemyfan = {
		60.0f,
		20.0f,
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
		// 見つけていないなら向きを変えながら移動
		EnemyMove();
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

	//対象のポジションから自身のポジションを引いてベクトルを求めて正規化
	XMVECTOR playerVec = XMLoadFloat3(&PlayerPos) - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = cos(XMVectorGetX((XMVector3Dot(playerVec, frontVec))));

	//距離と視野内だったらの判定
   if (InnerProduct > enemyfan.EnemyDegree / 2.0)return false;
   


	   float length = XMVectorGetX(XMVector3Length(playerVec));

	   if (length > enemyfan.EnemyLength) 
	   
		   return false;
	   
	   return true;
   

}


/// <summary>
/// 追撃アルゴリズム
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos)
{
	//ヒント
	//目的の方向に向かうとき、滑らかに向きを変える場合は、
	//自分の右向きのベクトルと、自分から対象へのベクトルとで内積を取り、＞０であれば対象は右側に、＜０であれば対象は左側にいます。
	//その方向に、自分の向きを変えれば、だんだん対象の方を向くようになります。
    

	//右ベクトル
	XMMATRIX RightEnemyVec = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.y+90.0f));
	XMVECTOR RightVec = XMVector3Normalize(XMVector3TransformCoord(front_, RightEnemyVec));
	
    //プレイヤーとのベクトル
	XMVECTOR EnemyVec = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&playerPos);
	EnemyVec = XMVector3Normalize(EnemyVec);


	float EnemyRad = XMVectorGetX(XMVector3Dot(front_, XMVector3Normalize(EnemyVec)));

	if (EnemyRad > 0)
	{
		transform_.rotate_.y += 0.5f;
	}
	else
	{
		transform_.rotate_.y -= 0.5f;
	}

	
	
	
}

/// <summary>
/// 移動処理(そのうちある程度の時間がったら方向転換するようにしたい)
/// </summary>
void Enemy::EnemyMove()
{
	
	

}