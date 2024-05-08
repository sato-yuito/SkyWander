#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
#include "Player.h"

class EnemyBase:public GameObject
{
protected:

	float Enemymovement_;//移動スピード

	XMVECTOR front_;//前方ベクトル

	Player* pPlayer;
	
	struct EnemyFan
	{
		float EnemyDegree;//視野角の範囲（角度）
		float EnemyLength;//中心から扇までの長さ
	} enemyfan;

	EnemyBase(GameObject* parent, std::string _name)
		:GameObject(parent, _name) {}

	virtual void Initialize() =0;
	
	virtual void Update() = 0 ;
	
	//描画
	virtual void Draw() = 0 ;

	//開放
	virtual void Release() =0 ;

	/// <summary>
	/// Playerを見つけているかどうか
	/// </summary>
	/// <returns></returns>
	virtual bool IsFindPlayer() = 0;
	
	/// <summary>
	/// 見つけたら追撃
	/// </summary>
	virtual void ChasePlayer() = 0;

	//攻撃
	virtual void EnemyAttack() = 0;
};

