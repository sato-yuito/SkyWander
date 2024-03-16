#pragma once
#include<vector>
#include"Engine/GameObject.h"
class Floor:public GameObject
{
	
	int floorModel_;

public:
	Floor(GameObject* parent);

	//�f�X�g���N�^
	~Floor();

	//������
	void Initialize() override;

	//�X�V
	void Update()override;

	//���f���\��
	void Draw() override;

	//�J��
	void Release() override;

	//���f���ԍ��̎擾
	int GetModelHandle() { return floorModel_; }
};

