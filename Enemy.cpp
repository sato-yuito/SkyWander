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
	
	Enemymovement_ = 0.05f;

	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
		
}

void Enemy::Update()
{
	if (IsFindPlayer()){
		//もし見つけているなら追撃する(のちに攻撃するようにしたい）
		ChasePlayer();
	}
	else{

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

bool Enemy::IsFindPlayer()
{
	return EnemyBase::IsFindPlayer();
}
void Enemy::ChasePlayer()
{
	EnemyBase::ChasePlayer();
}

/// <summary>
/// 10秒に一回向きを変えながら移動する
/// </summary>
void Enemy::EnemySearch()
{

}

void Enemy::EnemyAttack(){

}


//メモ
//不自然な動きなので自然の動きを出すようにしたほうがいい。
//動きは共通だけど速さと変えたいときはパラメーターを管理するクラスとか作って工夫ができる。
//伝える努力をしよう;;

