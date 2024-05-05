#include"EnemyBase.h"


void EnemyBase::Initialize()
{
	front_ = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer = (Player*)FindObject("Player");

	enemyfan.EnemyDegree = cos(XMConvertToRadians(60.0 / 2.0));
	enemyfan.EnemyLength = 10.0f;
	
	pPlayer = (Player*)FindObject("Player");

}


void EnemyBase::Update()
{

}

bool EnemyBase::IsFindPlayer()
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
	if (InnerProduct > enemyfan.EnemyDegree)
		return false;

	//���S�����܂ł̒������傫�����̔���
	if (length > enemyfan.EnemyLength)
		return false;

	return true;
}

void EnemyBase::ChasePlayer()
{
	XMFLOAT3 playerpos = pPlayer->GetPosition();
	playerpos.y = 0;//��������Ȃ���Player���W�����v���������ł������Ă��܂��̂�0�ɐݒ�
	//�Ώۂ̃|�W�V�����Ǝ��g�̃|�W�V������VECTOR�^�ɕϊ�
	XMVECTOR PlayerPos = XMLoadFloat3(&playerpos);
	XMVECTOR EnemyPosition = XMLoadFloat3(&transform_.position_);
	//�ǔ����邽�߂̕����x�N�g���Ƃ��Ďg�����߂̌v�Z
	XMVECTOR EnemyChase = PlayerPos - EnemyPosition;

	//�G�L�����N�^�[���v���C���[��ǂ�������Ƃ��Ƀv���C���[�������Ă�������Ɍ��������邽�߂̏���
	double enemtan = atan2(XMVectorGetX(-EnemyChase), XMVectorGetZ(-EnemyChase));

	//���W�A������x�ɕϊ�
	transform_.rotate_.y = XMConvertToDegrees(enemtan);

	// �v���C���[�Ɍ������Đi�ޕ����x�N�g���𐶐�
	XMVECTOR moveDirection = XMVector3Normalize(EnemyChase);

	//�ړ��x�N�g���v�Z
	XMVECTOR MoveEnemy = moveDirection * Enemymovement_;

	//�V�����ʒu���X�V����悤�Ɏ��g�̃|�W�V�����Ɋi�[���Đ��K��
	XMStoreFloat3(&transform_.position_, EnemyPosition + MoveEnemy);
}

