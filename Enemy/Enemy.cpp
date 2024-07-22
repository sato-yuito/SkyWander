#include "Enemy.h"

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
	EnemyBase::Update();
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


void Enemy::EnemyAttack()
{

}




