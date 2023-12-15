#include "Enemy.h"
#include "Engine/Model.h"
#include <DirectXMath.h>

/// <summary>
/// 扇の範囲内(視野角）を決める処理
/// </summary>
/// <param name="PlayerVec"></param>
/// <returns></returns>
bool Enemy::EnemyPOV(const XMFLOAT3& PlayerVec)
{
    //ヒント(視野角判定)
    /*視野内にいるかを判別するには、
        自分の向いてる向きのベクトル（長さ１）と、自分から対象へのベクトル
        （長さ１）で内積を取ると、cosΘが手に入ります。視野角が60°であれば、これがcos(60°)よりも大きければ、
        視野内にいます。*/


    //向いている方向を表すやつ
    XMVECTOR front =XMVectorSet(0, 0, 0, 0);

    XMMATRIX Enemyrotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMVECTOR EnemyfE = XMVector3TransformCoord(front, Enemyrotate);
    XMVECTOR ENEMYFE = XMVector3Normalize(EnemyfE);
    XMVECTOR Playervec = XMLoadFloat3(&PlayerVec) - XMLoadFloat3(&transform_.position_);
    XMVECTOR PLAYERVEC = XMVector3Normalize(Playervec);
  
    //内積をとる
    float InnerProduct = XMVectorGetX(XMVector3Dot(PLAYERVEC, ENEMYFE));
   
    return InnerProduct > enemyfan.EnemyDegree;
    
}


/// <summary>
/// 追撃アルゴリズムの実装
/// </summary>
/// <param name="player"></param>
/// <param name="speed"></param>
void Enemy::ShowPlayer(Player& player, float speed)
{
    //ヒント1,3
    /*自分が回転してないときの移動ベクトルに、回転行列をかけてから、座標に足します。<-ヒント1
     目的の方向に向かうとき、滑らかに向きを変える場合は、
         自分の右向きのベクトルと、自分から対象へのベクトルとで内積を取り、＞０であれば対象は右側に、
         ＜０であれば対象は左側にいます。
         その方向に、自分の向きを変えれば、だんだん対象の方を向くようになります。*/

    //位置取得
    XMFLOAT3 PlayerPosition = player.GetPosition();

    //プレイヤーベクトルの計算
    XMFLOAT3 PlayerVector;
    XMVECTOR playervector = XMLoadFloat3(&PlayerPosition);
    PlayerVector.x = PlayerPosition.x - transform_.position_.x;
    PlayerVector.y = PlayerPosition.y - transform_.position_.y;
    PlayerVector.z = PlayerPosition.z - transform_.position_.z;

    //プレイヤーベクトルの正規化
    float length = sqrt(PlayerVector.x * PlayerVector.x + PlayerVector.y * PlayerVector.y + PlayerVector.z * PlayerVector.z);
    PlayerVector.x /= length;
    PlayerVector.y /= length;
    PlayerVector.z /= length;

   
   
        transform_.position_.x += PlayerVector.x * speed;
        transform_.position_.y += PlayerVector.y * speed;
        transform_.position_.z += PlayerVector.z * speed;
      
    
}


Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy"),hModel_(-1),movement_(0.15f)
{
    enemyfan =
    {
        XMLoadFloat3(&transform_.position_),
        60.0f,
        20.0f,
        transform_.rotate_.y
    };
    map = (Map*)FindObject("Map");
    
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = (float)(rand() % 401 - 200) / 10;
	transform_.position_.z = 20.0f;
}

void Enemy::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");
    int hPlayerModel = pPlayer->GetModelHandle();
     pPlayer->GetPosition();
     
  
    //プレイヤーを見つけていない場合は移動し続けて見つけたら追撃
    if (EnemyPOV(pPlayer->GetPosition()))
    {
       
        // 移動
        transform_.position_.x += movement_ * sin(angle_);
        transform_.position_.z += movement_ * cos(angle_);


        // 移動範囲の制御
        if (transform_.position_.x < -5.0f)
        {
            angle_ = static_cast<float>(rand() % 180);

        }
        if (transform_.position_.z > 5.0f)
        {
            angle_ = static_cast<float>(rand() % 180 + 90);
        }
        if (transform_.position_.x > 5.0f)
        {
            angle_ = static_cast<float>(rand() % 180 + 180);
        }
        if (transform_.position_.z < -5.0)
        {
            angle_ = static_cast<float>(rand() % 180 - 90);
        }
    }
    else
    {
        ShowPlayer(*pPlayer, 0.1f);
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

