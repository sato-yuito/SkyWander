#pragma once
#include"Engine/GameObject.h"
class thorn:public GameObject
{
	int thornModel_;

public:
	thorn(GameObject* parent);

	//�f�X�g���N�^
	~thorn();

	//������
	void Initialize() override;

	//�X�V
	void Update()override;

	//���f���\��
	void Draw() override;

	//�J��
	void Release() override;

	//���f���ԍ��̎擾
	int GetModelHandle() { return thornModel_; }
};

