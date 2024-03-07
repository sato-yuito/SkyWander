#include "TestScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Map.h"
#include"Floor.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	
	 Instantiate<Map>(this);
	
	Instantiate<Player>(this);
	
	Instantiate<Enemy>(this);
	//Camera::SetPosition(XMFLOAT3(0, 6, -10));
}

//�X�V
void TestScene::Update()
{
	GameObject* pGameObject = FindObject("Player");
	if (pGameObject == nullptr)
	{
		SceneManager* GameOverScene = (SceneManager*)FindObject("SceneManager");
		GameOverScene->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
