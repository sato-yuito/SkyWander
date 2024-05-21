#include "Player.h"
#include"Sword.h"


Player::Player(GameObject* parent) :GameObject(parent, "Player"), playerModelhandle_(-1), playerstate_(Playeraction::wait)
{
	
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    
	PlayerSpeed = 0.1f;
	
	gravity = 0.02f;
	
	PlayerUP = 0.5f;
	
	PlayerVelocity = { 0,0,0 };
	
	JumpVelocity = { 0,0,0 };
	
	HP = 100;

	Attack = 10;
	
	footRayCast = 1.0;
	returnpPosy = -0.5;

	//���f���f�[�^�̃��[�h
	playerModelhandle_ = Model::Load("Player.fbx");
	assert(playerModelhandle_ >= 0);
	
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1.3, 1.3, 1.3));
	AddCollider(collision);

	//Instantiate<Sword>(this);
}

//�X�V
void Player::Update()
{
	PlayerCamTarget();

	switch (playerstate_){
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

//�`��
void Player::Draw()
{
	Model::SetTransform(playerModelhandle_, transform_);
	Model::Draw(playerModelhandle_);
}

//�J��
void Player::Release()
{

}

void Player::PlayerWait()
{
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S)  
		||Input::IsKey(DIK_D) || Input::IsKey(DIK_A)){
		playerstate_ = Playeraction::walk;
	}
	if (Input::IsKeyDown(DIK_SPACE)){
		playerstate_  = Playeraction::jump;
	}
}

void Player::PlayerWalk()
{
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
		PlayerVelocity.z += curSpeed;
	}
	if (Input::IsKey(DIK_S)){
		PlayerVelocity.z -= curSpeed;
	}
	//���E�ړ�
	if (Input::IsKey(DIK_D)){
		PlayerVelocity.x += curSpeed;
	}
	if (Input::IsKey(DIK_A)){
		PlayerVelocity.x -= curSpeed;
	}
	
	//������ς��鏈��
	XMVECTOR VectorPlayerMove = {0.0f,0.0f,0.0f,0.0f};
	VectorPlayerMove = XMLoadFloat3(&PlayerVelocity);
	XMVECTOR PlayerVecLength_ =  XMVector3Length(VectorPlayerMove);
	float PlayerLength_ = XMVectorGetX(PlayerVecLength_);
	if (PlayerLength_ != 0) {
		XMVECTOR PlayerFront = { 0,0,1,0 };
		VectorPlayerMove = XMVector3Normalize(VectorPlayerMove);
		XMVECTOR VecPlayerDot = XMVector3Dot(PlayerFront, VectorPlayerMove);
		float PlayerDot = XMVectorGetX(VecPlayerDot);
		float PlayerAngle = acos(PlayerDot);
		XMVECTOR VecPlayerCross = XMVector3Cross(PlayerFront, VectorPlayerMove);
		if (XMVectorGetY(VecPlayerCross) < 0){
			PlayerAngle *= -1;
		}
		transform_.rotate_.y = XMConvertToDegrees(PlayerAngle);
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

void Player::PlayerJump()
{
	//���L��true�̂Ƃ�wait�ɖ߂��㏸�ʂ������l�ɂ��ǂ�
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

void Player::PlayerFall()
{
	
	
}

bool Player::stageDatahit()
{
	RayCastData stageRayCast = PlayerRayCast();
	
	//�������Ă��邩���C�����������Ƌ����ƃv���C���[�̍�����returnpPosy�ȉ��̎��ʒu���X�V
	if (stageRayCast.hit&& footRayCast -stageRayCast.dist <= returnpPosy) {
		transform_.position_.y += (footRayCast - stageRayCast.dist);
		return true;
	}
	
	//ImGui::Text("isHit = %s", stageRayCast.hit ? "true" : "false");

	return false;
}

RayCastData Player::PlayerRayCast()
{
	RayCastData StageData;
	bool StageHit = false;//stage��ray���������Ă��Ȃ��Ƃ��̕ϐ�
	StageData.start = transform_.position_;
	StageData.start.y += footRayCast;
	StageData.dir = XMFLOAT3(0, -1, 0);

	//StageModel��Data���擾
	std::vector< Floor* > StageModel = ((Map*)FindObject("Map"))->GetfloorData();
	for (auto mapmodels : StageModel) {
		Model::RayCast(mapmodels->GetModelHandle(), &StageData);
		if (StageData.hit)
			StageHit = true;
		
	}

	StageData.hit = StageHit;
	return StageData;
}

void Player::PlayerAttack()
{
	
}

void Player::PlayerCamTarget()
{
	//y��z�����ɗ����J����
	float CamthisPlayerY = 6.5f;
	float CamthisPlayerZ = 10.0f;
	//y�����͏�(+)z�����͌��(-)�ɃJ������u��
	XMFLOAT3 CmPos ={
		transform_.position_.x,
		transform_.position_.y + CamthisPlayerY,
		transform_.position_.z - CamthisPlayerZ
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
