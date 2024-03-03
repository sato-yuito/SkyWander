#include "Map.h"
#include"Engine/Model.h"


Map::Map(GameObject* parent) :GameObject(parent, "Map"), models{}{
}

Map::~Map(){
}

void Map::Initialize(){

	int numberOfModels = 10; //—¼•û10ŒÂ‚¸‚Âo‚·•Ï”
	for (int i = 0; i < numberOfModels; i++) {
		models.push_back(Model::Load("Map.fbx"));
		assert(!models.empty());	
	}


	for (auto model:models){
		Transform t{};
		t.position_.x = rand() % 50;
		//t.position_.y = rand()%20;
		t.position_.z = rand() % 50;
		Model::SetTransform(model, t);
	}
}

void Map::Update(){
}

void Map::Draw(){
	for (auto model : models){
		Model::Draw(model);
	}
}

void Map::Release(){
}


