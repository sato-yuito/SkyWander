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
		//���������Ă���Ȃ�ǌ�����
		ChasePlayer(playerPos);
	}
	else
	{
		// �����Ă��Ȃ��Ȃ������ς��Ȃ���ړ�
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

	//�Ώۂ̃|�W�V�������玩�g�̃|�W�V�����������ăx�N�g�������߂Đ��K��
	XMVECTOR playerVec = XMLoadFloat3(&PlayerPos) - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//���ς��Ƃ�
	float InnerProduct = cos(XMVectorGetX((XMVector3Dot(playerVec, frontVec))));

	//�����Ǝ������������̔���
   if (InnerProduct > enemyfan.EnemyDegree / 2.0)return false;
   


	   float length = XMVectorGetX(XMVector3Length(playerVec));

	   if (length > enemyfan.EnemyLength) 
	   
		   return false;
	   
	   return true;
   

}


/// <summary>
/// �ǌ��A���S���Y��
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos)
{
	//�q���g
	//�ړI�̕����Ɍ������Ƃ��A���炩�Ɍ�����ς���ꍇ�́A
	//�����̉E�����̃x�N�g���ƁA��������Ώۂւ̃x�N�g���Ƃœ��ς����A���O�ł���ΑΏۂ͉E���ɁA���O�ł���ΑΏۂ͍����ɂ��܂��B
	//���̕����ɁA�����̌�����ς���΁A���񂾂�Ώۂ̕��������悤�ɂȂ�܂��B
    

	//�E�x�N�g��
	XMMATRIX RightEnemyVec = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.y+90.0f));
	XMVECTOR RightVec = XMVector3Normalize(XMVector3TransformCoord(front_, RightEnemyVec));
	
    //�v���C���[�Ƃ̃x�N�g��
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
/// �ړ�����(���̂���������x�̎��Ԃ�����������]������悤�ɂ�����)
/// </summary>
void Enemy::EnemyMove()
{
	
	

}