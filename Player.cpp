#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include"Map.h"
#include"Engine/ImGui/imgui.h"
namespace
{
	const float PlayerSpeed = 0.1f;//�v���C���[�̃X�s�[�h
	const float gravity = 0.01f;//�v���C���[�̏d��
	const float PlayerInitialSpeed = 0.05f;//�W�����v�̑��x
	const float JumpHeight = 2.0f;//�W�����v���������̍ō����B�n�_
	bool isPlayerDown = false;//�v���C���[�����~���Ă��邩�ǂ���
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), playerstate_(Playeraction::wait){

}

//�f�X�g���N�^
Player::~Player(){
}

//������
void Player::Initialize(){
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Player::Update() {
	//�J�����̍X�V
	Camera::SetTarget(transform_.position_);

	switch (playerstate_)
	{
	case Playeraction::wait:
		PlayerWait();
		break;
	case Playeraction::walk:
		PlayerWalk();
		break;
	case Playeraction::jump:
		PlayerJump();
		break;
	case Playeraction::attack:
		PlayerAttack();
		break;

	}

	//���C�L���X�g
	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast(((Map*)FindObject("Map"))->GetModelHandle(), &data);
	//�W�����v�Ȃǂ����ă}�b�v��ɂ��Ȃ��ꍇ
	if (data.hit) {
		if (data.dist > 0.5f) {
			transform_.position_.y -= gravity;
		}
	}
	
	ImGui::Text("state = %d", (int)playerstate_);
}

//�`��
void Player::Draw(){
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release(){

}


void Player::PlayerWait(){
	
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S)  
		||Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
	{
		playerstate_ = Playeraction::walk;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		isPlayerDown = false;
		playerstate_  = Playeraction::jump;
	}
}

void Player::PlayerWalk(){
	float curSpeed;
	
	//�_�b�V�������Ă���Ƃ�
	if (Input::IsKey(DIK_LSHIFT)) {
		curSpeed = PlayerSpeed * 2;
	}
	else {
		curSpeed = PlayerSpeed;
	}
	//�O��ړ�
	if (Input::IsKey(DIK_W)){
		transform_.position_.z+= curSpeed;
	}
	if (Input::IsKey(DIK_S)){
		transform_.position_.z -= curSpeed;
	}
	//���E�ړ�
	if (Input::IsKey(DIK_D)){
		transform_.position_.x += curSpeed;
	}
	if (Input::IsKey(DIK_A)){
		transform_.position_.x -= curSpeed;
	}
	
	if (Input::IsKey(DIK_SPACE)){
		PlayerJump();
	}
	
}

void Player::PlayerJump(){
	//�v���C���[�̈ʒu���ō����B�n�_��荂��������
	if (transform_.position_.y >= JumpHeight ){
		isPlayerDown  = true;
	}

	//�ō��n�_�ɓ��B���Ă��Ȃ���
	if (isPlayerDown == false){
		transform_.position_.y += PlayerInitialSpeed;
	}
	
	if (isPlayerDown == true) {
		if (transform_.position_.y <= 0.5f) {
			playerstate_ = Playeraction::wait;
		}
	}
}


void Player::PlayerAttack(){
}

void Player::Useitem(){
}

void Player::Playerfalling()
{

}


