#include "thorn.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
thorn::thorn(GameObject* parent)
	:GameObject(parent, "thron"), thornHandle_(-1)
{
}

thorn::~thorn()
{
}

void thorn::Initialize()
{
    //モデルデータのロード
    thornHandle_ = Model::Load("Assets/thoron.fbx");
    assert(thornHandle_ >= 0);

    //球体型のコライダーをつけて当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collision);
}

void thorn::Update()
{

    transform_.rotate_.x = 0.5f;

}

void thorn::Draw()
{
    Model::SetTransform(thornHandle_, transform_);
    Model::Draw(thornHandle_);
}

void thorn::Release()
{
}
