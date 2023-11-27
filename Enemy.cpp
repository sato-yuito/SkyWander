#include "Enemy.h"
#include "Engine/Model.h"

//
////����p��^���Ă��������Ă��Ȃ�������false,�����Ă���Ȃ�ture��Ԃ�
//bool Enemy::EenmyPOV(XMFLOAT3 PlayerVec)
//{
//    float POV = 45.0f;
//    float viewPov = tan(POV / 2.0f);
//    if(abs(PlayerVec.x))
//}

void Enemy::ShowPlayer(Player& player, float speed)
{
    //�ʒu�擾
    XMFLOAT3 PlayerPosition = player.GetPosition();

    //�v���C���[�x�N�g���̌v�Z
    XMFLOAT3 PlayerVector;
    PlayerVector.x = PlayerPosition.x - transform_.position_.x;
    PlayerVector.y = PlayerPosition.y - transform_.position_.y;
    PlayerVector.z = PlayerPosition.z - transform_.position_.z;

    //�v���C���[�x�N�g���̐��K��
    float length = sqrt(PlayerVector.x * PlayerVector.x + PlayerVector.y * PlayerVector.y + PlayerVector.z * PlayerVector.z);
    PlayerVector.x /= length;
    PlayerVector.y /= length;
    PlayerVector.z /= length;

    //�v���C���[�Ɍ������Ĉړ�
    transform_.position_.x += PlayerVector.x * speed;
    transform_.position_.y += PlayerVector.y * speed;
    transform_.position_.z += PlayerVector.z * speed;
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
    //Player�I�u�W�F�N�g��T���ă|�W�V�������v���C���[�̈ʒu���擾
    Player* pPlayer = (Player*)FindObject("Player");
    int hPlayerModel = pPlayer->GetModelHandle();
    pPlayer->GetPosition();
   
  

    //�v���C���[�������Ă��Ȃ��ꍇ�͈ړ��������Č�������ǌ�
    if (pPlayer == nullptr)
    {
       
        // �ړ�
        transform_.position_.x += movement_ * sin(angle_);
        transform_.position_.z += movement_ * cos(angle_);


        // �ړ��͈͂̐���
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

