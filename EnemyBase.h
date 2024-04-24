#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
#include "Player.h"

class EnemyBase:public GameObject
{
protected:

	float movement_;//�ړ���

	XMVECTOR front_;

	Player* pPlayer;

	float elaspsedTime_;//�o�ߎ��Ԃ�ǐՂ��邽�߂̕ϐ�
	
	struct EnemyFan
	{
		float EnemyDegree;//����p�͈̔́i�p�x�j
		float EnemyLength;//���S�����܂ł̒���
	} enemyfan;

protected:
	EnemyBase(GameObject* parent, std::string _name)
		:GameObject(parent, _name) {}

	virtual void Initialize() =0;
	
	virtual void Update() = 0 ;
	
	//�`��
	virtual void Draw() = 0 ;

	//�J��
	virtual void Release() =0 ;

	//�����Ă��邩
	virtual bool IsFindPlayer() = 0;

	//�v���C���[����������ǐ�
	virtual void ChasePlayer() = 0;

	//�����Ă��Ȃ��ꍇ�̈ړ�
	virtual void EnemySearch() = 0;

	//�U��
	virtual void EnemyAttack() = 0;
};

