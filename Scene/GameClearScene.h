#pragma once
#include"../Engine/GameObject.h"
class GameClearScene :public GameObject
{
public:
	//�R���X�g���N�^
	GameClearScene(GameObject* parent);

	//������
	void Initialize()override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

