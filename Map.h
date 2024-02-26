#pragma once
#include "Engine/GameObject.h"
#include<vector>
class Map :public GameObject
{
    std::vector<int>AllMapModel;

    Transform TestModelPos;
public:
    //�R���X�g���N�^
    Map(GameObject* parent);

    //�f�X�g���N�^
    ~Map();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    std::vector<int> GetModelHandle() { return AllMapModel; }
};
