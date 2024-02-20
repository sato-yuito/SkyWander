#include "Map.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
Map::Map(GameObject* parent) :GameObject(parent, "Map"), hModel_(-1), TestModel_(-1)
{
}

Map::~Map()
{
}

void Map::Initialize()
{
	hModel_ = Model::Load("Map.fbx");
	assert(hModel_ >= 0);
	
	TestModel_ = Model::Load("TestairMap.fbx");
	assert(TestModel_ >= 0);
	TestModelPos.position_ = { 0,5,6 };

}

void Map::Update()
{
}

void Map::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Model::SetTransform(TestModel_, TestModelPos);
	Model::Draw(TestModel_);
}

void Map::Release()
{
}


