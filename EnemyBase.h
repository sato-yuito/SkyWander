#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
#include "Player.h"

class EnemyBase:public GameObject
{
protected:

	float movement_;//移動量

	XMVECTOR front_;

	Player* pPlayer;

	float elaspsedTime_;//経過時間を追跡するための変数
	
	struct EnemyFan
	{
		float EnemyDegree;//視野角の範囲（角度）
		float EnemyLength;//中心から扇までの長さ
	} enemyfan;

protected:
	EnemyBase(GameObject* parent, std::string _name)
		:GameObject(parent, _name) {}

	virtual void Initialize() =0;
	
	virtual void Update() = 0 ;
	
	//描画
	virtual void Draw() = 0 ;

	//開放
	virtual void Release() =0 ;

	//見つけているか
	virtual bool IsFindPlayer() = 0;

	//プレイヤーを見つけたら追跡
	virtual void ChasePlayer() = 0;

	//見つけていない場合の移動
	virtual void EnemySearch() = 0;

	//攻撃
	virtual void EnemyAttack() = 0;
};

