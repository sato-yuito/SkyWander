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
	float PlayerUP = 0.5f;//ジャンプの上昇量
	XMFLOAT3 PlayerVelocity = { 0,0,0 };//移動量
	XMFLOAT3 JumpVelocity = { 0,0,0 };//ジャンプの移動量
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
	case Playeraction::fall:
		PlayerFall();
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
		PlayerVelocity.z += curSpeed;
	}
	if (Input::IsKey(DIK_S)){
		PlayerVelocity.z -= curSpeed;
	}
	//左右移動
	if (Input::IsKey(DIK_D)){
		PlayerVelocity.x += curSpeed;
	}
	if (Input::IsKey(DIK_A)){
		PlayerVelocity.x -= curSpeed;
	}
	
	if (Input::IsKeyDown(DIK_SPACE)){		
		JumpVelocity = PlayerVelocity;
		playerstate_ = Playeraction::jump;
		 
	}
	transform_.position_.x += PlayerVelocity.x;
	transform_.position_.y += PlayerVelocity.y;
	transform_.position_.z += PlayerVelocity.z;
	PlayerVelocity = { 0.0f,0.0f,0.0f };
}

void Player::PlayerJump(){

	//下記がtrueのときwaitに戻し上昇量を初期値にもどす
	if (stageDatahit()){
		playerstate_ = Playeraction::wait;
		PlayerUP = 0.5f;
	}
	else{
		transform_.position_.x += JumpVelocity.x;
		transform_.position_.z += JumpVelocity.z;
		transform_.position_.y += PlayerUP;
		PlayerUP -= gravity;
	}

	if (PlayerUP <= 0)
	{
		playerstate_ = Playeraction::fall;
	}
}

void Player::PlayerFall(){
	// Y方向の速度を減少させて落下させる
	PlayerVelocity.y -= gravity;

	// プレイヤーの位置を更新
	transform_.position_.x += PlayerVelocity.x;
	transform_.position_.y += PlayerVelocity.y;
	transform_.position_.z += PlayerVelocity.z;
}

bool Player::stageDatahit(){
	RayCastData StageData;
	bool StageHit = false;//stageのrayが当たっていないときの変数
	const float PlayerPosy = 1.0;//Playerがジャンプしたときの高さ
	const float returnpPosy = -0.5;//プレイヤーがジャンプして戻る距離(+だったら上昇しなくなる(検証済み))
	//StageModelのDataを取得
	std::vector< Floor* > StageModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : StageModel) {
		StageData.start = transform_.position_;
		StageData.start.y += PlayerPosy;
		StageData.dir = XMFLOAT3(0, -1, 0);
		Model::RayCast(mapmodels->GetModelHandle(), &StageData);
		if (StageData.hit)
			StageHit = true;
	}
	//当たっているかつレイが当たったと距離とプレイヤーの高さがreturnJump以下の時位置を更新
	if (StageHit && StageData.dist- PlayerPosy <= returnpPosy) {
	transform_.position_.y +=  PlayerPosy-StageData.dist;
		return true;
	}
	
	return false;
}
void Player::PlayerAttack(){
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