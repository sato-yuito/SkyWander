#include "Map.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
Map::Map(GameObject* parent) :GameObject(parent, "Map"), AllMapModel(-1)
{
}

Map::~Map()
{
}

void Map::Initialize()
{

	for (auto hModel : AllMapModel)
	{
		AllMapModel =Model::Load("Map.fbx");
		assert(AllMapModel >= 0);

		TestModel_ = Model::Load("TestairMap.fbx");
		assert(TestModel_ >= 0);
		TestModelPos.position_ = { 0,5,6 };

	}
	
}

void Map::Update()
{
}

void Map::Draw()
{
	
}

void Map::Release()
{
}


