#pragma once
#include"../Engine/GameObject.h"
class GameOverScene :public GameObject
{
public:
	//�R���X�g���N�^
	GameOverScene(GameObject* parent);

	//������
	void Initialize()override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

