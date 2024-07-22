#include "PlayScene.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"
#include"../Stage/Map.h"
#include"../Stage/Floor.h"
#include"../GoalItem/Treasure.h"
#include"../Engine/Camera.h"
#include "../Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{

	Instantiate<Map>(this);

	Instantiate<Player>(this);

	Instantiate<Enemy>(this);

	Instantiate<Treasure>(this);
}

void PlayScene::Update()
{
	GameObject* pGameObject = FindObject("Player");
	if (pGameObject == nullptr)
	{
		SceneManager* GameOverScene = (SceneManager*)FindObject("SceneManager");
		GameOverScene->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
