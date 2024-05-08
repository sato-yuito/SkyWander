#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
#include "Player.h"

class EnemyBase:public GameObject
{
protected:

	float Enemymovement_;//�ړ��X�s�[�h

	XMVECTOR front_;//�O���x�N�g��

	Player* pPlayer;
	
	struct EnemyFan
	{
		float EnemyDegree;//����p�͈̔́i�p�x�j
		float EnemyLength;//���S�����܂ł̒���
	} enemyfan;

	EnemyBase(GameObject* parent, std::string _name)
		:GameObject(parent, _name) {}

	virtual void Initialize() =0;
	
	virtual void Update() = 0 ;
	
	//�`��
	virtual void Draw() = 0 ;

	//�J��
	virtual void Release() =0 ;

	/// <summary>
	/// Player�������Ă��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	virtual bool IsFindPlayer() = 0;
	
	/// <summary>
	/// ��������ǌ�
	/// </summary>
	virtual void ChasePlayer() = 0;

	//�U��
	virtual void EnemyAttack() = 0;
};

