#include "Enemy.h"

#include"Map.h"
#include "Engine/Model.h"

namespace {
	const int LastTime = 10;//������ς����邽�߂̎���(�b)
}

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1), front_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),pPlayer(nullptr)
{

	movement_ = 0.06f;

	enemyfan.EnemyDegree = cos(XMConvertToRadians(60.0 / 2.0));
	enemyfan.EnemyLength = 10.0f;
	
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
	
	pPlayer = (Player*)FindObject("Player");
}

void Enemy::Update()
{
	
	if (IsFindPlayer())
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
bool Enemy::IsFindPlayer()
{
	XMFLOAT3 playerPos = pPlayer->GetPosition();
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
	if (InnerProduct >enemyfan.EnemyDegree)
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
	XMFLOAT3 playerpos = pPlayer->GetPosition();
	//�Ώۂ̃|�W�V�����Ǝ��g�̃|�W�V������VECTOR�^�ɕϊ�
	XMVECTOR PlayerPos = XMLoadFloat3(&playerpos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//�ǔ����邽�߂̕����x�N�g���Ƃ��Ďg�����߂̌v�Z&���K��
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;

	double enemtan= atan2(XMVectorGetX(EnemyChase),XMVectorGetZ(EnemyChase));
	
	//���W�A������x�ɕϊ�
	transform_.rotate_.y = XMConvertToDegrees(enemtan);

	//�ړ����ׂ��������v�Z����đ����������邱�Ƃœ�����

	XMVECTOR MoveEnemy = EnemyChase * movement_;
	//�����ꂾ�ƁA�v���C���[�̂�����ɐi��ł��܂��B�L�����̌����Ă���Ɉړ�����ׂ��B�z�[�~���O���ۂ������悤�ɂ���Ƃ��̂��߂ɁB(���������)
	
	//�V�����ʒu���X�V����悤�Ɏ��g�̃|�W�V�����Ɋi�[
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

/// <summary>
/// 10�b�Ɉ�������ς��Ȃ���ړ�����
/// </summary>
void Enemy::EnemySearch()
{
	
}