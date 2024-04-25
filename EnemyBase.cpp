#include"EnemyBase.h"


void EnemyBase::Initialize()
{
	front_ = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer = (Player*)FindObject("Player");

	enemyfan.EnemyDegree = cos(XMConvertToRadians(60.0 / 2.0));
	enemyfan.EnemyLength = 10.0f;
	
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
