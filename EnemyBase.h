#pragma once
#include"Engine/GameObject.h"
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

	EnemyBase(GameObject* parent,std::string _name)
		:GameObject(parent, _name){}

	~EnemyBase();

	void Initialize()override ;
	
	void Update()override ;
	
	//描画
	void Draw() override;

	//開放
	void Release() override;

	//見つけているか
	virtual bool IsFindPlayer()  = 0;

	//プレイヤーを見つけたら追跡
	virtual void ChasePlayer()  = 0;

	//見つけていない場合の移動
	virtual void EnemySearch()   = 0;


};

