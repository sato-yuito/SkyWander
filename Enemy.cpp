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

	movement_ = 0.02f;

	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	

	
	pPlayer = (Player*)FindObject("Player");
}

void Enemy::Update()
{
	if (EnemyBase::IsFindPlayer()){
		//���������Ă���Ȃ�ǌ�����(�̂��ɍU������悤�ɂ������j
		ChasePlayer();
	}
	else{
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


void Enemy::ChasePlayer()
{
	XMFLOAT3 playerpos = pPlayer->GetPosition();
	playerpos.y = 0;
	//�Ώۂ̃|�W�V�����Ǝ��g�̃|�W�V������VECTOR�^�ɕϊ�
	XMVECTOR PlayerPos = XMLoadFloat3(&playerpos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//�ǔ����邽�߂̕����x�N�g���Ƃ��Ďg�����߂̌v�Z
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;

	//�G�L�����N�^�[���v���C���[��ǂ�������Ƃ��Ƀv���C���[�������Ă�������Ɍ��������邽�߂̏���
	double enemtan= atan2(XMVectorGetX(-EnemyChase),XMVectorGetZ(-EnemyChase));
	
	//���W�A������x�ɕϊ�
	transform_.rotate_.y = XMConvertToDegrees(enemtan);

	// �v���C���[�Ɍ������Đi�ޕ����x�N�g���𐶐�
	XMVECTOR moveDirection = XMVector3Normalize(EnemyChase);

	//�ړ��x�N�g���v�Z
	XMVECTOR MoveEnemy = moveDirection * movement_;
	
	//�V�����ʒu���X�V����悤�Ɏ��g�̃|�W�V�����Ɋi�[
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

/// <summary>
/// 10�b�Ɉ�������ς��Ȃ���ړ�����
/// </summary>
void Enemy::EnemySearch()
{
	elaspsedTime_ += 0.016f; // �o�ߎ��Ԃ̐ݒ�(���t���[�����Z)

	// �w�肵�����Ԉȏ�ɂȂ����Ƃ��Ƀ����_���ɉ�]�����ă��Z�b�g����
	if (elaspsedTime_ >= LastTime)
	{
		transform_.rotate_.y = static_cast<float>(rand() % 360);
		elaspsedTime_ = 0.0f;
	}

	// ���݂̉�]�Ɋ�Â��Ĉړ��x�N�g�����v�Z
	XMVECTOR moveDirection = XMVectorSet(sinf(XMConvertToRadians(transform_.rotate_.y)),
		0.0f,
		cosf(XMConvertToRadians(transform_.rotate_.y)),
		0.0f);

	//���K��
	moveDirection = XMVector3Normalize(moveDirection);

	// �V�����ʒu���v�Z
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	XMVECTOR MoveEnemy = moveDirection * movement_;

	// �V�����ʒu��K�p
	XMVECTOR NewPosition = EnemyPosition + MoveEnemy;

	// �ړ��͈͂𐧌�
	NewPosition = XMVectorClamp(NewPosition, XMVectorSet(minX, 0.0f, minZ, 0.0f), XMVectorSet(maxX, 0.0f, maxZ, 0.0f));

	// �ړ��x�N�g�����Čv�Z
	MoveEnemy = NewPosition - EnemyPosition;

	XMStoreFloat3(&transform_.position_, NewPosition);
}

void Enemy::EnemyAttack(){
}


//����
//�s���R�ȓ����Ȃ̂Ŏ��R�̓������o���悤�ɂ����ق��������B
//�����͋��ʂ����Ǒ����ƕς������Ƃ��̓p�����[�^�[���Ǘ�����N���X�Ƃ�����čH�v���ł���B
//�`����w�͂����悤;;

