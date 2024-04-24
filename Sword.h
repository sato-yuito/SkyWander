#pragma once
#include"Engine/GameObject.h"
#include "Engine/Model.h"
class Sword:public GameObject
{
private:
	int swordModelHandle_;
public:
	//�R���X�g���N�^
	Sword(GameObject* parent);
	//�f�X�g���N�^
	~Sword();
	//������
	void Initialize() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;
	//���
	void Release() override;
};

