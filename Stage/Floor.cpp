#include "floor.h"
#include"../Engine/Model.h"
Floor::Floor(GameObject* parent):GameObject(parent,"floor"), floorModel_(-1)
{
}

Floor::~Floor(){
}

void Floor::Initialize(){
	floorModel_ = Model::Load("Map.fbx");
	//assert(floorModel_ > 0);
}

void Floor::Update(){
	
}

void Floor::Draw()
{
	Model::SetTransform(floorModel_, transform_);
	Model::Draw(floorModel_);
}

void Floor::Release(){
}

