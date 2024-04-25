#include "Enemy.h"

namespace {
	const int LastTime = 10;//向きを変えたるための時間(秒)
	float minX = -4.0f;//x座標の最小行動範囲
	float maxX = 4.0f;//x座標の最大行動範囲
	float minZ = -4.0f;//z座標の最小行動範囲
	float maxZ = 4.0f;//z座標の最大行動範囲
}

Enemy::Enemy(GameObject* parent)
	: EnemyBase(parent, EnemyName), hModel_(-1)
{
	
}

Enemy::~Enemy()
{
	
}

void Enemy::Initialize()
{
	EnemyBase::Initialize();

	movement_ = 0.02f;

	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	

	
	pPlayer = (Player*)FindObject("Player");
}

void Enemy::Update()
{
	if (EnemyBase::IsFindPlayer()){
		//もし見つけているなら追撃する(のちに攻撃するようにしたい）
		ChasePlayer();
	}
	else{
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


void Enemy::ChasePlayer()
{
	XMFLOAT3 playerpos = pPlayer->GetPosition();
	playerpos.y = 0;
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
	elaspsedTime_ += 0.016f; // 経過時間の設定(毎フレーム加算)

	// 指定した時間以上になったときにランダムに回転をしてリセットする
	if (elaspsedTime_ >= LastTime)
	{
		transform_.rotate_.y = static_cast<float>(rand() % 360);
		elaspsedTime_ = 0.0f;
	}

	// 現在の回転に基づいて移動ベクトルを計算
	XMVECTOR moveDirection = XMVectorSet(sinf(XMConvertToRadians(transform_.rotate_.y)),
		0.0f,
		cosf(XMConvertToRadians(transform_.rotate_.y)),
		0.0f);

	//正規化
	moveDirection = XMVector3Normalize(moveDirection);

	// 新しい位置を計算
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	XMVECTOR MoveEnemy = moveDirection * movement_;

	// 新しい位置を適用
	XMVECTOR NewPosition = EnemyPosition + MoveEnemy;

	// 移動範囲を制限
	NewPosition = XMVectorClamp(NewPosition, XMVectorSet(minX, 0.0f, minZ, 0.0f), XMVectorSet(maxX, 0.0f, maxZ, 0.0f));

	// 移動ベクトルを再計算
	MoveEnemy = NewPosition - EnemyPosition;

	XMStoreFloat3(&transform_.position_, NewPosition);
}

void Enemy::EnemyAttack(){
}


//メモ
//不自然な動きなので自然の動きを出すようにしたほうがいい。
//動きは共通だけど速さと変えたいときはパラメーターを管理するクラスとか作って工夫ができる。
//伝える努力をしよう;;

