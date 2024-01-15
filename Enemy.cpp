#include "Enemy.h"
#include "Player.h"
#include"Map.h"
#include "Engine/Model.h"

namespace {
	const int LastTime = 10;//10�b�Ɉ�������ς����邽�߂̕ϐ�
}

Enemy::Enemy(GameObject* parent)
	: GameObject(parent,"Enemy"),hModel_(-1),front_  (XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f))
{
	
	movement_ = 0.06f;
	

	enemyfan = {
		60.0f,
		10.0f,
	};
	
	playerPos  = ((Player*)FindObject("Player"))->GetPosition();
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
	
	if (IsFindPlayer(playerPos))
	{
		//���������Ă���Ȃ�ǌ�����(�̂��ɍU������悤�ɂ������j
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
/// ����͈̔͂ɂ��邩�ǂ���
/// </summary>
bool Enemy::IsFindPlayer(const XMFLOAT3& PlayerPos)
{
	//���g�̃|�W�V����������ϐ�
	XMVECTOR EnemPos = XMLoadFloat3(&transform_.position_);

	// �����Ă�����ɑ΂����]�s��
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//�G�̑O���x�N�g����matRY�ŉ�]������
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	//���K��
	frontVec = XMVector3Normalize(frontVec);

	//�v���C���[�̈ʒu��\���x�N�g��
	XMVECTOR Playervec = XMLoadFloat3(&playerPos);

	XMVECTOR playerVec = Playervec - EnemPos;
	float length = XMVectorGetX(XMVector3Length(playerVec));
	playerVec = XMVector3Normalize(playerVec);

	//���ς��Ƃ�
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//����p�͈͓̔����ǂ���
	if (InnerProduct > cos(XMConvertToRadians(enemyfan.EnemyDegree / 2.0)))
		return false;

	//���S�����܂ł̒������傫�����̔���
	if (length > enemyfan.EnemyLength)
		return false;

	return true;
}


/// <summary>
/// �ǌ��A���S���Y��
/// </summary>
void Enemy::ChasePlayer()
{
	//�Ώۂ̃|�W�V�����Ǝ��g�̃|�W�V������VECTOR�^�ɕϊ�
	XMVECTOR PlayerPos = XMLoadFloat3(&playerPos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//�ǔ����邽�߂̕����x�N�g���Ƃ��Ďg�����߂̌v�Z&���K��
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;
	EnemyChase = XMVector3Normalize(EnemyChase);

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