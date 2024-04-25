#include"EnemyBase.h"


void EnemyBase::Initialize()
{
	front_ = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer = nullptr;

	pPlayer = (Player*)FindObject("Player");

	enemyfan.EnemyDegree = cos(XMConvertToRadians(60.0 / 2.0));
	enemyfan.EnemyLength = 10.0f;
	elaspsedTime_ = 0.0f;
}


void EnemyBase::Update()
{

}
