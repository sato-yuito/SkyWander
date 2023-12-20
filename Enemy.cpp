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
		//���������Ă���Ȃ�ǌ�����
		
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
/// ����͈̔͂ɂ��邩�ǂ���
/// </summary>
bool Enemy::IsFindPlayer(const XMFLOAT3& PlayerPos)
{
	//�q���g(����p����)
	/*
		������ɂ��邩�𔻕ʂ���ɂ́A
		�����̌����Ă�����̃x�N�g���i�����P�j�ƁA��������Ώۂւ̃x�N�g��
		�i�����P�j�œ��ς����ƁAcos������ɓ���܂��B����p��60���ł���΁A���ꂪcos(60��)�����傫����΁A
		������ɂ��܂��B
	*/
	
	// �����Ă�����ɕϊ�
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	frontVec = XMVector3Normalize(frontVec);

	
	XMVECTOR playerVec = frontVec - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//���ς��Ƃ�
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//�����Ǝ������������̔���
	if (InnerProduct > enemyfan.EnemyDegree / 2.0)
	
		return false;
	


	   float length = XMVectorGetX(XMVector3Length(playerVec));

	   if (length > enemyfan.EnemyLength)

		   return true;
	   
	   
   
	  


}


/// <summary>
/// �ǌ��A���S���Y��
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

