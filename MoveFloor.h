#pragma once
#include"Engine/GameObject.h"
class MoveFloor :public GameObject
{
private:
	int movefloor;
public:
	MoveFloor(GameObject* parent);

	~MoveFloor();
    //‰Šú‰»
    void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;

    int GetModelHandle() { return movefloor; }
};

