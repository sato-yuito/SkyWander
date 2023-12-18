#include "Enemy.h"
#include "Player.h"
#include"Map.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent,"Enemy"),hModel_(-1),movement_(0.15f)
{
	enemyfan = {
		XMLoadFloat3(&transform_.position_),
		60.0f,
		20.0f,
		transform_.rotate_.y
	};
	map_ = (Map*)FindObject("Map");
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
		//見つけている
		ChasePlayer(playerPos, 0.1f);
	}
	else
	{
		// 見つけていない

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
/// 見つけているか
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


	//向いている方向を表すやつ
	XMVECTOR front = XMVectorSet(0, 0, -1, 0);

	// 向いてる方向に変換
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front, matRY);
	frontVec = XMVector3Normalize(frontVec);

	//
	XMVECTOR playerVec = XMLoadFloat3(&PlayerPos) - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	return InnerProduct > enemyfan.EnemyDegree;

}


/// <summary>
/// 追撃アルゴリズムの実装
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos, float speed)
{
	//目的の方向に向かうとき、滑らかに向きを変える場合は、
	//自分の右向きのベクトルと、自分から対象へのベクトルとで内積を取り、＞０であれば対象は右側に、＜０であれば対象は左側にいます。
	//その方向に、自分の向きを変えれば、だんだん対象の方を向くようになります。

	XM


}
