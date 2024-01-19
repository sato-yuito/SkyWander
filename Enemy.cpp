#include "Enemy.h"

#include"Map.h"
#include "Engine/Model.h"

namespace {
	const int LastTime = 10;//向きを変えたるための時間(秒)
}

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1), front_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),pPlayer(nullptr)
{

	movement_ = 0.06f;

	enemyfan.EnemyDegree = cos(XMConvertToRadians(60.0 / 2.0));
	enemyfan.EnemyLength = 10.0f;
	
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
	
	pPlayer = (Player*)FindObject("Player");
}

void Enemy::Update()
{
	
	if (IsFindPlayer())
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
bool Enemy::IsFindPlayer()
{
	XMFLOAT3 playerPos = pPlayer->GetPosition();
	//自身のポジションを入れる変数
	XMVECTOR EnemPos = XMLoadFloat3(&transform_.position_);

	// 向いてる方向に対する回転行列
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//敵の前方ベクトルをmatRYで回転させる
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	//正規化
	frontVec = XMVector3Normalize(frontVec);

	//プレイヤーの位置を表すベクトル
	XMVECTOR Playervec = XMLoadFloat3(&playerPos);

	XMVECTOR playerVec = Playervec - EnemPos;
	float length = XMVectorGetX(XMVector3Length(playerVec));
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));
	
	//視野角の範囲内かどうか
	if (InnerProduct >enemyfan.EnemyDegree)
		return false;

	//中心から扇までの長さより大きいかの判別
	if (length > enemyfan.EnemyLength)
		return false;

	return true;
}


/// <summary>
/// 追撃アルゴリズム
/// </summary>
void Enemy::ChasePlayer()
{
	XMFLOAT3 playerpos = pPlayer->GetPosition();
	//対象のポジションと自身のポジションをVECTOR型に変換
	XMVECTOR PlayerPos = XMLoadFloat3(&playerpos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//追尾するための方向ベクトルとして使うための計算
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;

	//敵キャラクターがプレイヤーを追いかけるときにプレイヤーが向いている方向に向けさせるための処理
	double enemtan= atan2(XMVectorGetX(-EnemyChase),XMVectorGetZ(-EnemyChase));
	
	//ラジアンから度に変換
	transform_.rotate_.y = XMConvertToDegrees(enemtan);

	// プレイヤーに向かって進む方向ベクトルを生成
	XMVECTOR moveDirection = XMVector3Normalize(EnemyChase);

	//移動ベクトル計算
	XMVECTOR MoveEnemy = moveDirection * movement_;
	
	
	//新しい位置を更新するように自身のポジションに格納
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

/// <summary>
/// 10秒に一回向きを変えながら移動する
/// </summary>
void Enemy::EnemySearch()
{
	if (LastTime)
	{
		transform_.rotate_.y = (rand() % 360);
	}
}