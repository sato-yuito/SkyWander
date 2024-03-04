#include "Map.h"
#include"Engine/Model.h"


Map::Map(GameObject* parent) :GameObject(parent, "Map"){
}

Map::~Map(){
}

void Map::Initialize(){

	for (int i = 0; i < 10; i++)
	{
		Floor* fl = Instantiate<Floor>(this);
		fl->SetPosition(0, 0, i*16);
		floorData.push_back(fl);
	}
	
}

void Map::Update(){
}

void Map::Draw(){
	
}

void Map::Release(){
}


