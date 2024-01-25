#include "TestScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Map.h"
#include"Engine/Camera.h"
//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Map>(this);
	Camera::SetPosition(XMFLOAT3(0, 6, -10));
	
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
