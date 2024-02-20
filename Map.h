
#pragma once
#include "Engine/GameObject.h"

class Map :public GameObject
{
    int hModel_;    //���f���ԍ�
    int TestModel_;//�e�X�g���f���\��

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

    int GetModelHandle() { return hModel_; }
};
