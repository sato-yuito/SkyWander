#pragma once
#include"Engine/GameObject.h"
class Treasure:public GameObject
{
	int treasureModel_;
public:
	Treasure(GameObject*parent);

	~Treasure();
	//������
	void Initialize() override;

	//�X�V
	void Update()override;

	//���f���\��
	void Draw() override;

	//�J��
	void Release() override;

	//���f���ԍ����擾
	int GetModelHandle() { return treasureModel_; }
};

