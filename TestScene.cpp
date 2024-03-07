#include "TestScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Map.h"
#include"Floor.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	
	 Instantiate<Map>(this);
	
	Instantiate<Player>(this);
	
	Instantiate<Enemy>(this);
	//Camera::SetPosition(XMFLOAT3(0, 6, -10));
}

//更新
void TestScene::Update()
{
	GameObject* pGameObject = FindObject("Player");
	if (pGameObject == nullptr)
	{
		SceneManager* GameOverScene = (SceneManager*)FindObject("SceneManager");
		GameOverScene->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
