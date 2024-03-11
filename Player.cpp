#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include"Engine/Camera.h"
#include"Map.h"
#include"Floor.h"
#include"Engine/ImGui/imgui.h"

namespace
{
	float PlayerSpeed = 0.1f;//プレイヤーのスピード
	float gravity =0.02f;//プレイヤーの重力
	float PlayerInitialSpeed = 0.5f;//ジャンプの上昇量
	bool isPlayerDown = false;//プレイヤーが下降しているかどうか
	int HP =0;//体力
	int Attack = 0;//攻撃力
}

using json = nlohmann::json;

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

	//レイキャスト
	RayCastData Gronddata;
	bool PlayerHit = false;//一回でもヒットしたら
	std::vector< Floor* > mapModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : mapModel) {
		Gronddata.start = transform_.position_;
		Gronddata.dir = XMFLOAT3(0, -1, 0);
		Model::RayCast(mapmodels->GetModelHandle(), &Gronddata);
		//ジャンプなどをしてマップ上にいない場合
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

		if (transform_.position_.y < -1)
		{
			KillMe();
		}
	}


	ImGui::Text("state = %d", (int)playerstate_);
	
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
		isPlayerDown = false;
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


void Player::Load(std::string LoadFile) {
	if (LoadFile.empty()) {
		LoadFile = "Player.json"; 
	}
	std::ifstream file(LoadFile);
	if (file.is_open())
	{
		json playerdata;
		file >> playerdata;

		HP = playerdata["HP"];
		Attack = playerdata["Attack"];
		file.close();
	}
}

void Player::Save(std::string SaveFile)
{
	if (SaveFile.empty())
	{
		SaveFile = "Player.json";
	}
	json data;
	data["HP"] = HP;
	data["Attack"] = Attack;

	std::ofstream file(SaveFile);
	if (file.is_open()) {
		file << std::setw(3) << data << std::endl;
		file.close();
	}
}



//メモ
/*
   まず下にraycast打ってポリゴンないときがおかしい
   着地した時にジャンプのフラグが治っていないのが問題
    ->それが解決したら敵キャラクターの動きも直し+プレイやーの攻撃処理もしたりアニメーションとかもやったりまだまだたくさんやることが
	:( 

	アドバイス
	見えやすいようにかくには物理演算を保存しているupdateを書くのもいいけどいまのままで
	状態遷移は変数に直接入れるのではなく関数で呼ぶべき。
	状態遷移は少ない場合は今のままでいいけど多くなる時別別な変数を作ってかんりすべき

*/