#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"

namespace
{
    const float PlayerSpeed = 0.5f;//�v���C���[�̃X�s�[�h
}
void Player::PlayerWalk()
{
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.x += PlayerSpeed;
    }
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.x -= PlayerSpeed;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.z += PlayerSpeed;

    }
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= PlayerSpeed;
    }
    //������ς��鏈��

}
void Player::PlayerRun()
{

}
void Player::PlayerJump()
{

}
void Player::PlayerAttack()
{

}
void Player::UseAitem()
{

}
Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1),map(nullptr)
{

}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);
    map = (Map*)FindObject("Map");
}

//�X�V
void Player::Update()
{
    Camera::SetTarget(transform_.position_);

    switch (playerstate_)
    {
    case :

    }
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{

}