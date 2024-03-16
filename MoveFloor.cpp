#include "MoveFloor.h"
#include"Engine/Model.h"
MoveFloor::MoveFloor(GameObject* parent) :GameObject(parent, "Movefloor"), movefloor(-1)
{
}

MoveFloor::~MoveFloor()
{
	movefloor = Model::Load("Assets/testairmap");
}

void MoveFloor::Initialize()
{
}

void MoveFloor::Update()
{
	int move = 0.05f;
	transform_.position_.y += move;
}

void MoveFloor::Draw()
{
	Model::SetTransform(movefloor, transform_);
	Model::Draw(movefloor);
}

void MoveFloor::Release()
{
}
