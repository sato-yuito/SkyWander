#include "Map.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
Map::Map(GameObject* parent) :GameObject(parent, "Map"), hModel_(-1)
{
}

Map::~Map()
{
}

void Map::Initialize()
{
	hModel_ = Model::Load("Map.fbx");
	assert(hModel_ >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(10, 0, 10), XMFLOAT3(100, 0, 100));
	AddCollider(collision);
}

void Map::Update()
{
}

void Map::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Map::Release()
{
}


