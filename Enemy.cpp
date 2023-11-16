#include "Enemy.h"
#include "Engine/Model.h"
#include"Player.h"

Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy"),hModel_(-1), timing_(rand() % 180 + 1),movement_(0.15f)
{
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
    //©“®ˆÚ“®
    transform_.position_.x += movement_*sin(angle_);
    transform_.position_.z += movement_*cos(angle_);


    // ˆÚ“®”ÍˆÍ‚Ì§Œä
    if (transform_.position_.x < -5.0f || transform_.position_.x > 5.0f ||
        transform_.position_.z < -5.0f || transform_.position_.z > 5.0f)
    {
        
        angle_= static_cast<float>(rand() % 360) * (3.14f / 180.0f); //360‹‚Ü‚Å‰ñ“]‚µ‚ÄˆÚ“®‚·‚éB
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

void Enemy::ShowPlayer()
{
}
