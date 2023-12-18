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
		//�����Ă���
		ChasePlayer(playerPos, 0.1f);
	}
	else
	{
		// �����Ă��Ȃ�

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
/// �����Ă��邩
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


	//�����Ă��������\�����
	XMVECTOR front = XMVectorSet(0, 0, -1, 0);

	// �����Ă�����ɕϊ�
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front, matRY);
	frontVec = XMVector3Normalize(frontVec);

	//
	XMVECTOR playerVec = XMLoadFloat3(&PlayerPos) - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//���ς��Ƃ�
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	return InnerProduct > enemyfan.EnemyDegree;

}


/// <summary>
/// �ǌ��A���S���Y���̎���
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos, float speed)
{
	//�ړI�̕����Ɍ������Ƃ��A���炩�Ɍ�����ς���ꍇ�́A
	//�����̉E�����̃x�N�g���ƁA��������Ώۂւ̃x�N�g���Ƃœ��ς����A���O�ł���ΑΏۂ͉E���ɁA���O�ł���ΑΏۂ͍����ɂ��܂��B
	//���̕����ɁA�����̌�����ς���΁A���񂾂�Ώۂ̕��������悤�ɂȂ�܂��B

	XM


}
