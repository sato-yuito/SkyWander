#pragma once
#include"Engine/GameObject.h"
class MoveFloor :public GameObject
{
private:
	int movefloor;
public:
	MoveFloor(GameObject* parent);

	~MoveFloor();
    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    int GetModelHandle() { return movefloor; }
};

