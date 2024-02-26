#include "Map.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
Map::Map(GameObject* parent) :GameObject(parent, "Map"), TestMap(-1), TestAirMap(-1)
{
}

Map::~Map()
{
}

void Map::Initialize()
{
	TestMap = Model::Load("Map.fbx");
    assert(TestMap >= 0);

	TestAirMap = Model::Load("TestairMap.fbx");
	assert(TestAirMap >= 0);
	TestModelPos.position_ = { 0,5,6 };

}

void Map::Update()
{
}

void Map::Draw()
{
	Model::SetTransform(TestMap, transform_);
	Model::Draw(TestMap);

	Model::SetTransform(TestAirMap, TestModelPos);
	Model::Draw(TestAirMap);
}

void Map::Release()
{
}


