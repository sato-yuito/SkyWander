#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"

namespace
{
    const float PlayerSpeed = 0.1f;//�v���C���[�̃X�s�[�h
      
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1),map(nullptr),playerstate_(Playeraction::wait)
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
    PlayerInputState();
    switch (playerstate_)
    {
    case Playeraction::wait:
        PlayerWait();
        break;
    case Playeraction::Walk:
        PlayerWalk();
        break;
    case Playeraction::run:
        PlayerRun();
        break;
    case Playeraction::jump:
        PlayerJump();
        break;
    case Playeraction::attack:
        PlayerAttack();
        break;
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

void Player::PlayerWait()
{
}

void Player::PlayerWalk()
{
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.z+= PlayerSpeed;
    }
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= PlayerSpeed;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += PlayerSpeed;

    }
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= PlayerSpeed;
    }
    //������ς��鏈��

}
void Player::PlayerRun()
{
    float RUN = PlayerSpeed * 2;

    if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D)))
    {
        // W�AA�AS�AD�̂����ꂩ��������Ă���ꍇ�ɑ���
        transform_.position_.z += RUN;
        
    }
    

}
void Player::PlayerJump()
{
    float jumpheight = 1.0f//�W�����v�̍����̐ݒ�

    if (Input::IsKey(DIK_SPACE))
    {
        transform_.position_.y += 0.5f;
    }
}
void Player::PlayerAttack()
{

}
void Player::UseAitem()
{

}

void Player::PlayerInputState()
{
    if (Input::IsKey(DIK_W))
    {
        playerstate_ = Playeraction::Walk;
    }
    else if (Input::IsKey(DIK_LSHIFT) && Input::IsKey(DIK_W))
    {
        playerstate_ = Playeraction::run;
    }
    else if (Input::IsKey(DIK_SPACE))
    {
        playerstate_ = Playeraction::jump;
    }
}