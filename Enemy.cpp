#include "Enemy.h"
#include "Player.h"
#include"Map.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent,"Enemy"),hModel_(-1),front_  (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f))
{
	
	movement_ = 0.06f;
	time_ = 10.0f;

	enemyfan = {
		60.0f,
		10.0f,
	};
	
	playerPos  = ((Player*)FindObject("Player"))->GetPosition();
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
	
	if (IsFindPlayer(playerPos))
	{
		//もし見つけているなら追撃する(のちに攻撃するようにしたい）
		ChasePlayer();
	}
	else
	{
		EnemySearch();
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



/// <summary>
/// 視野の範囲にいるかどうか
/// </summary>
bool Enemy::IsFindPlayer(const XMFLOAT3& PlayerPos)
{
	// 向いてる方向に変換
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	frontVec = XMVector3Normalize(frontVec);


	XMVECTOR Playervec = XMLoadFloat3(&playerPos);
	XMVECTOR playerVec = frontVec - Playervec;
	float length = XMVectorGetX(XMVector3Length(playerVec));
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//視野角の範囲内かどうか
	if (InnerProduct > cos(XMConvertToRadians(enemyfan.EnemyDegree / 2.0)))
	
		//中心から扇までの長さより大きいかの判別
		if (length > enemyfan.EnemyLength)
		{
			return false;
		}
	
		return true;
}


/// <summary>
/// 追撃アルゴリズム
/// </summary>
void Enemy::ChasePlayer()
{
	//対象のポジションと自身のポジションをVECTOR型に変換
	XMVECTOR PlayerPos = XMLoadFloat3(&playerPos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//追尾するための方向ベクトルとして使うための計算&正規化
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;
	EnemyChase = XMVector3Normalize(EnemyChase);

	//前方ベクトルを作成しベクトル間の角度計算
	XMVECTOR front_= (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
	float dot = XMVectorGetX(XMVector3Dot(EnemyChase, front_));
	float Eneangle_ = (float) acos(dot);

	//外積を計算しy方向が0より小さい場合角度が反転(プレイヤーが右側か左側の区別がつくようになる)
	XMVECTOR  EnemyCross = XMVector3Cross(front_, EnemyChase);
	if (XMVectorGetY(EnemyCross) < 0)
	{
		Eneangle_ *= -1.0f;
	}

	//ラジアンから度に変換
	transform_.rotate_.y = XMConvertToDegrees(Eneangle_);

	//移動すべき方向が計算されて速さをかけることで動ける
	XMVECTOR MoveEnemy = EnemyChase * movement_;

	//新しい位置を更新するように自身のポジションに格納
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

/// <summary>
/// 10秒に一回向きを変えながら移動する
/// </summary>
void Enemy::EnemySearch()
{
	EnemDirectionChange_ += 0.016f;
	if (EnemDirectionChange_ >= time_)
	{
		transform_.rotate_.y = static_cast<float>(rand() % 360);//ランダムに移動
		EnemDirectionChange_ = 0.0f;
	}
	XMVECTOR MoveEnemy = front_ * movement_;
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}