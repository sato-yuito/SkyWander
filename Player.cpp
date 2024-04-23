#include "Player.h"



Player::Player(GameObject* parent) :GameObject(parent, "Player"), playerModelhandle_(-1), playerstate_(Playeraction::wait){
	
}

//デストラクタ
Player::~Player(){
}

//初期化
void Player::Initialize(){
    
	PlayerSpeed = 0.1f;
	
	gravity = 0.02f;
	
	PlayerUP = 0.5f;
	
	PlayerVelocity = { 0,0,0 };
	
	JumpVelocity = { 0,0,0 };
	
	HP = 100;
	
	Attack = 10;
	
	//モデルデータのロード
	playerModelhandle_ = Model::Load("Player.fbx");
	assert(playerModelhandle_ >= 0);
	
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1.3, 1.3, 1.3));
	AddCollider(collision);

	Instantiate<Sword>(this);
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
	Model::SetTransform(playerModelhandle_, transform_);
	Model::Draw(playerModelhandle_);
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
	if (pTarget->GetObjectName() == "Treasure"){
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
	}
}
