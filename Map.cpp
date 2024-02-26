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
	AllMapModel.push_back(2);
	for (auto hModel : AllMapModel)
	{
		hModel = Model::Load("Map.fbx");
		assert(hModel >= 0);

		hModel = Model::Load("TestairMap.fbx");
		assert(hModel >= 0);
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


