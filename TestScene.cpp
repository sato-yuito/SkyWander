#include "TestScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Map.h"
#include"Engine/Camera.h"
//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Map>(this);
	Camera::SetPosition(XMFLOAT3(0, 6, -10));
	
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
