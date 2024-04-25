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
	//自身のポジションを入れる変数
	XMVECTOR EnemPos = XMLoadFloat3(&transform_.position_);

	// 向いてる方向に対する回転行列
	XMMATRIX matRY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//敵の前方ベクトルをmatRYで回転させる
	XMVECTOR frontVec = XMVector3TransformCoord(front_, matRY);
	//正規化
	frontVec = XMVector3Normalize(frontVec);

	//プレイヤーの位置を表すベクトル
	XMVECTOR Playervec = XMLoadFloat3(&playerPos);

	XMVECTOR playerVec = Playervec - EnemPos;
	float length = XMVectorGetX(XMVector3Length(playerVec));
	playerVec = XMVector3Normalize(playerVec);

	//内積をとる
	float InnerProduct = XMVectorGetX(XMVector3Dot(playerVec, frontVec));

	//視野角の範囲内かどうか
	if (InnerProduct > enemyfan.EnemyDegree)
		return false;

	//中心から扇までの長さより大きいかの判別
	if (length > enemyfan.EnemyLength)
		return false;

	return true;
}
