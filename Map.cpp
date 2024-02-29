#include "Map.h"
#include"Engine/Model.h"


Map::Map(GameObject* parent) :GameObject(parent, "Map"), models{}
{
}

Map::~Map()
{
}

void Map::Initialize()
{
	int numberOfModels = 10; //—¼•û10ŒÂ‚¸‚Âo‚·•Ï”
	for (int i = 0; i < numberOfModels; i++) {
		models.push_back(Model::Load("Map.fbx"));
		models.push_back(Model::Load("TestairMap.fbx"));
		assert(!models.empty());	
       
		Transform t{};
		t.position_.x = rand() % 25;
		
		t.position_.z = rand() % 10;
		Model::SetTransform(numberOfModels,t);
	}

	
	
	
	
}

void Map::Update()
{
}

void Map::Draw()
{
	for (auto model : models)
	{
		Model::Draw(model);
	}

}

void Map::Release()
{
}


