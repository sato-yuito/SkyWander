#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
class Enemy :public GameObject
{
    int hModel_;    //���f���ԍ�
    float movement_;
    float angle_;
    int time_;
    int timing_;
   
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;


    //����p�̐ݒ�
    bool EnemyPOV(const XMFLOAT3 &PlayerVec);

    //�v���C���[����������ǐ�
    void ShowPlayer(Player&player,float speed);
};

