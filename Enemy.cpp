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
		//���������Ă���Ȃ�ǌ�����(�̂��ɍU������悤�ɂ������j
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



/// <summary>
/// ����͈̔͂ɂ��邩�ǂ���
/// </summary>
bool Enemy::IsFindPlayer(const XMFLOAT3& PlayerPos)
{
	// �����Ă�����ɕϊ�
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	frontVec = XMVector3Normalize(frontVec);

	
	XMVECTOR playerVec = frontVec - XMLoadFloat3(&transform_.position_);
	playerVec = XMVector3Normalize(playerVec);

	//���ς��Ƃ�
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//����p�͈͓̔����ǂ���
	if (InnerProduct > cos(XMConvertToRadians(enemyfan.EnemyDegree / 2.0)))
		return false;
	
		float length = XMVectorGetX(XMVector3Length(playerVec));
		//���S�����܂ł̒������傫�����̔���
		if (length > enemyfan.EnemyLength)
		{
			return true;
		}
		return false;
}


/// <summary>
/// �ǌ��A���S���Y��
/// </summary>
void Enemy::ChasePlayer(XMFLOAT3 playerPos)
{
	//�Ώۂ̃|�W�V�����Ǝ��g�̃|�W�V������VECTOR�^�ɕϊ�
	XMVECTOR PlayerPos = XMLoadFloat3(&playerPos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//�ǔ����邽�߂̕����x�N�g���Ƃ��Ďg�����߂̌v�Z&���K��
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;
	EnemyChase = XMVector3Normalize(EnemyChase);

	//�O���x�N�g�����쐬���x�N�g���Ԃ̊p�x�v�Z
	XMVECTOR front_= (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
	float dot = XMVectorGetX(XMVector3Dot(EnemyChase, front_));
	float Eneangle_ = (float) acos(dot);

	//�O�ς��v�Z��y������0��菬�����ꍇ�p�x�����](�v���C���[���E���������̋�ʂ����悤�ɂȂ�)
	XMVECTOR  EnemyCross = XMVector3Cross(front_, EnemyChase);
	if (XMVectorGetY(EnemyCross) < 0)
	{
		Eneangle_ *= -1.0f;
	}

	//���W�A������x�ɕϊ�
	transform_.rotate_.y = XMConvertToDegrees(Eneangle_);

	//�ړ����ׂ��������v�Z����đ����������邱�Ƃœ�����
	XMVECTOR MoveEnemy = EnemyChase * movement_;

	//�V�����ʒu���X�V����悤�Ɏ��g�̃|�W�V�����Ɋi�[
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

/// <summary>
/// 10�b�Ɉ�������ς��Ȃ���ړ�����
/// </summary>
void Enemy::EnemySearch()
{
   

}