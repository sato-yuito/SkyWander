#pragma once
#include "../Engine/GameObject.h"
#include<vector>
#include"Floor.h"

class Map :public GameObject
{
    std::vector<Floor*>floorData;
    
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

    std::vector<Floor*>GetfloorData() { return floorData; }
  
};
