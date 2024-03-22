#include "Treasure.h"
#include"Engine/Model.h"
Treasure::Treasure(GameObject* parent)
	:GameObject(parent, "treasure"),treasureModel_(-1)
{
}

Treasure::~Treasure()
{
}

void Treasure::Initialize()
{
	treasureModel_ = Model::Load("Assets/Treasure.fbx");
	SetPosition(200, 0, 25);
}

void Treasure::Update(){
	if (FindObject("Player"))
	{

	}
}

void Treasure::Draw()
{
	Model::SetTransform(treasureModel_, transform_);
	Model::Draw(treasureModel_);
}

void Treasure::Release()
{
}
