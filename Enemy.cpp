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
    //自身のポジションを持ってきてVECTOR型に変換
    XMFLOAT3 enemyposition = GetPosition();
    XMVECTOR EnePos = XMLoadFloat3(&enemyposition);
    enemyfan.EnemyPosition = EnePos;

    //プレイヤーベクトルを変換し距離を計算して正規化
    XMVECTOR playervec = XMLoadFloat3(&PlayerVec);
    XMVECTOR EnemyandPlayer = XMVectorSubtract(playervec, enemyfan.EnemyPosition);
    XMVECTOR EnemyDir = XMVector3Normalize(EnemyandPlayer);

  
 
  

 

    
}


/// <summary>
/// 追撃アルゴリズムの実装
/// </summary>
/// <param name="player"></param>
/// <param name="speed"></param>
void Enemy::ShowPlayer(Player& player, float speed)
{
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

   
   //視野角に入っていたら追撃
      if(EnemyPOV(PlayerVector))
      {
        transform_.position_.x += PlayerVector.x * speed;
        transform_.position_.y += PlayerVector.y * speed;
        transform_.position_.z += PlayerVector.z * speed;
      }
    
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

