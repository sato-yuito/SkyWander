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
	int numberOfModels = 10; //両方10個ずつ出す変数
	for (int i = 0; i < numberOfModels; i++) {
		models.push_back(Model::Load("Map.fbx"));
		//models.push_back(Model::Load("TestairMap.fbx"));
		assert(!models.empty());	
       
		
	}

	for (auto model:models)
	{
		Transform t{};
		t.position_.x = rand() % 10;
		//t.position_.y = rand()%20;
		t.position_.z = rand() % 10;
		Model::SetTransform(model, t);
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


