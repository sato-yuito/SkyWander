#pragma once
#include"Engine/GameObject.h"
class thorn:public GameObject
{
	int thornHandle_;

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

	
};

