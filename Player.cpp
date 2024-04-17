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
	float PlayerSpeed = 0.1f;//プレイヤーのスピード
	float gravity =0.02f;//プレイヤーの重力
	float PlayerVelocity = 0.5f;//ジャンプの上昇量
	int HP = 100;//体力
	int Attack = 10;//攻撃力
}



Player::Player(GameObject* parent) :GameObject(parent, "Player"), playerModel(-1), playerstate_(Playeraction::wait){
	
}

//デストラクタ
Player::~Player(){
}

//初期化
void Player::Initialize(){
	//モデルデータのロード
	Load();
	playerModel = Model::Load("Player.fbx");
	assert(playerModel >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1.3, 1.3, 1.3));
	AddCollider(collision);
}

//更新
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
	
}

//描画
void Player::Draw(){
	Model::SetTransform(playerModel, transform_);
	Model::Draw(playerModel);
}

//開放
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
	
	//ダッシュをしているとき
	if (Input::IsKey(DIK_LSHIFT)) {
		curSpeed = PlayerSpeed * 2;
	}
	else {
		curSpeed = PlayerSpeed;
	}
	//前後移動
	if (Input::IsKey(DIK_W)){
		transform_.position_.z+= curSpeed;
	}
	if (Input::IsKey(DIK_S)){
		transform_.position_.z -= curSpeed;
	}
	//左右移動
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
	
	if (stageDatahit())
	{

		playerstate_ = Playeraction::wait;
		PlayerVelocity = 0.5f;
	}
	else
	{
		transform_.position_.y += PlayerVelocity;
		PlayerVelocity -= gravity;
	}

}


bool Player::stageDatahit(){
	RayCastData StageData;
	bool StageHit = false;//stageのrayが当たっていないときの変数
	std::vector< Floor* > StageModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : StageModel) {
		StageData.start = transform_.position_;
		StageData.start.z = 0.0f;
		StageData.dir = XMFLOAT3(0, -1, 0);
		Model::RayCast(mapmodels->GetModelHandle(), &StageData);
		if (StageData.hit)
			StageHit = true;
	}
	
	if (StageHit && StageData.dist <=) {
		return true;
	}
	return false;

}
void Player::PlayerAttack(){
}

void Player::Useitem(){
}

void Player::PlayerCamTarget(){
	//yとz方向に離すカメラ
	float CamdisPlayerY = 6.5f;
	float CamdisPlayerZ = 10.0f;
	//y方向は上(+)z方向は後ろ(-)にカメラを置く
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
//メモ
/*
  

	アドバイス
	見えやすいようにかくには物理演算を保存しているupdateを書くのもいいけどいまのままで
	状態遷移は変数に直接入れるのではなく関数で呼ぶべき。
	状態遷移は少ない場合は今のままでいいけど多くなる時別別な変数を作ってかんりすべき

*/