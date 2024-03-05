#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include"Map.h"
#include"Floor.h"
#include"Engine/ImGui/imgui.h"
namespace
{
	float PlayerSpeed = 0.1f;//�v���C���[�̃X�s�[�h
	float gravity =0.02f;//�v���C���[�̏d��
	float PlayerInitialSpeed = 0.5f;//�W�����v�̏㏸��
	
	bool isPlayerDown = false;//�v���C���[�����~���Ă��邩�ǂ���
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), playerModel(-1), playerstate_(Playeraction::wait){

}

//�f�X�g���N�^
Player::~Player(){
}

//������
void Player::Initialize(){
	//���f���f�[�^�̃��[�h
	playerModel = Model::Load("Player.fbx");
	assert(playerModel >= 0);
}

//�X�V
void Player::Update() {

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
	RayCastData Gronddata;
	bool PlayerHit = false;//���ł��q�b�g������
	std::vector< Floor* > mapModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : mapModel) {
		Gronddata.start = transform_.position_;
		Gronddata.dir = XMFLOAT3(0, -1, 0);
		Model::RayCast(mapmodels->GetModelHandle(), &Gronddata);
		//�W�����v�Ȃǂ����ă}�b�v��ɂ��Ȃ��ꍇ
		ImGui::Text("hit=%s", Gronddata.hit ? "true " : "false");
		ImGui::Text("dist=%f", Gronddata.dist );
		if (Gronddata.hit)
			PlayerHit = true;

	}
	if (PlayerHit) {
		if (Gronddata.dist > 0.5f) {
			transform_.position_.y += PlayerInitialSpeed;
			PlayerInitialSpeed -= gravity;
		}
	}
	else
	{
		transform_.position_.y -= gravity;
		if (transform_.position_.y < -1)
		{
			KillMe();
		}
	}


	ImGui::Text("state = %d", (int)playerstate_);
	
}

//�`��
void Player::Draw(){
	Model::SetTransform(playerModel, transform_);
	Model::Draw(playerModel);
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
	float curSpeed = 0.0f;
	
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
	
	if (Input::IsKeyDown(DIK_SPACE))
	{
		isPlayerDown = true;

		playerstate_ = Playeraction::jump;

		PlayerInitialSpeed = 0.5f;
		
	}
	
}

void Player::PlayerJump(){

	if (transform_.position_.y < 0.5f) {
			transform_.position_.y = 0.5f;
			isPlayerDown = false;
			playerstate_ = Playeraction::wait;
	}
	
}


void Player::PlayerAttack(){
}

void Player::Useitem(){
}

void Player::PlayerCamTarget(){
	
	
}



