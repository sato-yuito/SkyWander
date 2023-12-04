#include "Enemy.h"
#include "Engine/Model.h"
#include <DirectXMath.h>

//視野角判定するために必要間前準備
bool Enemy::EnemyPOV(const XMFLOAT3& PlayerVec)
{
    XMFLOAT3 enemyposition = GetPosition();//自身のポジションを入れる変数
    XMVECTOR EnePos = XMLoadFloat3(&enemyposition);//XMVECTOR型に変換
    enemyfan.EnemyPosition = EnePos;//自身のポジション取得

    XMVECTOR playervec = XMLoadFloat3(&PlayerVec);//Float型からXMVECOTR型に変換
    XMVECTOR EnemyandPlayer = playervec - enemyfan.EnemyPosition;//プレイヤーのベクトルからポジションを引いて計算
    DirectionDegree
   
   
}


/// <summary>
/// 追撃アルゴリズムの実装。
/// </summary>
/// <param name="player"></param>
/// <param name="speed"></param>
void Enemy::ShowPlayer(Player& player, float speed)
{
    //位置取得
    XMFLOAT3 PlayerPosition = player.GetPosition();

    //プレイヤーベクトルの計算
    XMFLOAT3 PlayerVector;
    XMVECTOR playervector = XMLoadFloat3(&PlayerVector);
    PlayerVector.x = PlayerPosition.x - transform_.position_.x;
    PlayerVector.y = PlayerPosition.y - transform_.position_.y;
    PlayerVector.z = PlayerPosition.z - transform_.position_.z;

    //プレイヤーベクトルの正規化
    float length = sqrt(PlayerVector.x * PlayerVector.x + PlayerVector.y * PlayerVector.y + PlayerVector.z * PlayerVector.z);
    PlayerVector.x /= length;
    PlayerVector.y /= length;
    PlayerVector.z /= length;

   
      if(EnemyPOV(PlayerVector))
      {
        transform_.position_.x += PlayerVector.x * speed;
        transform_.position_.y += PlayerVector.y * speed;
        transform_.position_.z += PlayerVector.z * speed;
      }
    
}


Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy"),hModel_(-1), timing_(rand() % 180 + 1),movement_(0.15f)
{
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
    //Playerオブジェクトを探してポジションをプレイヤーの位置を取得
    Player* pPlayer = (Player*)FindObject("Player");
    int hPlayerModel = pPlayer->GetModelHandle();
    pPlayer->GetPosition();
   
  

    //プレイヤーを見つけていない場合は移動し続けて見つけたら追撃
    if (pPlayer == nullptr)
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

