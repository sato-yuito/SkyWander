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
		models.push_back(Model::Load("TestairMap.fbx"));
		assert(!models.empty());	

		transform_.position_.x = rand() % 10;
	    transform_.position_.z = rand() % 10;
	}

	//作りたいオブジェクトの個数のトランスフォームをつくってfor分で回す
	
	
	
}

void Map::Update()
{
}

void Map::Draw()
{
	for (auto model : models)
	{
		Model::SetTransform(model, transform_);
		Model::Draw(model);
	}

}

void Map::Release()
{
}


