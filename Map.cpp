#include "Map.h"
#include"Engine/Model.h"
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
