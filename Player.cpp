#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include"Engine/ImGui/imgui.h"
#include "Player.h"
#include"Map.h"
#include"Floor.h"
#include"Treasure.h"

namespace
{
	float PlayerSpeed = 0.1f;//�v���C���[�̃X�s�[�h
	float gravity =9.8f;//�v���C���[�̏d��
	float PlayerVelocity = 0.5f;//�W�����v�̏㏸��
}



Player::Player(GameObject* parent) :GameObject(parent, "Player"), playerModel(-1), playerstate_(Playeraction::wait){
	
}

//�f�X�g���N�^
Player::~Player(){
}

//������
void Player::Initialize(){
	//���f���f�[�^�̃��[�h
	Load();
	playerModel = Model::Load("Player.fbx");
	assert(playerModel >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1.3, 1.3, 1.3));
	AddCollider(collision);
}

//�X�V
void Player::Update() {
	
	PlayerCamTarget();

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
	
	if (Input::IsKeyDown(DIK_SPACE)){		
		playerstate_ = Playeraction::jump;
	}
	
}

void Player::PlayerJump(){
	//���C�L���X�g
	RayCastData StageData;
	constexpr float startOffset = 1.0f;
	bool StageHit = false;//stage��ray���������Ă��Ȃ��Ƃ��̕ϐ�
	std::vector< Floor* > StageModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : StageModel) {
		StageData.start = transform_.position_;
		StageData.start.y += startOffset;
		StageData.dir = XMFLOAT3(0, -1, 0);
		Model::RayCast(mapmodels->GetModelHandle(), &StageData);
		if (StageData.hit)
			StageHit = true;
		
	}
	
	if (StageHit&& StageData.dist < startOffset) {
		transform_.position_.y += (startOffset - StageData.dist);
		PlayerVelocity = 0;
		playerstate_ = Playeraction::wait;
	}
	else
	{
		transform_.position_.y += PlayerVelocity;
		PlayerVelocity -= gravity;
	}

}


void Player::PlayerAttack(){
}

void Player::Useitem(){
}

void Player::PlayerCamTarget(){
	//y��z�����ɗ����J����
	float CamdisPlayerY = 6.5f;
	float CamdisPlayerZ = 10.0f;
	//y�����͏�(+)z�����͌��(-)�ɃJ������u��
	XMFLOAT3 CmPos =
	{
		transform_.position_.x,
		transform_.position_.y + CamdisPlayerY,
		transform_.position_.z - CamdisPlayerZ
	};

	Camera::SetPosition(CmPos);
	Camera::SetTarget(transform_.position_);
}


void Player::Load() {
	
	std::string PlayerFileName = "Player.json";
	std::ifstream ifs(PlayerFileName.c_str());
	if (ifs.is_open())
	{
		json playerjson;
		ifs >> playerjson;

		HP = playerjson["HP"];
		Attack = playerjson["Attack"];
	}
}

void Player::Save()
{
	
	
	
}



void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Treasure")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
	}
}
//����
/*
  

	�A�h�o�C�X
	�����₷���悤�ɂ����ɂ͕������Z��ۑ����Ă���update�������̂��������ǂ��܂̂܂܂�
	��ԑJ�ڂ͕ϐ��ɒ��ړ����̂ł͂Ȃ��֐��ŌĂԂׂ��B
	��ԑJ�ڂ͏��Ȃ��ꍇ�͍��̂܂܂ł������Ǒ����Ȃ鎞�ʕʂȕϐ�������Ă���肷�ׂ�

*/