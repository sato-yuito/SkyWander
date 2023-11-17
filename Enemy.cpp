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
    //自動移動
    transform_.position_.x += movement_*sin(angle_);
    transform_.position_.z += movement_*cos(angle_);


    // 移動範囲の制御
    if (transform_.position_.x < -5.0f )
    {
        float angleX= static_cast<float>(rand() % 180); 
        angle_ -= angleX;
    }
    if (transform_.position_.z > 5.0f)
    {
        float angleZ = static_cast<float>(rand() % 180+90);
        angle_ += angleZ;
    }
    if (transform_.position_.x > 5.0f)
    {
        float angleX = static_cast<float>(rand() % 180+180);
        angle_ += angleX;
    }
    if (transform_.position_.z < -5.0)
    {
        float angleZ = static_cast<float>(rand() %180-90);
        angle_ -= angleZ;
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

//void Enemy::ShowPlayer( Player&player)
//{
//    //// プレイヤーの位置を取得
//    // XMFLOAT3 PlayerPosition = player.GetPosition();
//    // XMVECTOR PlayerWorldPosition = XMLoadFloat3(&PlayerPosition);//変換
//
//    // //自身の位置も取得
//    // XMFLOAT3 EnemyPosition = GetPosition();
//    // XMVECTOR EnemyWorldPotion = XMLoadFloat3(&EnemyPosition);
//
//
//}
