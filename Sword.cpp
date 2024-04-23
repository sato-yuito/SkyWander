#include "Sword.h"

Sword::Sword(GameObject* parent):GameObject(parent,"Sword"),swordModelHandle_(-1)
{
}

Sword::~Sword()
{
}

void Sword::Initialize()
{
	swordModelHandle_ = Model::Load("Sword.fbx");
	assert(swordModelHandle_ >= 0);
}

void Sword::Update()
{
}

void Sword::Drow()
{
	Model::SetTransform(swordModelHandle_, transform_);
	Model::Draw(swordModelHandle_);
}

void Sword::Release()
{
}
