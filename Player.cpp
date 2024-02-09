#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include"Map.h"

namespace
{
	const float PlayerSpeed = 0.1f;//�v���C���[�̃X�s�[�h
	const float gravity = 0.01f;//�v���C���[�̏d��
	const float PlayerInitialSpeed = 0.05f;//�W�����v�̏����x
	const float JumpHeight = 2.0f;//�W�����v���������̍ō����B�n�_
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), playerstate_(Playeraction::wait)						 
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
}

//�X�V
void Player::Update()
{
	Camera::SetTarget(transform_.position_);
   
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
	
	RayCastData data;
	data.start = transform_.position_;

	data.dir = XMFLOAT3(0, -1, 0);
	 
	Model::RayCast(((Map*)FindObject("Map"))->GetModelHandle(), &data);
	//�W�����v�Ȃǂ����ă}�b�v��ɂ��Ȃ��ꍇ
   if (data.hit)
	{
		if(data.dist > 0.5f)
		{ 
			transform_.position_.y -= gravity;
			
		}
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
	
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
	{
		playerstate_ = Playeraction::Walk;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		playerstate_  = Playeraction::jump;
	}
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

}
void Player::PlayerRun()
{

	if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_W)) ||  Input::IsKey(DIK_S))
	{
		transform_.position_.x = PlayerSpeed * 2;
	}

	else if (Input::IsKey(DIK_LSHIFT) && (Input::IsKey(DIK_D)) || (Input::IsKey(DIK_A)))
	{
		transform_.position_.z = PlayerSpeed * 2;
	}

	
}

bool PlayerLower = false;//�v���C���[�����̍����ɓ��B�������ǂ���
void Player::PlayerJump()
{
	
	//�v���C���[�̈ʒu���ō����B�n�_��荂��������
	if (transform_.position_.y >= JumpHeight )
	{
		PlayerLower = true;

	}
	//�ō��n�_�ɓ��B���Ă��Ȃ���
	if (PlayerLower == false)
	{
		transform_.position_.y += PlayerInitialSpeed;
	}
	if (JumpHeight)
	{
		playerstate_ = Playeraction::Walk;
	}
}


void Player::PlayerAttack()
{

}

void Player::UseAitem()
{

}