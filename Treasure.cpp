#include "Treasure.h"
#include"Engine/Model.h"
#include"Engine/Collider.h"
Treasure::Treasure(GameObject* parent)
	:GameObject(parent, "Treasure"),treasureModel_(-1)
{
}

Treasure::~Treasure()
{
}

void Treasure::Initialize()
{
	treasureModel_ = Model::Load("Treasure.fbx");
	assert(treasureModel_ >= 0);
	transform_.scale_ ={ 0.5,0.5,0.5};
	transform_.rotate_ = { 0,-180,0 };
	transform_.position_ = { 0,-1,185 };

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 2.5f);
	AddCollider(collision);
}

void Treasure::Update(){
	
}

void Treasure::Draw()
{
	Model::SetTransform(treasureModel_, transform_);
	Model::Draw(treasureModel_);
}

void Treasure::Release()
{
}
