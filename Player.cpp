#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include"Map.h"
#include"Engine/ImGui/imgui.h"
namespace
{
	const float PlayerSpeed = 0.1f;//プレイヤーのスピード
	const float gravity = 0.01f;//プレイヤーの重力
	const float PlayerInitialSpeed = 0.05f;//ジャンプの速度
	const float JumpHeight = 2.0f;//ジャンプをした時の最高到達地点
	bool isPlayerDown = false;//プレイヤーが下降しているかどうか
}

Player::Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), playerstate_(Playeraction::wait){

}

//デストラクタ
Player::~Player(){
}

//初期化
void Player::Initialize(){
	//モデルデータのロード
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
}

//更新
void Player::Update() {
	//カメラの更新
	Camera::SetTarget(transform_.position_);

	switch (playerstate_)
	{
	case Playeraction::wait:
		PlayerWait();
		break;
	case Playeraction::Walk:
		PlayerWalk();
		break;
	case Playeraction::jump:
		PlayerJump();
		break;
	case Playeraction::attack:
		PlayerAttack();
		break;
	}

	//レイキャスト
	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast(((Map*)FindObject("Map"))->GetModelHandle(), &data);
	//ジャンプなどをしてマップ上にいない場合
	if (data.hit) {
		if (data.dist > 0.5f) {
			transform_.position_.y -= gravity;
		}
	}

	XMFLOAT3 p_pos = transform_.position_;
	ImGui::Text("Player Position = { %f,%f,%f}", p_pos.x, p_pos.y, p_pos.z);

	float dist = data.dist;
	ImGui::Text("dist = %f", dist);

	bool isHit = data.hit;
	ImGui::Text("isHit = %s", isHit ? "true" : "false");
}

//描画
void Player::Draw(){
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release(){

}


void Player::PlayerWait(){
	
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S)  
		||Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
	{
		playerstate_ = Playeraction::Walk;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		isPlayerDown = false;
		playerstate_  = Playeraction::jump;
	}
}

void Player::PlayerWalk(){
	//前後移動
	if (Input::IsKey(DIK_W)){
		transform_.position_.z+= PlayerSpeed;
	}
	if (Input::IsKey(DIK_S)){
		transform_.position_.z -= PlayerSpeed;
	}
	//左右移動
	if (Input::IsKey(DIK_D)){
		transform_.position_.x += PlayerSpeed;
	}
	if (Input::IsKey(DIK_A)){
		transform_.position_.x -= PlayerSpeed;
	}
	//ダッシュ
	if (Input::IsKey(DIK_LSHIFT)){
		transform_.position_.x *= PlayerSpeed * 2;
		transform_.position_.z *= PlayerSpeed * 2;
	}
	//ジャンプ
	if (Input::IsKeyDown(DIK_SPACE)){
		playerstate_ = Playeraction::jump;
	}
}

void Player::PlayerJump(){
	//プレイヤーの位置が最高到達地点より高かったら
	if (transform_.position_.y >= JumpHeight ){
		isPlayerDown  = true;
	}

	//最高地点に到達していない間
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