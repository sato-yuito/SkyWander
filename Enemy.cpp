#include "Enemy.h"

namespace {
	const int LastTime = 10;//������ς����邽�߂̎���(�b)
	float minX = -4.0f;//x���W�̍ŏ��s���͈�
	float maxX = 4.0f;//x���W�̍ő�s���͈�
	float minZ = -4.0f;//z���W�̍ŏ��s���͈�
	float maxZ = 4.0f;//z���W�̍ő�s���͈�
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
		//���������Ă���Ȃ�ǌ�����(�̂��ɍU������悤�ɂ������j
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
/// 10�b�Ɉ�������ς��Ȃ���ړ�����
/// </summary>
void Enemy::EnemySearch()
{

}

void Enemy::EnemyAttack(){

}


//����
//�s���R�ȓ����Ȃ̂Ŏ��R�̓������o���悤�ɂ����ق��������B
//�����͋��ʂ����Ǒ����ƕς������Ƃ��̓p�����[�^�[���Ǘ�����N���X�Ƃ�����čH�v���ł���B
//�`����w�͂����悤;;

